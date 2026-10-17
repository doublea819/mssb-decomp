// Default keyboard controls for port 1 when no bindings have been saved.
#include <dolphin/pad.h>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>

#include <cstdio>
#include <cstdlib>

extern "C" void port_pad_init_defaults(void)
{
    // Initialise aurora's PAD (and load saved bindings) first: its PADInit
    // resets the key mappings, and the game's own PADInit call later is then
    // a no-op that keeps these defaults.
    PADInit();
    u32 count = 0;
    if (PADGetKeyButtonBindings(0, &count) != nullptr)
        return; // user bindings were loaded

    PADKeyButtonBinding buttons[PAD_BUTTON_COUNT] = {
        {SDL_SCANCODE_X, PAD_BUTTON_A},       {SDL_SCANCODE_Z, PAD_BUTTON_B},
        {SDL_SCANCODE_C, PAD_BUTTON_X},       {SDL_SCANCODE_V, PAD_BUTTON_Y},
        {SDL_SCANCODE_RETURN, PAD_BUTTON_START}, {SDL_SCANCODE_LSHIFT, PAD_TRIGGER_Z},
        {SDL_SCANCODE_Q, PAD_TRIGGER_L},      {SDL_SCANCODE_E, PAD_TRIGGER_R},
        {SDL_SCANCODE_I, PAD_BUTTON_UP},      {SDL_SCANCODE_K, PAD_BUTTON_DOWN},
        {SDL_SCANCODE_J, PAD_BUTTON_LEFT},    {SDL_SCANCODE_L, PAD_BUTTON_RIGHT},
    };
    PADKeyAxisBinding axes[PAD_AXIS_COUNT] = {
        {SDL_SCANCODE_RIGHT, PAD_AXIS_LEFT_X_POS, 100}, {SDL_SCANCODE_LEFT, PAD_AXIS_LEFT_X_NEG, 100},
        {SDL_SCANCODE_UP, PAD_AXIS_LEFT_Y_POS, 100},    {SDL_SCANCODE_DOWN, PAD_AXIS_LEFT_Y_NEG, 100},
        {SDL_SCANCODE_D, PAD_AXIS_RIGHT_X_POS, 100},    {SDL_SCANCODE_A, PAD_AXIS_RIGHT_X_NEG, 100},
        {SDL_SCANCODE_W, PAD_AXIS_RIGHT_Y_POS, 100},    {SDL_SCANCODE_S, PAD_AXIS_RIGHT_Y_NEG, 100},
        {SDL_SCANCODE_1, PAD_AXIS_TRIGGER_L, 100},      {SDL_SCANCODE_3, PAD_AXIS_TRIGGER_R, 100},
    };
    PADSetKeyButtonBindings(0, buttons);
    PADSetKeyAxisBindings(0, axes);
    PADSetKeyboardActive(0, TRUE);
    if (getenv("MSSB_DEBUG_INPUT") != nullptr)
        fprintf(stderr, "[input] default keyboard bindings for port 1\n");
}

// Scripted input for testing without a person at the keyboard:
// MSSB_INPUT="300:A,600:START,900:DOWN,950:SLEFT" holds each button (or
// pushes the main stick: SLEFT/SRIGHT/SUP/SDOWN) on port 1 for a few frames,
// starting at the given PADRead call (~frame) number. "START-END/STEP:A"
// repeats the press every STEP frames from START to END.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace {
struct ScriptedPress
{
    u32 frame;
    u16 button;
    s8 stickX;
    s8 stickY;
};

u16 button_from_name(const char* n)
{
    static const struct
    {
        const char* name;
        u16 mask;
    } table[] = {
        {"A", PAD_BUTTON_A},       {"B", PAD_BUTTON_B},       {"X", PAD_BUTTON_X},
        {"Y", PAD_BUTTON_Y},       {"START", PAD_BUTTON_START}, {"Z", PAD_TRIGGER_Z},
        {"L", PAD_TRIGGER_L},      {"R", PAD_TRIGGER_R},      {"UP", PAD_BUTTON_UP},
        {"DOWN", PAD_BUTTON_DOWN}, {"LEFT", PAD_BUTTON_LEFT}, {"RIGHT", PAD_BUTTON_RIGHT},
    };
    for (const auto& e : table)
        if (strcasecmp(n, e.name) == 0)
            return e.mask;
    return 0;
}

std::vector<ScriptedPress>& script()
{
    static std::vector<ScriptedPress> presses = [] {
        std::vector<ScriptedPress> out;
        const char* env = getenv("MSSB_INPUT");
        if (env == nullptr)
            return out;
        static char buf[16384];
        strncpy(buf, env, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';
        for (char* tok = strtok(buf, ","); tok != nullptr; tok = strtok(nullptr, ","))
        {
            char* colon = strchr(tok, ':');
            if (colon == nullptr)
                continue;
            *colon = '\0';
            const char* name = colon + 1;
            s8 sx = 0, sy = 0;
            if (strcasecmp(name, "SLEFT") == 0)
                sx = -100;
            else if (strcasecmp(name, "SRIGHT") == 0)
                sx = 100;
            else if (strcasecmp(name, "SUP") == 0)
                sy = 100;
            else if (strcasecmp(name, "SDOWN") == 0)
                sy = -100;
            u32 start = (u32)atoi(tok);
            u32 end = start;
            u32 step = 1;
            if (const char* dash = strchr(tok, '-'))
            {
                end = (u32)atoi(dash + 1);
                if (const char* slash = strchr(dash, '/'))
                    step = (u32)atoi(slash + 1);
            }
            for (u32 f = start; f <= end && step != 0; f += step)
                out.push_back({f, button_from_name(name), sx, sy});
        }
        return out;
    }();
    return presses;
}
} // namespace


#ifndef __EMSCRIPTEN__
// Online play is browser-only (port/web/src/net_web.cpp).
extern "C" void port_pad_script(PADStatus* status);
extern "C" {
void port_pad_apply_script(PADStatus* status) { port_pad_script(status); }
int port_net_active(void) { return 0; }
float port_fixed_frame_ms(void) { return 0.0f; }
void port_net_frame(void) { }
}
#endif

static u32 s_scriptFrame = 0; // PADRead calls so far: the frame MSSB_INPUT is keyed to

extern "C" u32 port_pad_script_frame(void)
{
    return s_scriptFrame;
}

// MSSB_INPUT presses (online play applies them to the local pad instead, in
// port/web/src/net_web.cpp).
extern "C" void port_touch_apply(PADStatus* status);
extern "C" void port_pad_script(PADStatus* status)
{
    port_touch_apply(status); // on-screen touch controls (port/src/touch.cpp)
    u32 frame = ++s_scriptFrame;
    // MSSB_DEBUG_INPUT: port 1 as the game reads it, whenever it changes.
    static const bool s_debugPad = getenv("MSSB_DEBUG_INPUT") != nullptr;
    static PADStatus s_last;
    if (s_debugPad && (status[0].button != s_last.button || status[0].err != s_last.err ||
                       status[0].stickX / 32 != s_last.stickX / 32 || status[0].stickY / 32 != s_last.stickY / 32))
    {
        fprintf(stderr, "[input] port 1: err %d buttons 0x%04x stick %d,%d c %d,%d trig %u,%u\n", status[0].err,
                status[0].button, status[0].stickX, status[0].stickY, status[0].substickX, status[0].substickY,
                status[0].triggerLeft, status[0].triggerRight);
        s_last = status[0];
    }
    for (const ScriptedPress& p : script())
    {
        if (frame >= p.frame && frame < p.frame + 6)
        {
            status[0].err = PAD_ERR_NONE;
            status[0].button |= p.button;
            if (p.stickX != 0)
                status[0].stickX = p.stickX;
            if (p.stickY != 0)
                status[0].stickY = p.stickY;
            static const bool s_debug = getenv("MSSB_DEBUG_INPUT") != nullptr;
            if (s_debug && frame == p.frame)
                fprintf(stderr, "[input] frame %u press 0x%x\n", frame, p.button);
        }
    }
}

// The first controller a button is pressed on drives port 1, unless the one
// holding port 1 has been used already. SDL hands out player slots in
// connection order, so otherwise a pad that shows up second (a device that
// isn't a real pad took slot 0, or it reconnected while another was listed)
// would only drive port 2.
#include <set>

extern "C" void port_pad_assign(void)
{
    static std::set<SDL_JoystickID> s_used;
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    if (ids == nullptr)
        return;
    SDL_Gamepad* port1 = nullptr;
    SDL_Gamepad* pressed = nullptr;
    for (int i = 0; i < count; i++)
    {
        SDL_Gamepad* pad = SDL_GetGamepadFromID(ids[i]);
        if (pad == nullptr)
            continue;
        if (SDL_GetGamepadPlayerIndex(pad) == 0)
            port1 = pad;
        if (s_used.count(ids[i]) != 0)
            continue;
        for (int b = 0; b < SDL_GAMEPAD_BUTTON_COUNT; b++)
        {
            if (SDL_GetGamepadButton(pad, (SDL_GamepadButton)b))
            {
                s_used.insert(ids[i]);
                if (pressed == nullptr)
                    pressed = pad;
                break;
            }
        }
    }
    SDL_free(ids);
    if (pressed == nullptr || pressed == port1 ||
        (port1 != nullptr && s_used.count(SDL_GetGamepadID(port1)) != 0))
        return;
    int old = SDL_GetGamepadPlayerIndex(pressed);
    if (port1 != nullptr)
        SDL_SetGamepadPlayerIndex(port1, old);
    SDL_SetGamepadPlayerIndex(pressed, 0);
    fprintf(stderr, "[input] '%s' now drives port 1 (was port %d)\n", SDL_GetGamepadName(pressed), old + 1);
}
