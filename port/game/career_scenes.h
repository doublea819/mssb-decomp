// Career Mode cutscenes: the script (career_scenes.c) and the ids the Career menu plays.
// Lines are shown in Challenge mode's own talk window (bank 8), one box per line, A to advance.
#pragma once
#include "mssbTypes.h"

// Speaker: a character id (0-53), or one of these.
enum {
    W_END = -100,    // end of a scene
    W_NARR = -1,     // narration: no face
    W_LAKITU = -2,   // the announcer (Challenge mode's Lakitu portrait)
    W_VOICE = -3,    // your captain's voice: Birdo for Yoshi, Diddy for DK, else the captain
    W_CAPTAIN = -4,  // your captain
    W_OPP = -5,      // the opponent's captain (chapter, Cup round, Star Festival invitees)
    W_SUB = -6,      // your team's sub-captain
};

typedef struct SceneLine {
    s16 who;
    const char* text; // {NAME} {BODY} {CAPTAIN} {OPP} {SEED} {ROUND}
} SceneLine;

// Scene ids: kind << 16 | a << 8 | b.
enum {
    SC_NONE = 0,
    SC_TRYOUT = 1,       // before the prologue game
    SC_PICK = 2,         // a = your team (TEAM_*)
    SC_ARRIVE = 3,       // a = your team, b = opponent team
    SC_RESULT = 4,       // a = your team, b = opponent team, won in bit 7 of b
    SC_FEST = 5,         // before the Star Festival
    SC_FEST_END = 6,     // b = won
    SC_BOWSER = 7,       // Bowser crashes the party
    SC_BOWSER_END = 8,   // b = won
    SC_JR = 9,           // Bowser Jr. takes over; b = won the Bowser game
    SC_SEED = 10,        // the Kingdom Cup seed reveal
    SC_ROUND = 11,       // b = 0 quarterfinal, 1 semifinal
    SC_FINAL = 12,       // the final at Bowser Castle
    SC_OVER = 13,        // career over (lost a Cup game)
    SC_CHAMP = 14,       // won the Kingdom Cup; a = your team
    SC_EPILOGUE = 15,    // after the All-Star game
};
#define SCENE_ID(kind, a, b) (((u32)(kind) << 16) | ((u32)(a) << 8) | (u32)(b))

// The lines of a scene (ending with W_END), or NULL when there is none.
const SceneLine* career_scene_lines(u32 id);
