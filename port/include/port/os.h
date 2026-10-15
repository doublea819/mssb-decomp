// PC platform hooks shared between the port layer and patched game code.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Run code in "interrupt context": takes the global interrupt lock on the
// calling thread. Wrap game callbacks invoked from non-game threads with these.
void port_interrupt_enter(void);
void port_interrupt_leave(void);

// Sets up the SDK's low-memory boot globals (bus/core clock). Call once at
// startup, before game code runs.
void port_os_init(void);

// Web builds (single-threaded): queue fn(arg) to run in interrupt context the
// next time interrupts are enabled or the game waits. Natively unused.
void port_raise_interrupt(void (*fn)(void*), void* arg);
// Web builds: run audio DMA periods until the output queue is topped up.
void port_audio_pump(void);
// Web builds: let the browser's event loop run (JSPI suspend).
void port_yield_to_browser(void);

// One VI retrace: runs the retrace callbacks and, if the game finished its
// frame (port_vi_frame_done) since the last present, ends aurora's frame,
// presents it, pumps window events and begins the next (vi_frame.cpp).
void port_present_frame(void);
// The game finished drawing a frame (fn_800A7DB0, before its retrace wait).
void port_vi_frame_done(void);
// The draw thread finished a pass: wait for aurora to consume its draws
// (MSSB_ASYNC_DRAW=1: don't).
void port_draw_pass_done(void);

// Ask the app to exit at the next frame boundary.
void port_request_quit(void);
// Stops the audio thread; call before aurora_shutdown (which destroys the stream).
void port_audio_shutdown(void);

// Crash/hang handling (port/src/crash.cpp).
void port_crash_init(const char* userPath);
void port_crash_heartbeat(void);

// Default keyboard controls if none are saved (port/src/input.cpp).
void port_pad_init_defaults(void);

// The game's PADRead result: MSSB_INPUT scripted presses and the page's touch
// controls added, or in online play the inputs every peer agreed on.
struct PADStatus;
void port_pad_apply_script(struct PADStatus* status);

// Online play (port/web/src/net_web.cpp; stubs elsewhere). port_net_frame runs
// at each frame boundary and blocks until every port's input for the frame is
// known; port_fixed_frame_ms is the dt every task gets in net mode (0: off).
int port_net_active(void);
float port_fixed_frame_ms(void);
void port_net_frame(void);
// Hash of the gameplay state peers must agree on (port/game/net_state.c).
unsigned int port_game_state_hash(unsigned int frame);

#ifdef __cplusplus
}
#endif
