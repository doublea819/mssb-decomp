// On-screen touch controls (iPhone): a floating analog stick on the left half of
// the screen and GameCube buttons on the right (the web build's layout, port/web/
// touch.js), drawn with ImGui over the game. Port 1 reads them on top of any
// controller (port_touch_apply, from PADRead). They hide once a controller is
// used and come back when the screen is touched.
//
// On by default on iOS; MSSB_TOUCH=1 turns them on elsewhere (MSSB_TOUCH=0 off).
#include <dolphin/pad.h>

#include <SDL3/SDL.h>
#include <imgui.h>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>

namespace {

enum Btn { B_A, B_B, B_X, B_Y, B_L, B_R, B_Z, B_START, B_COUNT };

struct Layout
{
    float x, y, w, h; // points
    bool round;
};

const u16 kMask[B_COUNT] = {PAD_BUTTON_A, PAD_BUTTON_B,  PAD_BUTTON_X,  PAD_BUTTON_Y,
                            PAD_TRIGGER_L, PAD_TRIGGER_R, PAD_TRIGGER_Z, PAD_BUTTON_START};
const char* const kLabel[B_COUNT] = {"A", "B", "X", "Y", "L", "R", "Z", "START"};
const ImU32 kColor[B_COUNT] = {IM_COL32(46, 179, 109, 255),  IM_COL32(214, 60, 60, 255),
                               IM_COL32(183, 192, 207, 255), IM_COL32(183, 192, 207, 255),
                               IM_COL32(125, 135, 153, 255), IM_COL32(125, 135, 153, 255),
                               IM_COL32(120, 90, 200, 255),  IM_COL32(125, 135, 153, 255)};

std::mutex s_mutex;
bool s_enabled = false;  // touch controls exist on this device
bool s_visible = false;  // shown (hidden while a controller is in use)
Layout s_btn[B_COUNT];
float s_unit = 1.0f;     // layout scale
float s_stickHomeX = 0, s_stickHomeY = 0;
float s_winW = 1, s_winH = 1;

struct Stick
{
    SDL_FingerID id;
    float x0, y0, x, y;
};
bool s_hasStick = false;
Stick s_stick;
std::map<SDL_FingerID, int> s_fingerBtn; // finger -> button (-1: none)

u16 s_buttons = 0;
s8 s_sx = 0, s_sy = 0;

float stick_radius() { return 56.0f * s_unit; }

void layout(SDL_Window* win)
{
    int w = 0, h = 0;
    SDL_GetWindowSize(win, &w, &h);
    if (w <= 0 || h <= 0)
        return;
    s_winW = (float)w;
    s_winH = (float)h;
    SDL_Rect safe{0, 0, w, h};
    SDL_GetWindowSafeArea(win, &safe);
    // 1.0 on a ~400 pt tall landscape phone; bigger on the Duo's inner screen.
    float u = s_winH / 400.0f;
    u = u < 0.8f ? 0.8f : (u > 1.6f ? 1.6f : u);
    s_unit = u;
    const float pad = 16.0f * u;
    const float left = (float)safe.x + pad;
    const float right = (float)(safe.x + safe.w) - pad;
    const float top = (float)safe.y + 10.0f * u;
    const float bottom = (float)(safe.y + safe.h) - pad;
    // The face buttons, as the web build's cluster (194 x 178).
    const float cx = right - 194.0f * u;
    const float cy = bottom - 178.0f * u;
    s_btn[B_A] = {cx + 52 * u, cy + 50 * u, 84 * u, 84 * u, true};
    s_btn[B_B] = {cx + 0 * u, cy + 122 * u, 56 * u, 56 * u, true};
    s_btn[B_X] = {cx + 142 * u, cy + 40 * u, 52 * u, 72 * u, false};
    s_btn[B_Y] = {cx + 46 * u, cy + 0 * u, 76 * u, 46 * u, false};
    s_btn[B_L] = {left, top, 84 * u, 44 * u, false};
    s_btn[B_START] = {left, top + 58 * u, 76 * u, 32 * u, false};
    s_btn[B_R] = {right - 84 * u, top, 84 * u, 44 * u, false};
    s_btn[B_Z] = {right - 64 * u, top + 54 * u, 64 * u, 36 * u, false};
    s_stickHomeX = left + 76 * u;
    s_stickHomeY = bottom - 76 * u;
}

int button_at(float x, float y)
{
    const float slop = 6.0f * s_unit;
    for (int i = 0; i < B_COUNT; i++)
    {
        const Layout& b = s_btn[i];
        if (x >= b.x - slop && x <= b.x + b.w + slop && y >= b.y - slop && y <= b.y + b.h + slop)
            return i;
    }
    return -1;
}

void publish()
{
    u16 buttons = 0;
    for (const auto& [id, b] : s_fingerBtn)
        if (b >= 0)
            buttons |= kMask[b];
    s8 sx = 0, sy = 0;
    if (s_hasStick)
    {
        float dx = (s_stick.x - s_stick.x0) / stick_radius();
        float dy = (s_stick.y - s_stick.y0) / stick_radius();
        float mag = std::sqrt(dx * dx + dy * dy);
        if (mag > 1.0f)
        {
            dx /= mag;
            dy /= mag;
        }
        if (mag > 0.12f)
        {
            sx = (s8)std::lround(dx * 100.0f);
            sy = (s8)std::lround(-dy * 100.0f); // pad Y is up
        }
    }
    s_buttons = buttons;
    s_sx = sx;
    s_sy = sy;
}

void release_all()
{
    s_hasStick = false;
    s_fingerBtn.clear();
    publish();
}

} // namespace

extern "C" {

void port_touch_init(void)
{
    const char* env = getenv("MSSB_TOUCH");
#if defined(SDL_PLATFORM_IOS) && !defined(SDL_PLATFORM_TVOS) // iPhone (not Apple TV: controllers only)
    s_enabled = env == nullptr || env[0] != '0';
#else
    s_enabled = env != nullptr && env[0] == '1';
#endif
    s_visible = s_enabled;
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
}

// Every SDL event (port/src/vi_frame.cpp handle_events).
void port_touch_event(const SDL_Event* e)
{
    if (!s_enabled)
        return;
    std::lock_guard lk(s_mutex);
    switch (e->type)
    {
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        if (s_visible)
        {
            s_visible = false; // a controller took over
            release_all();
        }
        return;
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        if (s_visible && (e->gaxis.value > 20000 || e->gaxis.value < -20000))
        {
            s_visible = false;
            release_all();
        }
        return;
    case SDL_EVENT_FINGER_DOWN:
    case SDL_EVENT_FINGER_MOTION:
    case SDL_EVENT_FINGER_UP:
    case SDL_EVENT_FINGER_CANCELED:
        break;
    default:
        return;
    }
    const float x = e->tfinger.x * s_winW;
    const float y = e->tfinger.y * s_winH;
    const SDL_FingerID id = e->tfinger.fingerID;
    if (e->type == SDL_EVENT_FINGER_DOWN)
    {
        s_visible = true;
        int b = button_at(x, y);
        if (b >= 0)
            s_fingerBtn[id] = b;
        else if (!s_hasStick && x < s_winW * 0.5f)
        {
            s_hasStick = true;
            s_stick = {id, x, y, x, y};
        }
        else
            s_fingerBtn[id] = -1;
    }
    else if (e->type == SDL_EVENT_FINGER_MOTION)
    {
        if (s_hasStick && s_stick.id == id)
        {
            s_stick.x = x;
            s_stick.y = y;
        }
        else if (auto it = s_fingerBtn.find(id); it != s_fingerBtn.end() && it->second >= 0)
        {
            int b = button_at(x, y);
            if (b >= 0)
                it->second = b; // a thumb can roll from A onto B
        }
    }
    else
    {
        if (s_hasStick && s_stick.id == id)
            s_hasStick = false;
        s_fingerBtn.erase(id);
    }
    publish();
}

// Port 1's pad, after PADRead (port/src/input.cpp port_pad_script).
void port_touch_apply(PADStatus* status)
{
    if (!s_enabled)
        return;
    std::lock_guard lk(s_mutex);
    if (!s_visible)
        return;
    status[0].err = PAD_ERR_NONE; // the touch pad counts as a connected controller
    status[0].button |= s_buttons;
    if (s_sx != 0 || s_sy != 0)
    {
        status[0].stickX = s_sx;
        status[0].stickY = s_sy;
    }
    if (s_buttons & PAD_TRIGGER_L)
        status[0].triggerLeft = 200;
    if (s_buttons & PAD_TRIGGER_R)
        status[0].triggerRight = 200;
}

// Inside the frame, before aurora_end_frame (port/src/vi_frame.cpp).
void port_touch_draw(SDL_Window* win)
{
    if (!s_enabled || win == nullptr)
        return;
    std::lock_guard lk(s_mutex);
    layout(win);
    if (!s_visible)
        return;
    ImDrawList* dl = ImGui::GetForegroundDrawList();
    const ImVec2 disp = ImGui::GetIO().DisplaySize;
    const float kx = disp.x / s_winW, ky = disp.y / s_winH; // window points -> ImGui units
    auto P = [&](float x, float y) { return ImVec2(x * kx, y * ky); };
    ImFont* font = ImGui::GetFont();

    for (int i = 0; i < B_COUNT; i++)
    {
        const Layout& b = s_btn[i];
        const bool down = (s_buttons & kMask[i]) != 0;
        ImU32 c = kColor[i];
        const int alpha = down ? 235 : 120;
        c = (c & 0x00FFFFFF) | ((ImU32)alpha << IM_COL32_A_SHIFT);
        const ImVec2 a = P(b.x, b.y), z = P(b.x + b.w, b.y + b.h);
        const float r = b.round ? (z.x - a.x) * 0.5f : std::fmin(z.x - a.x, z.y - a.y) * 0.5f;
        if (b.round)
        {
            ImVec2 ctr((a.x + z.x) * 0.5f, (a.y + z.y) * 0.5f);
            dl->AddCircleFilled(ctr, r, c, 40);
            dl->AddCircle(ctr, r, IM_COL32(10, 15, 24, alpha), 40, 2.0f);
        }
        else
        {
            dl->AddRectFilled(a, z, c, r);
            dl->AddRect(a, z, IM_COL32(10, 15, 24, alpha), r, 0, 2.0f);
        }
        const float fs = (i == B_START ? 15.0f : (i == B_A ? 30.0f : 20.0f)) * s_unit * ky;
        ImVec2 ts = font->CalcTextSizeA(fs, 1e9f, 0.0f, kLabel[i]);
        dl->AddText(font, fs, ImVec2((a.x + z.x - ts.x) * 0.5f, (a.y + z.y - ts.y) * 0.5f),
                    IM_COL32(255, 255, 255, down ? 255 : 200), kLabel[i]);
    }

    // The stick: where the thumb landed, or a faint hint where it usually goes.
    const float R = stick_radius();
    float bx = s_hasStick ? s_stick.x0 : s_stickHomeX;
    float by = s_hasStick ? s_stick.y0 : s_stickHomeY;
    float kxp = bx, kyp = by;
    if (s_hasStick)
    {
        float dx = s_stick.x - s_stick.x0, dy = s_stick.y - s_stick.y0;
        float mag = std::sqrt(dx * dx + dy * dy);
        if (mag > R)
        {
            dx *= R / mag;
            dy *= R / mag;
        }
        kxp = bx + dx;
        kyp = by + dy;
    }
    const int a = s_hasStick ? 150 : 60;
    dl->AddCircleFilled(P(bx, by), (64.0f * s_unit) * kx, IM_COL32(20, 25, 40, a), 48);
    dl->AddCircle(P(bx, by), (64.0f * s_unit) * kx, IM_COL32(255, 255, 255, a), 48, 2.0f);
    dl->AddCircleFilled(P(kxp, kyp), (30.0f * s_unit) * kx, IM_COL32(220, 225, 235, s_hasStick ? 230 : 90), 32);
}

} // extern "C"
