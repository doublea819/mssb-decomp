// Career Mode (PC): takes over the main menu's Challenge entry.
//
// Picking it sets up the next career game the way port/game/skipfe.c does
// (both teams' rosters, captains, stadium, ports) and loads game.rel straight
// from the main menu. When the game ends (fn_3_76558, the end-of-game
// bookkeeping), the box score is read from main.dol's records, scored into
// iWAR (your player's line) and tWAR (the team), and the career advances.
//
// State lives in <user data folder>/career.sav (key = value text) and every
// game's recap is appended to career_log.txt there and printed with [career].
//
// user.ini:
//   career_body = toad      your player's character (a color-variant family)
//   career_innings = 3      innings per career game (default: the saved option)
//   career_reset = true     start a new career on the next boot
// Design: "Mario Superstar Baseball: Career Mode v2" (docs/career/).
#include "mssbTypes.h"
#include "static/GameSettings.h"
#include "game/character_stats.h"
#include "main/charsel_state_type.h"
#include "main/menu_globals.h" // SavedSettings
#include "game/auto_00_000759BC_text.h" // BattingRecord, PitchingRecord, LineScore

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

extern CharSelectState lbl_8034E9A0;
extern CharacterStats inMemRoster[2][9];
extern SavedSettings lbl_800E8754;
extern void fn_2_2FC0(u8 mode, s32 b, s32 c); // menus: build both teams
extern u8 lbl_80108ED0[12];                 // captain character ids (logo order)
extern BattingRecord lbl_803537E4[2][9];
extern PitchingRecord lbl_803535C8[2][9];
extern LineScore lbl_80353A90;

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);
const char* port_user_path(void);

// ---------------------------------------------------------------- data
enum { TEAM_MARIO, TEAM_PEACH, TEAM_WARIO, TEAM_DK, TEAM_YOSHI, TEAM_BOWSER, TEAM_COUNT };
static const char* const sTeamName[TEAM_COUNT] = {"Mario", "Peach", "Wario", "DK", "Yoshi", "Bowser"};
static const s32 sTeamCaptain[TEAM_COUNT] = {CHAR_ID_MARIO, CHAR_ID_PEACH, CHAR_ID_WARIO,
                                             CHAR_ID_DK, CHAR_ID_YOSHI, CHAR_ID_BOWSER};
// Preset index of each team in lbl_8034E9A0.presets (order of lbl_80108EC4).
static const s32 sTeamPreset[TEAM_COUNT] = {0, 1, 2, 3, 4, 5};
static const s32 sTeamStadium[TEAM_COUNT] = {STADIUM_ID_MARIO_STADIUM, STADIUM_ID_PEACH_GARDEN,
                                             STADIUM_ID_WARIO_PALACE,  STADIUM_ID_DK_JUNGLE,
                                             STADIUM_ID_YOHSI_PARK,    STADIUM_ID_BOWSERS_CASTLE};
// Chapter order (your own captain's chapter is skipped).
static const s32 sChapterOrder[5] = {TEAM_YOSHI, TEAM_PEACH, TEAM_MARIO, TEAM_DK, TEAM_WARIO};

// Tier 1 generic variants (CHARACTER_VARIANT_CLASSIFICATION 3/4), for the prologue teams.
static const s32 sProloguePool[] = {
    CHAR_ID_SHYGUY_RED,     CHAR_ID_KOOPA_GREEN,   CHAR_ID_PIANTA_BLUE,   CHAR_ID_NOKI_BLUE,
    CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_DRYBONES_GRAY, CHAR_ID_PARATROOPA_RED, CHAR_ID_TOAD_YELLOW,
    CHAR_ID_SHYGUY_BLUE,    CHAR_ID_KOOPA_RED,     CHAR_ID_NOKI_RED,      CHAR_ID_MAGIKOOPA_RED,
    CHAR_ID_DRYBONES_GREEN, CHAR_ID_BRO_HAMMER,    CHAR_ID_PIANTA_RED,    CHAR_ID_TOAD_GREEN,
    CHAR_ID_PARATROOPA_GREEN, CHAR_ID_SHYGUY_GREEN, CHAR_ID_NOKI_GREEN,   CHAR_ID_DRYBONES_RED,
};

static const char* const sBodyNames[] = {"toad", "toadblue", "toadyellow", "toadgreen", "toadpurple", "shyguy",
                                         "shyguyblue", "shyguyyellow", "shyguygreen", "shyguyblack", "koopa",
                                         "koopared", "paratroopa", "paratroopagreen", "piantablue", "piantared",
                                         "piantayellow", "nokiblue", "nokired", "nokigreen", "hammerbro",
                                         "firebro", "boomerangbro", "magikoopablue", "magikoopared",
                                         "magikoopagreen", "magikoopayellow", "drybonesgray", "drybonesgreen",
                                         "drybonesred", "drybonesblue"};
static const s32 sBodyIds[] = {CHAR_ID_TOAD_RED, CHAR_ID_TOAD_BLUE, CHAR_ID_TOAD_YELLOW, CHAR_ID_TOAD_GREEN,
                               CHAR_ID_TOAD_PURPLE, CHAR_ID_SHYGUY_RED, CHAR_ID_SHYGUY_BLUE, CHAR_ID_SHYGUY_YELLOW,
                               CHAR_ID_SHYGUY_GREEN, CHAR_ID_SHYGUY_BLACK, CHAR_ID_KOOPA_GREEN, CHAR_ID_KOOPA_RED,
                               CHAR_ID_PARATROOPA_RED, CHAR_ID_PARATROOPA_GREEN, CHAR_ID_PIANTA_BLUE,
                               CHAR_ID_PIANTA_RED, CHAR_ID_PIANTA_YELLOW, CHAR_ID_NOKI_BLUE, CHAR_ID_NOKI_RED,
                               CHAR_ID_NOKI_GREEN, CHAR_ID_BRO_HAMMER, CHAR_ID_BRO_FIRE, CHAR_ID_BRO_BOOMERANG,
                               CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_MAGIKOOPA_RED, CHAR_ID_MAGIKOOPA_GREEN,
                               CHAR_ID_MAGIKOOPA_YELLOW, CHAR_ID_DRYBONES_GRAY, CHAR_ID_DRYBONES_GREEN,
                               CHAR_ID_DRYBONES_RED, CHAR_ID_DRYBONES_BLUE};

// ---------------------------------------------------------------- state
enum { STAGE_PROLOGUE = 0, STAGE_CHAPTERS = 1, STAGE_SEASON_DONE = 9 };

enum { SB_G, SB_PA, SB_AB, SB_H, SB_2B, SB_3B, SB_HR, SB_RBI, SB_R, SB_BB, SB_HBP, SB_K, SB_SB, SB_COUNT };
enum { SP_G, SP_OUTS, SP_K, SP_BB, SP_H, SP_R, SP_ER, SP_HR, SP_COUNT };

typedef struct CareerState {
    s32 stage;         // STAGE_*
    s32 chapter;       // index into the chapters you play (0..3)
    s32 game;          // game within the chapter (0..2)
    s32 body;          // your character id
    s32 team;          // TEAM_* (-1 until the prologue picks a captain)
    s32 roster[9];     // your team, slot 0 = captain
    s32 pointsEarned;  // attribute points earned so far
    s32 wins, losses, ties;
    f32 chapterIwar, chapterTwar;
    s32 chapterWins;
    s32 gamesPlayed;
    // Player creation (Career menu)
    s32 created;       // player created
    char name[12];
    s32 star;          // index into sStarNames (whose captain star you use)
    s32 bars[4];       // Batting, Pitching, Fielding, Speed (1-10)
    s32 pointsSpent;   // attribute points applied so far
    s32 innings;       // career game length (Settings)
    // Lineup and Positions (the game's lineup screen): your team in batting order and each
    // batter's lbl_80354720 entry (order row, field position). Used while the 9 players match.
    s32 lineupSet;
    s32 lineupIds[9];
    s32 lineupOrd[9][4];
    // Your season (regular-season games): batting and pitching totals, and the last game's lines.
    s32 bat[SB_COUNT];
    s32 pit[SP_COUNT];
    char last[3][48];
    f32 seasonIwar, seasonTwar; // regular season totals
    f32 lastIwar, lastTwar;     // the last game
    s32 hasLast;
    // Bat / throw hand (0 right, 1 left; -1: the body's own), and each lineup player's.
    s32 bats, throws;
    s32 lineupHand[9]; // BattingStance + FieldingArm * 2
} CareerState;

static CareerState sCareer;
static s32 sLoaded;
static s32 sArmed;        // a career game was set up and hasn't been scored yet
static s32 sMySlot = -1;  // your roster slot in the armed game
static s32 sOppTeam = -1; // opponent TEAM_* (-1: prologue)

static void career_path(char* out, size_t n, const char* file) {
    const char* dir = port_user_path();
    snprintf(out, n, "%s/%s", (dir != NULL && dir[0] != '\0') ? dir : ".", file);
}

static s32 lookup_body(const char* v) {
    s32 i;
    if (v == NULL) {
        return CHAR_ID_TOAD_RED;
    }
    for (i = 0; i < (s32)(sizeof(sBodyNames) / sizeof(sBodyNames[0])); i++) {
        if (strcasecmp(v, sBodyNames[i]) == 0) {
            return sBodyIds[i];
        }
    }
    fprintf(stderr, "[career] unknown career_body '%s', using Toad\n", v);
    return CHAR_ID_TOAD_RED;
}

static void career_new(void) {
    s32 i;
    memset(&sCareer, 0, sizeof(sCareer));
    sCareer.stage = STAGE_PROLOGUE;
    sCareer.team = -1;
    sCareer.body = lookup_body(port_user_ini_get("career_body"));
    for (i = 0; i < 9; i++) {
        sCareer.roster[i] = -1;
    }
    sCareer.innings = 0; // 0: the saved game option
    sCareer.bats = sCareer.throws = -1;
    snprintf(sCareer.name, sizeof(sCareer.name), "ROOKIE");
}

static void career_save(void) {
    char path[1024];
    FILE* f;
    s32 i;
    career_path(path, sizeof(path), "career.sav");
    f = fopen(path, "w");
    if (f == NULL) {
        fprintf(stderr, "[career] can't write %s\n", path);
        return;
    }
    {
        static s32 s_told;
        if (!s_told) {
            s_told = 1;
            fprintf(stderr, "[career] save file: %s\n", path);
        }
    }
    fprintf(f, "version = 1\nstage = %d\nchapter = %d\ngame = %d\nbody = %d\nteam = %d\nroster =", sCareer.stage,
            sCareer.chapter, sCareer.game, sCareer.body, sCareer.team);
    for (i = 0; i < 9; i++) {
        fprintf(f, " %d", sCareer.roster[i]);
    }
    fprintf(f, "\npoints = %d\nwins = %d\nlosses = %d\nties = %d\nchapter_iwar = %.2f\nchapter_twar = %.2f\n"
               "chapter_wins = %d\ngames = %d\n",
            sCareer.pointsEarned, sCareer.wins, sCareer.losses, sCareer.ties, sCareer.chapterIwar, sCareer.chapterTwar,
            sCareer.chapterWins, sCareer.gamesPlayed);
    fprintf(f, "created = %d\nname = %s\nstar = %d\nbars = %d %d %d %d\nspent = %d\ninnings = %d\n", sCareer.created,
            sCareer.name, sCareer.star, sCareer.bars[0], sCareer.bars[1], sCareer.bars[2], sCareer.bars[3],
            sCareer.pointsSpent, sCareer.innings);
    fprintf(f, "season_bat =");
    for (i = 0; i < SB_COUNT; i++) fprintf(f, " %d", sCareer.bat[i]);
    fprintf(f, "\nseason_pit =");
    for (i = 0; i < SP_COUNT; i++) fprintf(f, " %d", sCareer.pit[i]);
    fprintf(f, "\nlast1 = %s\nlast2 = %s\nlast3 = %s\n", sCareer.last[0], sCareer.last[1], sCareer.last[2]);
    fprintf(f, "war = %.2f %.2f %.2f %.2f %d\nhands = %d %d\n", sCareer.seasonIwar, sCareer.seasonTwar,
            sCareer.lastIwar, sCareer.lastTwar, sCareer.hasLast, sCareer.bats, sCareer.throws);
    if (sCareer.lineupSet) {
        fprintf(f, "lineup =");
        for (i = 0; i < 9; i++) {
            fprintf(f, " %d:%d:%d:%d:%d:%d", sCareer.lineupIds[i], sCareer.lineupOrd[i][0], sCareer.lineupOrd[i][1],
                    sCareer.lineupOrd[i][2], sCareer.lineupOrd[i][3], sCareer.lineupHand[i]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

static void career_load(void) {
    char path[1024];
    char line[256];
    FILE* f;
    if (sLoaded) {
        return;
    }
    sLoaded = 1;
    career_new();
    if (port_user_ini_bool("career_reset") || (getenv("MSSB_CAREER_RESET") != NULL)) {
        fprintf(stderr, "[career] career_reset: starting over\n");
        career_save();
        return;
    }
    career_path(path, sizeof(path), "career.sav");
    f = fopen(path, "r");
    if (f == NULL) {
        return;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
        char* eq = strchr(line, '=');
        char* key = line;
        char* val;
        if (eq == NULL) {
            continue;
        }
        *eq = '\0';
        val = eq + 1;
        while (*key == ' ') key++;
        {
            char* e = key + strlen(key);
            while (e > key && e[-1] == ' ') *--e = '\0';
        }
#define K(name) (strcmp(key, name) == 0)
        if (K("stage")) sCareer.stage = atoi(val);
        else if (K("chapter")) sCareer.chapter = atoi(val);
        else if (K("game")) sCareer.game = atoi(val);
        else if (K("body")) sCareer.body = atoi(val);
        else if (K("team")) sCareer.team = atoi(val);
        else if (K("points")) sCareer.pointsEarned = atoi(val);
        else if (K("wins")) sCareer.wins = atoi(val);
        else if (K("losses")) sCareer.losses = atoi(val);
        else if (K("ties")) sCareer.ties = atoi(val);
        else if (K("chapter_iwar")) sCareer.chapterIwar = (f32)atof(val);
        else if (K("chapter_twar")) sCareer.chapterTwar = (f32)atof(val);
        else if (K("chapter_wins")) sCareer.chapterWins = atoi(val);
        else if (K("games")) sCareer.gamesPlayed = atoi(val);
        else if (K("created")) sCareer.created = atoi(val);
        else if (K("star")) sCareer.star = atoi(val);
        else if (K("spent")) sCareer.pointsSpent = atoi(val);
        else if (K("innings")) sCareer.innings = atoi(val);
        else if (K("bars")) sscanf(val, "%d %d %d %d", &sCareer.bars[0], &sCareer.bars[1], &sCareer.bars[2], &sCareer.bars[3]);
        else if (K("name")) {
            char* v = val;
            char* e;
            while (*v == ' ') v++;
            e = v + strlen(v);
            while (e > v && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' ')) *--e = '\0';
            snprintf(sCareer.name, sizeof(sCareer.name), "%s", v);
        }
        else if (K("war")) {
            sscanf(val, "%f %f %f %f %d", &sCareer.seasonIwar, &sCareer.seasonTwar, &sCareer.lastIwar, &sCareer.lastTwar,
                   &sCareer.hasLast);
        }
        else if (K("hands")) sscanf(val, "%d %d", &sCareer.bats, &sCareer.throws);
        else if (K("season_bat") || K("season_pit")) {
            s32* dst = K("season_bat") ? sCareer.bat : sCareer.pit;
            s32 n = K("season_bat") ? SB_COUNT : SP_COUNT;
            char* q = val;
            s32 i;
            for (i = 0; i < n; i++) dst[i] = (s32)strtol(q, &q, 10);
        }
        else if (K("last1") || K("last2") || K("last3")) {
            char* v = val;
            char* e;
            s32 idx = key[4] - '1';
            while (*v == ' ') v++;
            e = v + strlen(v);
            while (e > v && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' ')) *--e = '\0';
            snprintf(sCareer.last[idx], sizeof(sCareer.last[0]), "%s", v);
        }
        else if (K("lineup")) {
            char* p = val;
            s32 i;
            s32 ok = 1;
            for (i = 0; i < 9 && ok; i++) {
                s32* o = sCareer.lineupOrd[i];
                s32 got = sscanf(p, " %d:%d:%d:%d:%d:%d", &sCareer.lineupIds[i], &o[0], &o[1], &o[2], &o[3],
                                 &sCareer.lineupHand[i]);
                if (got == 5) sCareer.lineupHand[i] = -1;
                ok = got >= 5;
                while (*p == ' ') p++;
                while (*p != ' ' && *p != '\0' && *p != '\n') p++;
            }
            sCareer.lineupSet = ok;
        }
        else if (K("roster")) {
            char* p = val;
            s32 i;
            for (i = 0; i < 9; i++) {
                sCareer.roster[i] = (s32)strtol(p, &p, 10);
            }
        }
#undef K
    }
    fclose(f);
    fprintf(stderr, "[career] loaded: stage %d chapter %d game %d team %d points %d (%d-%d)\n", sCareer.stage,
            sCareer.chapter, sCareer.game, sCareer.team, sCareer.pointsEarned, sCareer.wins, sCareer.losses);
}

// The last career game's recap, shown on the Career menu.
static char sRecap[6][80];
static s32 sRecapCount;

static void recap(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

static void career_log(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
#include <stdarg.h>
static void career_log(const char* fmt, ...) {
    char path[1024];
    char buf[512];
    va_list ap;
    FILE* f;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    fprintf(stderr, "[career] %s\n", buf);
    career_path(path, sizeof(path), "career_log.txt");
    f = fopen(path, "a");
    if (f != NULL) {
        fprintf(f, "%s\n", buf);
        fclose(f);
    }
}

static void recap(const char* fmt, ...) {
    va_list ap;
    if (sRecapCount >= 6) {
        return;
    }
    va_start(ap, fmt);
    vsnprintf(sRecap[sRecapCount], sizeof(sRecap[0]), fmt, ap);
    va_end(ap);
    sRecapCount++;
}

// The chapters you play, in order (your own captain's is skipped).
static s32 career_chapter_team(s32 n) {
    s32 i;
    s32 k = 0;
    for (i = 0; i < 5; i++) {
        if (sChapterOrder[i] == sCareer.team) {
            continue;
        }
        if (k == n) {
            return sChapterOrder[i];
        }
        k++;
    }
    return -1;
}

static s32 preset_char(s32 team, s32 i) {
    u8 id = lbl_8034E9A0.presets[sTeamPreset[team]][i];
    return lbl_8034E9A0.roster[id / 9][id % 9].stats.CharID;
}

// ---------------------------------------------------------------- menu hooks
s32 port_career_enabled(void) {
    return 1;
}

// Writes team t explicitly: the captain in slot 0 (where the menus' team builder puts the
// captain, fn_2_C7DC) and `ids` in slots 1-8. The builder's own picks only supply field
// positions and the batting order.
static void place_team(s32 t, s32 captain, const s32* ids, s32 count) {
    s32 slot;
    inMemRoster[t][0] = lbl_8034E9A0.roster[captain / 9][captain % 9];
    for (slot = 1; slot < 9; slot++) {
        s32 id = (slot - 1 < count) ? ids[slot - 1] : ids[0];
        inMemRoster[t][slot] = lbl_8034E9A0.roster[id / 9][id % 9];
    }
    lbl_8034E9A0.captainSlot[t] = 0;
}

extern void characterSelectScreen(u8 team);
extern void fn_80069854(void);
extern u8 lbl_80354720[2][9][4]; // OrderEntry (main/file_8004207C.h)

// The 9 players of your team in the set-up game match the saved lineup's.
static s32 lineup_matches(void) {
    s32 i;
    s32 k;
    if (!sCareer.lineupSet) {
        return 0;
    }
    for (i = 0; i < 9; i++) {
        s32 found = 0;
        for (k = 0; k < 9; k++) {
            found |= inMemRoster[0][k].stats.CharID == sCareer.lineupIds[i];
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

// Your team in the saved batting order with the saved field positions.
static void apply_lineup(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        s32 id = sCareer.lineupIds[i];
        s32 k;
        inMemRoster[0][i] = lbl_8034E9A0.roster[id / 9][id % 9];
        if (sCareer.lineupHand[i] >= 0) {
            inMemRoster[0][i].stats.BattingStance = (u8)(sCareer.lineupHand[i] % 2);
            inMemRoster[0][i].stats.FieldingArm = (u8)(sCareer.lineupHand[i] / 2);
        }
        for (k = 0; k < 4; k++) {
            lbl_80354720[0][i][k] = (u8)sCareer.lineupOrd[i][k];
        }
    }
}

static BOOL setup_game(s32 arm);

// Main menu, Career picked: set up the next career game. Returns TRUE when a game is set up.
BOOL port_career_setup_next_game(void) {
    return setup_game(1);
}

static BOOL setup_game(s32 arm) {
    s32 mine[8];
    s32 opp[8];
    s32 nMine = 0;
    s32 nOpp = 0;
    s32 i;
    s32 t;
    s32 stadium;

    career_load();
    if (sCareer.stage == STAGE_SEASON_DONE) {
        // The Star Festival, Bowser game and Kingdom Cup aren't built yet: keep the finished season
        // as career_done.sav and start a new career.
        char from[1024];
        char to[1024];
        career_path(from, sizeof(from), "career.sav");
        career_path(to, sizeof(to), "career_done.sav");
        rename(from, to);
        career_log("Season finished (%d-%d-%d, %d attribute points); saved as career_done.sav. Starting a new career.",
                   sCareer.wins, sCareer.losses, sCareer.ties, sCareer.pointsEarned);
        career_new();
        career_save();
    }

    if (sCareer.stage == STAGE_PROLOGUE) {
        // Tryout at Mario Stadium: you and 8 generics vs Bowser Jr. and 8 generics.
        s32 p = 0;
        lbl_8034E9A0.captain[0] = sCareer.body;
        lbl_8034E9A0.captain[1] = CHAR_ID_BOWSERJR;
        for (i = 0; i < (s32)(sizeof(sProloguePool) / sizeof(sProloguePool[0])) && (nMine < 8 || nOpp < 8); i++) {
            s32 id = sProloguePool[i];
            if (id == sCareer.body) {
                continue;
            }
            if ((p++ & 1) == 0 && nMine < 8) {
                mine[nMine++] = id;
            } else if (nOpp < 8) {
                opp[nOpp++] = id;
            } else {
                mine[nMine++] = id;
            }
        }
        stadium = STADIUM_ID_MARIO_STADIUM;
        sOppTeam = -1;
    } else {
        s32 opponent = career_chapter_team(sCareer.chapter);
        lbl_8034E9A0.captain[0] = sTeamCaptain[sCareer.team];
        lbl_8034E9A0.captain[1] = sTeamCaptain[opponent];
        for (i = 1; i < 9; i++) {
            mine[nMine++] = sCareer.roster[i];
        }
        for (i = 0; i < 9; i++) {
            s32 id = preset_char(opponent, i);
            if (id != sTeamCaptain[opponent]) {
                opp[nOpp++] = id;
            }
        }
        // Your character can't be on both teams: the opponent fields an unused generic instead
        // (Yoshi's team is all five Shy Guys, for example).
        for (i = 0; i < nOpp; i++) {
            if (opp[i] == sCareer.body) {
                s32 k;
                for (k = 0; k < (s32)(sizeof(sProloguePool) / sizeof(sProloguePool[0])); k++) {
                    s32 cand = sProloguePool[k];
                    s32 j;
                    s32 used = 0;
                    for (j = 0; j < nOpp; j++) used |= opp[j] == cand;
                    for (j = 1; j < 9; j++) used |= sCareer.roster[j] == cand;
                    if (!used && cand != sCareer.body) {
                        opp[i] = cand;
                        break;
                    }
                }
            }
        }
        stadium = sTeamStadium[opponent];
        sOppTeam = opponent;
    }

    // Build both teams the menus' way (positions, batting order), then put our players in.
    {
        // The team builder rewrites captain[] (it came back as Mario for both teams), so keep ours.
        s32 cap0 = lbl_8034E9A0.captain[0];
        s32 cap1 = lbl_8034E9A0.captain[1];
        // Out of Challenge mode first: in mode 5 the builder takes both captains (and with them the
        // team logos, fn_800678CC) from the Challenge save.
        g_d_GameSettings.GameModeSelected = GAME_TYPE_EXHIBITION_GAME;
        g_d_GameSettings.exhibitionMatchInd = 1;
        fn_2_2FC0(10, 0, 1);
        place_team(0, cap0, mine, nMine);
        place_team(1, cap1, opp, nOpp);
        lbl_8034E9A0.captain[0] = cap0;
        lbl_8034E9A0.captain[1] = cap1;
        // Field positions by class, as the game assigns them after team select (it also orders the
        // roster by position); then your own saved order and positions, while the 9 still match.
        characterSelectScreen(0);
        characterSelectScreen(1);
        if (lineup_matches()) {
            apply_lineup();
        }
        fn_80069854(); // captain slots
        // Team logo: captainVariant = captain index (lbl_80108ED0) * 4 + variant. A generic
        // tryout captain has no logo of its own; it uses Mario's (the host).
        for (t = 0; t < 2; t++) {
            s32 cap = t == 0 ? cap0 : cap1;
            s32 k;
            s32 known = 0;
            for (k = 0; k < 12; k++) {
                if (lbl_80108ED0[k] == cap) {
                    known = 1;
                }
            }
            if (!known) {
                for (k = 0; k < 12; k++) {
                    if (lbl_80108ED0[k] == CHAR_ID_MARIO) {
                        lbl_8034E9A0.captainVariant[t] = (s8)((k + 1) * 4 - 1);
                    }
                }
            }
        }
    }
    sMySlot = -1;
    for (i = 0; i < 9; i++) {
        if (inMemRoster[0][i].stats.CharID == sCareer.body) {
            sMySlot = i;
        }
    }
    // Your bat / throw hands (Create Your Player), unless the lineup screen set them since.
    if (sMySlot >= 0 && !lineup_matches()) {
        if (sCareer.bats >= 0) inMemRoster[0][sMySlot].stats.BattingStance = (u8)sCareer.bats;
        if (sCareer.throws >= 0) inMemRoster[0][sMySlot].stats.FieldingArm = (u8)sCareer.throws;
    }
    for (t = 0; t < 2; t++) {
        char buf[128];
        s32 n = 0;
        for (i = 0; i < 9; i++) {
            n += snprintf(buf + n, sizeof(buf) - n, " %d", inMemRoster[t][i].stats.CharID);
        }
        fprintf(stderr, "[career] team %d:%s\n", t, buf);
    }

    lbl_8034E9A0.ports[0] = 0;
    lbl_8034E9A0.ports[1] = 0xFF;
    lbl_8034E9A0.ports[2] = 0xFF;
    lbl_8034E9A0.ports[3] = 0xFF;
    g_d_GameSettings.GameModeSelected = GAME_TYPE_EXHIBITION_GAME;
    g_d_GameSettings.exhibitionMatchInd = 1;
    g_d_GameSettings.StadiumID = stadium;
    g_d_GameSettings.humanTeamNumber = 1;
    g_d_GameSettings.PlayerPorts[0] = 0;
    g_d_GameSettings.PlayerPorts[1] = 4; // CPU
    g_d_GameSettings._10 = 0;            // human vs CPU: you control your whole team
    // The team index that bats first (fn_3_5A87C: teamBatting = home_AwaySetting). You're the visitor
    // at the tryout and at every chapter game (their park), so you bat first.
    g_d_GameSettings.home_AwaySetting = 0;
    {
        const char* v = port_user_ini_get("career_innings");
        if (sCareer.innings >= 1 && sCareer.innings <= 9) {
            lbl_800E8754.innings = (u8)sCareer.innings; // Career menu > Settings
        } else if (v != NULL && atoi(v) >= 1 && atoi(v) <= 9) {
            lbl_800E8754.innings = (u8)atoi(v);
        }
    }
    if (!arm) {
        return TRUE; // the Lineup / Positions pages: the teams only
    }
    sArmed = 1;
    if (sCareer.stage == STAGE_PROLOGUE) {
        career_log("Prologue: the tryout at Mario Stadium. Bowser Jr. is here. You are slot %d.", sMySlot);
    } else {
        career_log("Chapter %d (%s's team), game %d of 3, at their stadium. You are slot %d.", sCareer.chapter + 1,
                   sTeamName[sOppTeam], sCareer.game + 1, sMySlot);
    }
    return TRUE;
}

// ---------------------------------------------------------------- scoring
typedef struct GameScore {
    f32 iwar, twar;
    s32 positives; // hits, walks, HBP, RBI, runs (prologue DK rule)
    s32 won;       // 1 win, 0 loss, 2 tie
    s32 runsFor, runsAgainst;
} GameScore;

static GameScore score_game(s32 slot) {
    GameScore g;
    const BattingRecord* b;
    const PitchingRecord* p;
    f32 bat;
    s32 i;
    s32 teamHr = 0;
    memset(&g, 0, sizeof(g));
    g.runsFor = lbl_80353A90.runs[0][0];
    g.runsAgainst = lbl_80353A90.runs[1][0];
    g.won = lbl_80353A90.winner == 0 ? 1 : (lbl_80353A90.winner == 1 ? 0 : 2);
    for (i = 0; i < 9; i++) {
        teamHr += lbl_803537E4[0][i].homeRuns;
    }
    if (slot >= 0) {
        b = &lbl_803537E4[0][slot];
        p = &lbl_803535C8[0][slot];
        bat = b->singles * 1.0f + b->doubles * 2.0f + b->triples * 3.0f + b->homeRuns * 4.0f +
              (b->walks + b->hitByPitch) * 0.5f + b->runs * 1.0f + b->rbi * 1.0f - b->strikeouts * 1.0f;
        if (b->plateAppearances > 0) {
            bat = bat * 4.0f / (f32)b->plateAppearances; // scaled to 4 plate appearances
        }
        g.iwar = bat;
        if (lbl_80353A90.mvp[0] == slot) {
            g.iwar += 1.0f;
        }
        if (p->played && p->battersFaced > 0) {
            g.iwar += p->outsPitched * 0.33f + p->strikeouts * 0.5f + p->wins * 1.0f -
                      (p->hitsAllowed + p->walks) * 0.5f - p->homeRunsAllowed * 1.5f - p->_04 * 1.0f;
        }
        g.positives = b->hits + b->walks + b->hitByPitch + b->rbi + b->runs;
        // Last game's lines (Career menu) and the season totals (regular season only).
        {
            char* l = sCareer.last[1];
            size_t cap = sizeof(sCareer.last[1]);
            size_t n;
            snprintf(l, cap, "%d-%d", b->hits, b->atBats);
#define PART(cnt, tag)                                                                   \
    do {                                                                                 \
        n = strlen(l);                                                                   \
        if ((cnt) == 1) snprintf(l + n, cap - n, ", %s", tag);                           \
        else if ((cnt) > 1) snprintf(l + n, cap - n, ", %d %s", (s32)(cnt), tag);        \
    } while (0)
            PART(b->doubles, "2B");
            PART(b->triples, "3B");
            PART(b->homeRuns, "HR");
            PART(b->runs, "R");
            PART(b->rbi, "RBI");
            PART(b->walks + b->hitByPitch, "BB");
            PART(b->_12, "SB");
#undef PART
            if (p->played && p->battersFaced > 0) {
                snprintf(sCareer.last[2], sizeof(sCareer.last[2]), "%d.%d IP, %d K, %d R", p->outsPitched / 3,
                         p->outsPitched % 3, p->strikeouts, p->_02);
            } else {
                sCareer.last[2][0] = '\0';
            }
            if (sCareer.stage == STAGE_CHAPTERS) {
                s32* t = sCareer.bat;
                t[SB_G]++;
                t[SB_PA] += b->plateAppearances;
                t[SB_AB] += b->atBats;
                t[SB_H] += b->hits;
                t[SB_2B] += b->doubles;
                t[SB_3B] += b->triples;
                t[SB_HR] += b->homeRuns;
                t[SB_RBI] += b->rbi;
                t[SB_R] += b->runs;
                t[SB_BB] += b->walks;
                t[SB_HBP] += b->hitByPitch;
                t[SB_K] += b->strikeouts;
                t[SB_SB] += b->_12;
                if (p->played && p->battersFaced > 0) {
                    s32* q = sCareer.pit;
                    q[SP_G]++;
                    q[SP_OUTS] += p->outsPitched;
                    q[SP_K] += p->strikeouts;
                    q[SP_BB] += p->walks;
                    q[SP_H] += p->hitsAllowed;
                    q[SP_R] += p->_02;
                    q[SP_ER] += p->_04;
                    q[SP_HR] += p->homeRunsAllowed;
                }
            }
        }
        career_log("  You: %d PA, %d H (%d 2B, %d 3B, %d HR), %d RBI, %d R, %d BB, %d K%s", b->plateAppearances,
                   b->hits, b->doubles, b->triples, b->homeRuns, b->rbi, b->runs, b->walks, b->strikeouts,
                   lbl_80353A90.mvp[0] == slot ? ", game MVP" : "");
        recap("You: %d-%d  %d RBI  %d R%s", b->hits, b->atBats, b->rbi, b->runs,
              lbl_80353A90.mvp[0] == slot ? "  MVP" : "");
        if (p->played && p->battersFaced > 0) {
            recap("Pitching: %d.%d IP  %d K  %d H  %d ER", p->outsPitched / 3, p->outsPitched % 3, p->strikeouts,
                  p->hitsAllowed, p->_04);
            career_log("  Pitching: %d outs, %d K, %d H, %d BB, %d HR, %d ER", p->outsPitched, p->strikeouts,
                       p->hitsAllowed, p->walks, p->homeRunsAllowed, p->_04);
        }
    }
    g.twar = (g.won == 1 ? 3.0f : (g.won == 0 ? -1.0f : 0.0f)) + 0.25f * (f32)(g.runsFor - g.runsAgainst) -
             0.5f * lbl_80353A90.errors[0] + 0.25f * (f32)teamHr;
    return g;
}

// Thresholds are for 9-inning games; shorter games scale them down (at most to a third).
static f32 length_scale(void) {
    f32 n = (f32)lbl_800E8754.innings;
    if (n < 3.0f) n = 3.0f;
    if (n > 9.0f) n = 9.0f;
    return n / 9.0f;
}

static s32 chapter_points(f32 iwar) {
    f32 k = length_scale();
    if (iwar >= 18.0f * k) return 4;
    if (iwar >= 12.0f * k) return 3;
    if (iwar >= 7.0f * k) return 2;
    if (iwar >= 3.0f * k) return 1;
    return 0;
}

static const char* recruit_tier(f32 twar) {
    f32 k = length_scale();
    if (twar >= 9.0f) return "up to Tier 3 (sub-captain)"; // wins dominate tWAR; not scaled
    if (twar >= 4.0f) return "up to Tier 2 (unique player)";
    (void)k;
    if (twar >= 0.0f) return "Tier 1 (generic)";
    return "no recruit";
}

// Best bar of your player: 0 batting, 1 pitching, 2 fielding, 3 speed.
static s32 best_bar(void) {
    // Character-select bars at 0x37..0x3A of the record: Batting, Pitching, Running (speed), Fielding.
    const u8* bars = (const u8*)&lbl_8034E9A0.roster[sCareer.body / 9][sCareer.body % 9] + 0x37;
    s32 v[4];
    s32 best = 0;
    s32 i;
    v[0] = bars[0];
    v[1] = bars[1];
    v[3] = bars[2];
    v[2] = bars[3];
    for (i = 1; i < 4; i++) {
        if (v[i] > v[best]) best = i;
    }
    return best;
}

// Tier 1: the generic variants (variantClassification 3/4 in lbl_801094E4; docs/career/career_data.md).
static s32 is_tier1(s32 id) {
    switch (id) {
    case CHAR_ID_KOOPA_GREEN: case CHAR_ID_KOOPA_RED: case CHAR_ID_TOAD_RED: case CHAR_ID_TOAD_BLUE:
    case CHAR_ID_TOAD_YELLOW: case CHAR_ID_TOAD_GREEN: case CHAR_ID_TOAD_PURPLE: case CHAR_ID_BOO:
    case CHAR_ID_SHYGUY_RED: case CHAR_ID_SHYGUY_BLUE: case CHAR_ID_SHYGUY_YELLOW: case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_SHYGUY_BLACK: case CHAR_ID_PARATROOPA_RED: case CHAR_ID_PARATROOPA_GREEN:
    case CHAR_ID_PIANTA_BLUE: case CHAR_ID_PIANTA_RED: case CHAR_ID_PIANTA_YELLOW: case CHAR_ID_NOKI_BLUE:
    case CHAR_ID_NOKI_RED: case CHAR_ID_NOKI_GREEN: case CHAR_ID_BRO_HAMMER: case CHAR_ID_BRO_FIRE:
    case CHAR_ID_BRO_BOOMERANG: case CHAR_ID_MAGIKOOPA_BLUE: case CHAR_ID_MAGIKOOPA_RED:
    case CHAR_ID_MAGIKOOPA_GREEN: case CHAR_ID_MAGIKOOPA_YELLOW: case CHAR_ID_GOOMBA: case CHAR_ID_PARAGOOMBA:
    case CHAR_ID_DRYBONES_GRAY: case CHAR_ID_DRYBONES_GREEN: case CHAR_ID_DRYBONES_RED: case CHAR_ID_DRYBONES_BLUE:
        return 1;
    default:
        return 0;
    }
}

// Your team: the captain's default 9 with you in place of the last generic variant.
static void build_team_roster(s32 team) {
    s32 i;
    s32 replaced = -1;
    for (i = 0; i < 9; i++) {
        sCareer.roster[i] = preset_char(team, i);
    }
    // Captain into slot 0.
    for (i = 0; i < 9; i++) {
        if (sCareer.roster[i] == sTeamCaptain[team] && i != 0) {
            s32 tmp = sCareer.roster[0];
            sCareer.roster[0] = sCareer.roster[i];
            sCareer.roster[i] = tmp;
        }
    }
    for (i = 8; i >= 1; i--) {
        if (is_tier1(sCareer.roster[i])) {
            replaced = i;
            break;
        }
    }
    if (replaced < 0) {
        replaced = 8;
    }
    // Never two of you: if your body is already on the team, that slot is the one you take.
    for (i = 1; i < 9; i++) {
        if (sCareer.roster[i] == sCareer.body) {
            replaced = i;
        }
    }
    sCareer.roster[replaced] = sCareer.body;
}

// Called right after the game's end-of-game bookkeeping (fn_3_76558).
void port_career_game_final(void) {
    GameScore g;
    if (!sArmed) {
        return; // not a career game (or a rematch from the results screen)
    }
    sArmed = 0;
    career_load();
    sRecapCount = 0;
    recap("%s %d-%d  %s", lbl_80353A90.winner == 0 ? "WIN" : (lbl_80353A90.winner == 1 ? "LOSS" : "TIE"),
          lbl_80353A90.runs[0][0], lbl_80353A90.runs[1][0],
          sOppTeam < 0 ? "Tryout vs Bowser Jr." : sTeamName[sOppTeam]);
    career_log("Final: %d-%d %s", lbl_80353A90.runs[0][0], lbl_80353A90.runs[1][0],
               lbl_80353A90.winner == 0 ? "WIN" : (lbl_80353A90.winner == 1 ? "LOSS" : "TIE"));
    snprintf(sCareer.last[0], sizeof(sCareer.last[0]), "%s %d-%d vs %s",
             lbl_80353A90.winner == 0 ? "W" : (lbl_80353A90.winner == 1 ? "L" : "T"), lbl_80353A90.runs[0][0],
             lbl_80353A90.runs[1][0], sOppTeam < 0 ? "Bowser Jr." : sTeamName[sOppTeam]);
    sCareer.last[1][0] = sCareer.last[2][0] = '\0';
    g = score_game(sMySlot);
    sCareer.lastIwar = g.iwar;
    sCareer.lastTwar = g.twar;
    sCareer.hasLast = 1;
    if (sCareer.stage == STAGE_CHAPTERS) {
        sCareer.seasonIwar += g.iwar;
        sCareer.seasonTwar += g.twar;
    }
    career_log("  iWAR %.2f, tWAR %.2f", g.iwar, g.twar);
    recap("iWAR %.2f   tWAR %.2f", g.iwar, g.twar);
    sCareer.gamesPlayed++;
    if (g.won == 1) sCareer.wins++;
    else if (g.won == 0) sCareer.losses++;
    else sCareer.ties++;

    if (sCareer.stage == STAGE_PROLOGUE) {
        f32 total = g.iwar + g.twar;
        s32 pts = g.iwar >= 7.0f ? 2 : (g.iwar >= 3.0f ? 1 : 0);
        if (g.positives == 0) {
            sCareer.team = TEAM_DK;
            career_log("Nothing went right at the tryout. Walking home through the jungle, DK finds you.");
        } else if (total >= 10.0f) {
            sCareer.team = TEAM_MARIO;
            career_log("Mario picks you first. Now every at-bat is watched.");
        } else if (total >= 4.0f) {
            sCareer.team = best_bar() == 3 ? TEAM_YOSHI : TEAM_PEACH;
            career_log("%s", sCareer.team == TEAM_YOSHI ? "Yoshi waves you over like you were always on the team."
                                                         : "Peach invites you to the castle team.");
        } else {
            sCareer.team = TEAM_WARIO;
            career_log("Wario signs you for the price of a coin, and gloats about the bargain.");
        }
        sCareer.pointsEarned += pts;
        build_team_roster(sCareer.team);
        career_log("Captain: %s (score %.2f). Attribute points earned: %d.", sTeamName[sCareer.team], total, pts);
        recap("Your captain: %s   +%d attribute point%s", sTeamName[sCareer.team], pts, pts == 1 ? "" : "s");
        sCareer.stage = STAGE_CHAPTERS;
        sCareer.chapter = 0;
        sCareer.game = 0;
        sCareer.chapterIwar = sCareer.chapterTwar = 0.0f;
        sCareer.chapterWins = 0;
    } else {
        sCareer.chapterIwar += g.iwar;
        sCareer.chapterTwar += g.twar;
        if (g.won == 1) sCareer.chapterWins++;
        sCareer.game++;
        if (sCareer.game >= 3) {
            s32 pts = chapter_points(sCareer.chapterIwar);
            sCareer.pointsEarned += pts;
            career_log("Chapter %d done vs %s: %d-%d in the series. iWAR %.2f -> %d attribute points. tWAR %.2f -> "
                       "recruit %s.",
                       sCareer.chapter + 1, sTeamName[career_chapter_team(sCareer.chapter)], sCareer.chapterWins,
                       3 - sCareer.chapterWins, sCareer.chapterIwar, pts, sCareer.chapterTwar,
                       recruit_tier(sCareer.chapterTwar));
            recap("Series %d-%d   +%d attribute point%s", sCareer.chapterWins, 3 - sCareer.chapterWins, pts,
                  pts == 1 ? "" : "s");
            recap("Recruit: %s", recruit_tier(sCareer.chapterTwar));
            sCareer.chapter++;
            sCareer.game = 0;
            sCareer.chapterIwar = sCareer.chapterTwar = 0.0f;
            sCareer.chapterWins = 0;
            if (sCareer.chapter >= 4) {
                sCareer.stage = STAGE_SEASON_DONE;
                career_log("Regular season complete: %d-%d-%d, %d attribute points earned.", sCareer.wins,
                           sCareer.losses, sCareer.ties, sCareer.pointsEarned);
            }
        }
    }
    career_save();
}


// ---------------------------------------------------------------- Career menu (scene 18)
// A menu screen of its own, entered from the main menu's Challenge entry like Options: the
// game's menu background (changeScene) with the menu drawn in the game's font by its text system
// (DrawTextOnCondition) on sprite layer 8. First visit: Create Character. After that the hub:
// Next Game, Attributes, Lineup, Positions, Settings, Save.
#include "main/file_8000F150.h" // TextSystem lbl_80366B18
#include "main/file_8001FE00.h" // SceneFade lbl_8037169C

extern void fn_2_11A0(u16 scene);
extern void port_menus_start_game(void);
#include "musyx/musyx.h"
extern u8 lbl_800EFBA4[]; // menu sound-effect volumes

static const char* const sCharName[54] = {
    "Mario", "Luigi", "DK", "Diddy", "Peach", "Daisy", "Yoshi", "Baby Mario", "Baby Luigi", "Bowser", "Wario",
    "Waluigi", "Koopa", "Toad", "Boo", "Toadette", "Shy Guy", "Birdo", "Monty", "Bowser Jr.", "Paratroopa",
    "Pianta", "Pianta", "Pianta", "Noki", "Noki", "Noki", "Hammer Bro", "Toadsworth", "Toad", "Toad", "Toad",
    "Toad", "Magikoopa", "Magikoopa", "Magikoopa", "Magikoopa", "King Boo", "Petey", "Dixie", "Goomba",
    "Paragoomba", "Koopa", "Paratroopa", "Shy Guy", "Shy Guy", "Shy Guy", "Shy Guy", "Dry Bones", "Dry Bones",
    "Dry Bones", "Dry Bones", "Fire Bro", "Boomerang Bro",
};

// Base bodies: families with color variants, and their colors.
typedef struct Family {
    const char* name;
    s32 count;
    s32 ids[5];
    const char* colors[5];
} Family;
static const Family sFamilies[] = {
    {"Toad", 5, {CHAR_ID_TOAD_RED, CHAR_ID_TOAD_BLUE, CHAR_ID_TOAD_YELLOW, CHAR_ID_TOAD_GREEN, CHAR_ID_TOAD_PURPLE},
     {"Red", "Blue", "Yellow", "Green", "Purple"}},
    {"Shy Guy", 5, {CHAR_ID_SHYGUY_RED, CHAR_ID_SHYGUY_BLUE, CHAR_ID_SHYGUY_YELLOW, CHAR_ID_SHYGUY_GREEN, CHAR_ID_SHYGUY_BLACK},
     {"Red", "Blue", "Yellow", "Green", "Black"}},
    {"Koopa", 2, {CHAR_ID_KOOPA_GREEN, CHAR_ID_KOOPA_RED}, {"Green", "Red"}},
    {"Paratroopa", 2, {CHAR_ID_PARATROOPA_RED, CHAR_ID_PARATROOPA_GREEN}, {"Red", "Green"}},
    {"Pianta", 3, {CHAR_ID_PIANTA_BLUE, CHAR_ID_PIANTA_RED, CHAR_ID_PIANTA_YELLOW}, {"Blue", "Red", "Yellow"}},
    {"Noki", 3, {CHAR_ID_NOKI_BLUE, CHAR_ID_NOKI_RED, CHAR_ID_NOKI_GREEN}, {"Blue", "Red", "Green"}},
    {"Bro", 3, {CHAR_ID_BRO_HAMMER, CHAR_ID_BRO_FIRE, CHAR_ID_BRO_BOOMERANG}, {"Hammer", "Fire", "Boomerang"}},
    {"Magikoopa", 4, {CHAR_ID_MAGIKOOPA_BLUE, CHAR_ID_MAGIKOOPA_RED, CHAR_ID_MAGIKOOPA_GREEN, CHAR_ID_MAGIKOOPA_YELLOW},
     {"Blue", "Red", "Green", "Yellow"}},
    {"Dry Bones", 4, {CHAR_ID_DRYBONES_GRAY, CHAR_ID_DRYBONES_GREEN, CHAR_ID_DRYBONES_RED, CHAR_ID_DRYBONES_BLUE},
     {"Gray", "Green", "Red", "Blue"}},
};
#define FAMILY_COUNT ((s32)(sizeof(sFamilies) / sizeof(sFamilies[0])))

// Star Special: any captain's star move (the 12 captains).
static const s32 sStarChars[12] = {CHAR_ID_MARIO, CHAR_ID_LUIGI, CHAR_ID_PEACH, CHAR_ID_DAISY, CHAR_ID_YOSHI,
                                   CHAR_ID_BIRDO, CHAR_ID_DK, CHAR_ID_DIDDY, CHAR_ID_WARIO, CHAR_ID_WALUIGI,
                                   CHAR_ID_BOWSER, CHAR_ID_BOWSERJR};

static const char* const sBarName[4] = {"Batting", "Pitching", "Fielding", "Speed"};
static const char* const sStadiumName[TEAM_COUNT] = {"Mario Stadium", "Peach Garden", "Wario Palace",
                                                    "DK Jungle", "Yoshi Park", "Bowser Castle"};

// The game's bars for a character: Batting, Pitching, Fielding, Speed (record bytes 0x37..0x3A are
// Batting, Pitching, Running, Fielding).
static void body_bars(s32 id, s32* out) {
    const u8* b = (const u8*)&lbl_8034E9A0.roster[id / 9][id % 9] + 0x37;
    out[0] = b[0];
    out[1] = b[1];
    out[2] = b[3];
    out[3] = b[2];
}

static s32 family_of(s32 id, s32* color) {
    s32 f;
    s32 c;
    for (f = 0; f < FAMILY_COUNT; f++) {
        for (c = 0; c < sFamilies[f].count; c++) {
            if (sFamilies[f].ids[c] == id) {
                if (color) *color = c;
                return f;
            }
        }
    }
    if (color) *color = 0;
    return 0;
}

// --- text entries
// Row labels and the info block are placed where the main menu's own sprites sit: a sprite's
// last animation key gives its position in the sprite's space (the way fn_8000F988 /
// fn_8000F534 place text bound to a sprite). Titles and help lines are in screen space.
#include "main/file_80034F50.h" // lbl_803C4BE0 (sprite banks)
extern SpaniTexSlot lbl_803C4BE0[];
extern void* fn_800B0A5C_insertQueue(void* draw, u16 priority);
extern void fn_80053FE8(void); // menu frame (title banner, help bar)
extern void fn_2_82DE8(void);  // menu background of team select / lineup / stadium select
void port_career_layout_open(s32 rows, s32 row);
void port_career_layout_page(s32 rows, s32 row);
void port_career_layout_move(s32 row);
void port_career_layout_close(void);
s32 port_career_layout_up(void);
s32 port_career_layout_busy(void);
LayoutObj* port_career_layout_obj(s32 slot);

#define UI_LINES 24
#define UI_CHARS 160
static u16 sUiBuf[UI_LINES][UI_CHARS];
static s32 sUiEntry[UI_LINES];
static s32 sUiCount;

static void encode(u16* out, s32 cap, const char* s) {
    s32 n = 0;
    for (; *s != '\0' && n < cap - 1; s++) {
        char c = *s;
        u16 g;
        if (c >= 'A' && c <= 'Z') g = (u16)(0x20 + (c - 'A'));
        else if (c >= 'a' && c <= 'z') g = (u16)(0x3E + (c - 'a'));
        else if (c >= '0' && c <= '9') g = (u16)(0x0F + (c - '0'));
        else if (c == '.' || c == ',' || c == '-' || c == '\'' || c == '/' || c == ':' || c == '(' || c == ')' ||
                 c == '+' || c == '!' || c == '?' || c == '&' || c == ';')
            g = (u16)(c - 0x21);
        else if (c == '\n') g = 0x4001; // new line
        else if (c == '\x01') g = 0x4037; // control code 55: the menus' heavy font (font 3)
        else g = 0x4002;                // space (and anything the font may not have)
        out[n++] = g;
    }
    out[n] = 0x4000; // end of text (control code 0); a 0 is a glyph, not the end
}

// Text placed in a layout sprite's own space, scaled (the main menu's labels sit centered and
// smaller on their plates): matrix = sprite matrix * T(x, y) * S(scale), refreshed every frame
// since the sprite animates (the highlighted row's plate slides).
typedef struct UiXf {
    s32 used;
    s32 slot;
    f32 x, y, scale;
    Mtx m;
} UiXf;
static UiXf sXf[UI_LINES];

static void ui_xf_update(void) {
    s32 i;
    for (i = 0; i < UI_LINES; i++) {
        UiXf* f = &sXf[i];
        LayoutObj* o;
        Mtx t;
        Mtx sc;
        Mtx tmp;
        if (!f->used) continue;
        o = port_career_layout_obj(f->slot);
        if (o == NULL) continue;
        PSMTXTrans(t, f->x, f->y, 0.0f);
        PSMTXScale(sc, f->scale, f->scale, 1.0f);
        PSMTXConcat(o->mtx, t, tmp);
        PSMTXConcat(tmp, sc, f->m);
    }
}

static void ui_clear(void) {
    s32 i;
    for (i = 0; i < UI_LINES; i++) sXf[i].used = 0;
    for (i = 0; i < sUiCount; i++) {
        if (sUiEntry[i] >= 0 && lbl_80366B18.entries[sUiEntry[i]].text == sUiBuf[i]) {
            lbl_80366B18.entries[sUiEntry[i]].state = 0;
        }
    }
    sUiCount = 0;
}

#define UI_WHITE 0xFFFFFFFF
#define UI_GOLD 0xFFD830FF
#define UI_GRAY 0xC8C8C8FF

static TextEntry* ui_new(u32 color, s32 font, const char* fmt, va_list ap) {
    char buf[UI_CHARS];
    s32 k;
    TextEntry* e;
    if (sUiCount >= UI_LINES) {
        return NULL;
    }
    vsnprintf(buf, sizeof(buf), fmt, ap);
    for (k = 0; k < 30; k++) {
        if (lbl_80366B18.entries[k].state == 0) {
            break;
        }
    }
    if (k >= 30) {
        return NULL;
    }
    encode(sUiBuf[sUiCount], UI_CHARS, buf);
    e = &lbl_80366B18.entries[k];
    memset(e, 0, sizeof(*e));
    e->text = sUiBuf[sUiCount];
    e->layer = 6; // in front of the box (layer 8)
    e->fontSize = (u8)font;
    e->color = color;
    e->shadowColor = 0x000000FF;
    e->shadowX = 2;
    e->shadowY = 2;
    e->lineSpacing = 4;
    e->charLimit = -1;
    e->state = 2;
    sUiEntry[sUiCount++] = k;
    return e;
}

// Screen-space text (x, y in the 640x448 screen; halign 0 left, 1 centered on x).
static TextEntry* ui_text(s32 x, s32 y, u32 color, s32 font, s32 halign, const char* fmt, ...)
    __attribute__((format(printf, 6, 7)));
static TextEntry* ui_text(s32 x, s32 y, u32 color, s32 font, s32 halign, const char* fmt, ...) {
    va_list ap;
    TextEntry* e;
    va_start(ap, fmt);
    e = ui_new(color, font, fmt, ap);
    va_end(ap);
    if (e != NULL) {
        e->x = (u16)x;
        e->y = (u16)y;
        e->hAlign = (u8)halign;
    }
    return e;
}
#define ui_line(x, y, color, ...) ui_text((x), (y), (color), 1, 0, __VA_ARGS__)

// Text on main-menu layout sprite `slot`, offset (dx, dy) from the sprite's key position
// (in the sprite's own space), drawn above the layout (layer 8, over the highlight).
static TextEntry* ui_on(s32 slot, s32 dx, s32 dy, u32 color, s32 font, s32 halign, const char* fmt, ...)
    __attribute__((format(printf, 7, 8)));
static TextEntry* ui_on(s32 slot, s32 dx, s32 dy, u32 color, s32 font, s32 halign, const char* fmt, ...) {
    LayoutObj* o = port_career_layout_obj(slot);
    u32 info[128];
    s16 kx = 0;
    s16 ky = 0;
    va_list ap;
    TextEntry* e;
    if (o == NULL) {
        return NULL;
    }
    memset(info, 0, sizeof(info));
    if (fn_8000CEF0((Anim*)lbl_803C4BE0[o->_66].anim, o->_64, 0, 0, info)) {
        kx = *(s16*)((u8*)info + 0x14);
        ky = *(s16*)((u8*)info + 0x16);
    }
    va_start(ap, fmt);
    e = ui_new(color, font, fmt, ap);
    va_end(ap);
    if (e == NULL) {
        return NULL;
    }
    e->mtx = o->_00 != NULL ? o->mtx : NULL;
    e->x = (u16)(kx + dx);
    e->y = (u16)(ky + dy + (o->_00 == NULL ? (s32)o->y : 0));
    e->layer = 8;
    e->hAlign = (u8)halign;
    e->vAlign = 0;
    return e;
}

// Centered text at (x, y) of sprite `slot`'s space, scaled.
static TextEntry* ui_xf(s32 slot, f32 x, f32 y, f32 scale, u32 color, s32 font, const char* fmt, ...)
    __attribute__((format(printf, 7, 8)));
static TextEntry* ui_xf(s32 slot, f32 x, f32 y, f32 scale, u32 color, s32 font, const char* fmt, ...) {
    va_list ap;
    TextEntry* e;
    UiXf* f;
    if (port_career_layout_obj(slot) == NULL) {
        return NULL;
    }
    va_start(ap, fmt);
    e = ui_new(color, font, fmt, ap);
    va_end(ap);
    if (e == NULL) {
        return NULL;
    }
    f = &sXf[sUiCount - 1];
    f->used = 1;
    f->slot = slot;
    f->x = x;
    f->y = y;
    f->scale = scale;
    ui_xf_update();
    e->mtx = f->m;
    e->x = 0;
    e->y = 0;
    e->layer = 8;
    e->hAlign = 1;
    e->vAlign = 1;
    return e;
}

// --- menu state
enum { PAGE_CREATE, PAGE_CREATE_BARS, PAGE_HUB, PAGE_ATTR, PAGE_SETTINGS };
enum { CR_BODY, CR_COLOR, CR_NAME, CR_STAR, CR_HANDS, CR_BARS, CR_CONFIRM, CR_ROWS };
enum { HUB_NEXT, HUB_ATTR, HUB_LINEUP, HUB_SETTINGS, HUB_ROWS };
enum { LEAVE_MAIN = 1, LEAVE_GAME, LEAVE_LINEUP };

static s32 sScene;        // 0 enter, 1 menu up, 2 leaving
static s32 sPage;
static s32 sRow;
static s32 sDirty;
static s32 sNameEdit;     // editing the name: cursor position, -1 off
static char sMsg[64];     // one-line status ("Saved")
static s32 sConfirmLeave; // hub: "Leave Career?" prompt up
static s32 sLeave;        // LEAVE_* while leaving
static s32 sLeaveWait;
static s32 sReturnRow = -1; // hub row to come back to (from Lineup / Positions)
// The game's lineup screen as the Lineup / Positions pages
static s32 sLineupActive;
static s32 sLineupField;
static s32 sFrameUp, sBgUp;
// Create Character working copy
static s32 sFam, sColor, sStar, sBars[4], sPool, sBats, sThrows;
static char sName[12];
// Attributes page
static s32 sAttrBase[4];

static s32 sNoFadeWait;
static s32 sCardUp, sCardKill;

// --- the matchup card (the right-hand box on every page): your team's logo vs the next
// opponent's, the record and your season stats; below, your player's face and last game.
// Sprites of the game's own banks: the team logo of team select (bank 15, anim 2, frame =
// captainVariant) and the lineup screen's face icons (bank 1, anim 0x83, frame = character id).
extern void fn_80034E20(void* group, SpaniDesc* descs);
extern void fn_80034CEC(void* group);
extern void fn_800B0A14_removeQueue(void* unused);
extern void* lbl_803CC1B8; // the running task
static SpaniDesc sCardDescs[4] = {
    // Layer 6: in front of the box (layer 8), as the main menu's own picture (layer 7) is.
    {0, 2, 0.0f, 0.0f, -1, 0, 6, 255, 15, {0, 0, 0}, 0.0f, 0, 1, 0},    // your team's logo
    {0, 2, 0.0f, 0.0f, -1, 0, 6, 255, 15, {0, 0, 0}, 0.0f, 0, 1, 0},    // the opponent's logo
    {0, 0x83, 0.0f, 0.0f, -1, 0, 6, 255, 1, {0, 0, 0}, 0.0f, 0, 1, 0},  // your player's face
    {3, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
static LayoutGroup* sCardTask;
static s32 sCardShow;
static s32 sLogo[2] = {-1, -1}; // logo frames of the next game's teams (captainVariant)

// Logo frame of a captain: captain index (lbl_80108ED0) * 4; a generic captain uses Mario's.
static s32 logo_frame(s32 captain) {
    s32 k;
    for (k = 0; k < 12; k++) {
        if (lbl_80108ED0[k] == captain) return k * 4;
    }
    for (k = 0; k < 12; k++) {
        if (lbl_80108ED0[k] == CHAR_ID_MARIO) return k * 4;
    }
    return 0;
}

static s32 sprite_key(LayoutObj* o, s32* x, s32* y) {
    u32 info[128];
    memset(info, 0, sizeof(info));
    *x = *y = 0;
    if (!fn_8000CEF0((Anim*)lbl_803C4BE0[o->_66].anim, o->_64, 0, 0, info)) {
        return 0;
    }
    *x = *(s16*)((u8*)info + 0x14);
    *y = *(s16*)((u8*)info + 0x16);
    return 1;
}

// Screen spots (640x448) in the main menu's right-hand box: its top panel is about
// (272, 130)-(605, 305) and its bottom panel (275, 317)-(604, 382).
#define CARD_LOGO0_X 284
#define CARD_LOGO1_X 448
#define CARD_LOGO_Y 138
#define CARD_FACE_X 284
#define CARD_FACE_Y 326

static void card_update(void) {
    static const s32 kPos[3][2] = {{CARD_LOGO0_X, CARD_LOGO_Y}, {CARD_LOGO1_X, CARD_LOGO_Y}, {CARD_FACE_X, CARD_FACE_Y}};
    s32 frames[3];
    s32 i;
    if (sCardKill) {
        fn_80034CEC(sCardTask);
        sCardTask = NULL;
        sCardKill = 0;
        sCardUp = 0;
        fn_800B0A14_removeQueue(NULL);
        return;
    }
    ui_xf_update();
    if (sLogo[0] >= 0) {
        frames[0] = sLogo[0];
        frames[1] = sLogo[1];
    } else {
        s32 opp = sCareer.stage == STAGE_CHAPTERS ? career_chapter_team(sCareer.chapter) : -1;
        frames[0] = logo_frame(sCareer.team >= 0 ? sTeamCaptain[sCareer.team] : CHAR_ID_MARIO);
        frames[1] = logo_frame(sCareer.stage == STAGE_PROLOGUE ? CHAR_ID_BOWSERJR : (opp >= 0 ? sTeamCaptain[opp] : CHAR_ID_MARIO));
    }
    // Your face: the body being picked on Create Your Player.
    frames[2] = (sPage == PAGE_CREATE || sPage == PAGE_CREATE_BARS) ? sFamilies[sFam].ids[sColor] : sCareer.body;
    for (i = 0; i < 3; i++) {
        LayoutObj* o = lbl_80371C30[sCardTask->start + i].obj;
        s32 kx;
        s32 ky;
        if (o == NULL) continue;
        if (!sCardShow || !port_career_layout_up()) {
            o->flags &= ~2;
            continue;
        }
        o->_5C = (u32)frames[i] << 16;
        o->_68 = 0;
        // A root sprite's key is its top-left on screen, moved by (x, y).
        sprite_key(o, &kx, &ky);
        o->x = (f32)(kPos[i][0] - kx);
        o->y = (f32)(kPos[i][1] - ky);
        o->flags |= 2;
    }
}

static void card_init(void) {
    s32 i;
    sCardTask = (LayoutGroup*)lbl_803CC1B8;
    fn_80034E20(sCardTask, sCardDescs);
    for (i = 0; i < 3; i++) {
        lbl_80371C30[sCardTask->start + i].obj->flags &= ~2;
    }
    sCardTask->callback = card_update;
}

static s32 page_rows(s32 page) {
    switch (page) {
    case PAGE_CREATE: return CR_ROWS;
    case PAGE_CREATE_BARS: return 5;
    case PAGE_HUB: return HUB_ROWS;
    case PAGE_ATTR: return 5;
    case PAGE_SETTINGS: return 2;
    }
    return 1;
}

static void sfx(s32 kind) {
    static const u16 ids[3] = {0x1B7, 0x1B8, 0x1B9}; // move, confirm, back
    sndFXStartEx(ids[kind], lbl_800EFBA4[kind], 0x3F, 0);
}

static void create_begin(void) {
    s32 i;
    s32 base[4];
    sFam = family_of(sCareer.body, &sColor);
    sStar = sCareer.star;
    snprintf(sName, sizeof(sName), "%s", sCareer.name[0] ? sCareer.name : "ROOKIE");
    body_bars(sFamilies[sFam].ids[sColor], base);
    for (i = 0; i < 4; i++) sBars[i] = sCareer.created ? sCareer.bars[i] : base[i];
    sPool = 0;
    sNameEdit = -1;
    {
        s32 id = sFamilies[sFam].ids[sColor];
        const CharacterStats* c = &lbl_8034E9A0.roster[id / 9][id % 9];
        sBats = sCareer.bats >= 0 ? sCareer.bats : c->stats.BattingStance;
        sThrows = sCareer.throws >= 0 ? sCareer.throws : c->stats.FieldingArm;
    }
}

// Changing body/color resets the allocation to that body's own bars.
static void create_body_changed(void) {
    s32 i;
    body_bars(sFamilies[sFam].ids[sColor], sBars);
    for (i = 0; i < 4; i++) {
        if (sBars[i] < 1) sBars[i] = 1;
    }
    sPool = 0;
    {
        s32 id = sFamilies[sFam].ids[sColor];
        sBats = lbl_8034E9A0.roster[id / 9][id % 9].stats.BattingStance;
        sThrows = lbl_8034E9A0.roster[id / 9][id % 9].stats.FieldingArm;
    }
}

static void create_confirm(void) {
    s32 newBody = sFamilies[sFam].ids[sColor];
    s32 i;
    if (sCareer.team >= 0 && newBody != sCareer.body) {
        for (i = 1; i < 9; i++) {
            if (sCareer.roster[i] == sCareer.body) sCareer.roster[i] = newBody;
        }
        for (i = 0; i < 9; i++) {
            if (sCareer.lineupIds[i] == sCareer.body) sCareer.lineupIds[i] = newBody;
        }
    }
    sCareer.body = newBody;
    sCareer.star = sStar;
    sCareer.bats = sBats;
    sCareer.throws = sThrows;
    for (i = 0; i < 9; i++) {
        if (sCareer.lineupIds[i] == newBody) sCareer.lineupHand[i] = sBats + sThrows * 2;
    }
    for (i = 0; i < 4; i++) sCareer.bars[i] = sBars[i];
    snprintf(sCareer.name, sizeof(sCareer.name), "%s", sName);
    sCareer.created = 1;
    career_save();
    career_log("Created %s: %s %s, star of %s, bars B%d P%d F%d S%d", sCareer.name, sFamilies[sFam].colors[sColor],
               sFamilies[sFam].name, sCharName[sStarChars[sStar]], sBars[0], sBars[1], sBars[2], sBars[3]);
}

static void name_shown(char* shown, size_t cap) {
    if (sNameEdit >= 0) {
        s32 n = (s32)strlen(sName);
        s32 k;
        size_t o = 0;
        for (k = 0; k <= n && k < 10 && o + 3 < cap; k++) {
            if (k == sNameEdit) shown[o++] = '(';
            shown[o++] = k < n ? sName[k] : ' ';
            if (k == sNameEdit) shown[o++] = ')';
        }
        shown[o] = '\0';
    } else {
        snprintf(shown, cap, "%s", sName);
    }
}

static void row_label(s32 i, char* out, size_t cap) {
    out[0] = '\0';
    switch (sPage) {
    case PAGE_CREATE:
        switch (i) {
        case CR_BODY: snprintf(out, cap, "Body: %s", sFamilies[sFam].name); break;
        case CR_COLOR: snprintf(out, cap, "Color: %s", sFamilies[sFam].colors[sColor]); break;
        case CR_NAME: {
            char shown[32];
            name_shown(shown, sizeof(shown));
            snprintf(out, cap, "Name: %s", shown);
            break;
        }
        case CR_STAR: snprintf(out, cap, "Star: %s", sCharName[sStarChars[sStar]]); break;
        case CR_HANDS: snprintf(out, cap, "Bats %s  Throws %s", sBats ? "L" : "R", sThrows ? "L" : "R"); break;
        case CR_BARS: snprintf(out, cap, "Attributes"); break;
        case CR_CONFIRM: snprintf(out, cap, "Confirm"); break;
        }
        break;
    case PAGE_CREATE_BARS:
        if (i < 4) snprintf(out, cap, "%s  %d", sBarName[i], sBars[i]);
        else snprintf(out, cap, "Done");
        break;
    case PAGE_HUB: {
        static const char* const rows[HUB_ROWS] = {"Next Game", "Attributes", "Lineup & Positions", "Settings", "Save"};
        snprintf(out, cap, "%s", rows[i]);
        break;
    }
    case PAGE_ATTR:
        if (i < 4) snprintf(out, cap, "%s  %d", sBarName[i], sCareer.bars[i]);
        else snprintf(out, cap, "Done");
        break;
    case PAGE_SETTINGS:
        if (i == 0) snprintf(out, cap, "Innings  %d", sCareer.innings >= 1 ? sCareer.innings : lbl_800E8754.innings);
        else snprintf(out, cap, "Done");
        break;
    }
}

// ".308" style rate (no leading zero below 1).
static void fmt_rate(char* out, size_t cap, double v) {
    char t[16];
    snprintf(t, sizeof(t), "%.3f", v);
    snprintf(out, cap, "%s", (v < 1.0 && t[0] == '0') ? t + 1 : t);
}

// The right-hand box: record, season stats, last game (the logos and face are sprites).
// Top panel (272,130)-(605,305), bottom panel (275,317)-(604,382); lines of the 18-pixel font
// fit about 28 characters across a panel.
static TextEntry* card_block(s32 x, s32 y, s32 pitch, const char* text) {
    TextEntry* e = ui_line(x, y, UI_WHITE, "%s", text);
    if (e != NULL) {
        e->lineSpacing = (s8)(pitch - 18);
        e->charSpacing = -1;
    }
    return e;
}

// iWAR / tWAR: the condensed heavy font, gold.
static void card_war(s32 x, s32 y, f32 iwar, f32 twar) {
    TextEntry* e = ui_text(x, y, UI_GOLD, 0, 0, "iWAR %.2f  tWAR %.2f", iwar, twar);
    if (e != NULL) {
        e->shadowColor = 0x3A2400FF;
        e->charSpacing = -1;
    }
}

// --- the button words: the main menu's own word pictures (bank 6 textures 49, 52-57, one per
// row), swapped for words made of the same pictures' letters (port/game/career_labels.c) while
// the Career menu is up. "Options" is the game's own picture. Restored when the menu closes.
extern const char* const g_careerLabelNames[];
extern const u8* const g_careerLabelData[];
extern const s32 g_careerLabelCount;
static const s32 kLabelTex[7] = {49, 52, 53, 54, 55, 56, 57}; // row i's picture (frame i of anim 0x36)
static TexArchive* sLabelArc;
static u32 sLabelOrig[7];

static void labels_restore(void) {
    s32 i;
    if (sLabelArc == NULL) return;
    for (i = 0; i < 7; i++) sLabelArc->entries[kLabelTex[i]].data = sLabelOrig[i];
    sLabelArc = NULL;
}

static void labels_apply(void) {
    static const char* const kWords[5][7] = {
        {"Character", "Color", "Title", "Encore", "Grip", "Training", "Complete"}, // PAGE_CREATE
        {"Contact", "Pitching", "Fielding", "Pace", "Complete"},                // PAGE_CREATE_BARS
        {"Play Game", "Training", "Roster", "Options"},                         // PAGE_HUB
        {"Contact", "Pitching", "Fielding", "Pace", "Complete"},                // PAGE_ATTR
        {"Game Time", "Complete"},                                              // PAGE_SETTINGS
    };
    LayoutObj* label = port_career_layout_obj(0x18);
    s32 i;
    if (label == NULL) return;
    if (sLabelArc == NULL) {
        TexArchive* arc = (TexArchive*)lbl_803C4BE0[label->_66].tex;
        if (arc == NULL || arc->count <= kLabelTex[6]) return;
        sLabelArc = arc;
        for (i = 0; i < 7; i++) sLabelOrig[i] = arc->entries[kLabelTex[i]].data;
    }
    for (i = 0; i < 7; i++) {
        const char* w = kWords[sPage][i];
        u32 data = sLabelOrig[i];
        s32 k;
        if (w != NULL && strcmp(w, "Options") == 0) {
            data = sLabelOrig[6];
        } else if (w != NULL) {
            for (k = 0; k < g_careerLabelCount; k++) {
                if (strcmp(g_careerLabelNames[k], w) == 0) {
                    PTR32_SET(data, g_careerLabelData[k]);
                }
            }
        }
        sLabelArc->entries[kLabelTex[i]].data = data;
    }
}

// The right-hand box (the main menu's description box): numbers and names for the page, in a
// fixed grid. The text font is about 15 px a character and 18 px a line at this size, so the top
// panel (272,130)-(605,305) holds 6 rows of about 22 characters under the logos, and the bottom
// panel (275,317)-(604,382) 4 rows of about 17 characters beside your face. The text system has
// only 30 entries (the menu frame keeps 10), so columns are single multi-line entries.
#define BOX_X 282    // left column
#define BOX_Y 194    // first row
#define BOX_ROW 18   // row pitch
#define LOW_X 336
#define LOW_Y 319
#define LOW_ROW 17

static TextEntry* box_text(s32 x, s32 y, s32 pitch, u32 color, const char* fmt, ...)
    __attribute__((format(printf, 5, 6)));
static TextEntry* box_text(s32 x, s32 y, s32 pitch, u32 color, const char* fmt, ...) {
    char v[UI_CHARS];
    va_list ap;
    TextEntry* e;
    va_start(ap, fmt);
    vsnprintf(v, sizeof(v), fmt, ap);
    va_end(ap);
    e = ui_line(x, y, color, "%s", v);
    if (e != NULL) {
        e->lineSpacing = (s8)(pitch - 18);
    }
    return e;
}

// One row of a label / value list (rows 0-5 of the top panel), the highlighted one gold.
static void box_item(s32 row, s32 valX, s32 hot, const char* label, const char* fmt, ...)
    __attribute__((format(printf, 5, 6)));
static void box_item(s32 row, s32 valX, s32 hot, const char* label, const char* fmt, ...) {
    char v[48];
    va_list ap;
    u32 c = hot ? UI_GOLD : UI_WHITE;
    va_start(ap, fmt);
    vsnprintf(v, sizeof(v), fmt, ap);
    va_end(ap);
    ui_line(BOX_X, BOX_Y + row * BOX_ROW, c, "%s", label);
    if (v[0]) ui_line(BOX_X + valX, BOX_Y + row * BOX_ROW, c, "%s", v);
}

static void draw_card(void) {
    const s32* b = sCareer.bat;
    const s32* q = sCareer.pit;
    s32 r;
    if (sPage == PAGE_CREATE) {
        static const char* const kName[] = {"Character", "Color", "Title", "Encore", "Grip", "Training"};
        char shown[32];
        for (r = 0; r < CR_ROWS - 1; r++) {
            s32 hot = r == sRow;
            switch (r) {
            case CR_BODY: box_item(r, 150, hot, kName[r], "%s", sFamilies[sFam].name); break;
            case CR_COLOR: box_item(r, 150, hot, kName[r], "%s", sFamilies[sFam].colors[sColor]); break;
            case CR_NAME: name_shown(shown, sizeof(shown)); box_item(r, 150, hot, kName[r], "%s", shown); break;
            case CR_STAR: box_item(r, 150, hot, kName[r], "%s", sCharName[sStarChars[sStar]]); break;
            case CR_HANDS: box_item(r, 150, hot, kName[r], "%s / %s", sBats ? "L" : "R", sThrows ? "L" : "R"); break;
            case CR_BARS: box_item(r, 150, hot, kName[r], "%d %d %d %d", sBars[0], sBars[1], sBars[2], sBars[3]); break;
            }
        }
    } else if (sPage == PAGE_CREATE_BARS || sPage == PAGE_ATTR) {
        static const char* const kName[] = {"Contact", "Pitching", "Fielding", "Pace"};
        const s32* bars = sPage == PAGE_ATTR ? sCareer.bars : sBars;
        for (r = 0; r < 4; r++) {
            box_item(r, 150, r == sRow, kName[r], "%d", bars[r]);
        }
        // Points, a little below the bars and inside the panel.
        ui_line(BOX_X, BOX_Y + 4 * BOX_ROW + 6, UI_GOLD, "%s", sPage == PAGE_ATTR ? "Points to spend" : "Points to place");
        ui_line(BOX_X + 240, BOX_Y + 4 * BOX_ROW + 6, UI_GOLD, "%d",
                sPage == PAGE_ATTR ? sCareer.pointsEarned - sCareer.pointsSpent : sPool);
    } else if (sPage == PAGE_SETTINGS) {
        s32 inn = sCareer.innings >= 1 ? sCareer.innings : lbl_800E8754.innings;
        // Two lines centered between the logos and the bottom of the panel.
        u32 c = sRow == 0 ? UI_GOLD : UI_WHITE;
        ui_line(BOX_X, 222, c, "Game Time");
        ui_line(BOX_X + 150, 222, c, "%d inning%s", inn, inn == 1 ? "" : "s");
        ui_line(BOX_X, 256, UI_WHITE, "CPU level");
        ui_line(BOX_X + 150, 256, UI_WHITE, "soon");
    } else {
        // Hub: two columns of label / value (labels at 282 and 452, values 92 / 70 to the right),
        // each column one entry; the WAR row is gold.
        char la[UI_CHARS] = "";
        char va[UI_CHARS] = "";
        char lb[UI_CHARS] = "";
        char vb[UI_CHARS] = "";
        if (sCareer.stage == STAGE_PROLOGUE) {
            snprintf(la, sizeof(la), "Tryout\n");
            snprintf(va, sizeof(va), "\n");
            snprintf(lb, sizeof(lb), "\n");
            snprintf(vb, sizeof(vb), "\n");
        } else {
            snprintf(la, sizeof(la), "Record\n");
            snprintf(va, sizeof(va), "%d-%d\n", sCareer.wins, sCareer.losses);
            snprintf(lb, sizeof(lb), "%s\n", sCareer.stage == STAGE_CHAPTERS ? "Game" : "");
            snprintf(vb, sizeof(vb), "%s\n", sCareer.stage == STAGE_CHAPTERS ? (sCareer.game == 0 ? "1/3" : sCareer.game == 1 ? "2/3" : "3/3") : "");
        }
        if (b[SB_G] > 0) {
            char avg[16];
            char ops[16];
            s32 ab = b[SB_AB];
            s32 tb = b[SB_H] + b[SB_2B] + 2 * b[SB_3B] + 3 * b[SB_HR];
            s32 obpDen = ab + b[SB_BB] + b[SB_HBP];
            double obp = obpDen > 0 ? (double)(b[SB_H] + b[SB_BB] + b[SB_HBP]) / obpDen : 0.0;
            double slg = ab > 0 ? (double)tb / ab : 0.0;
            size_t n;
            fmt_rate(avg, sizeof(avg), ab > 0 ? (double)b[SB_H] / ab : 0.0);
            fmt_rate(ops, sizeof(ops), obp + slg);
            n = strlen(la); snprintf(la + n, sizeof(la) - n, "\nAVG\nHR\nR\n%s", q[SP_OUTS] > 0 ? "ERA" : "2B");
            n = strlen(lb); snprintf(lb + n, sizeof(lb) - n, "\nOPS\nRBI\nSB\n%s", q[SP_OUTS] > 0 ? "WHIP" : "3B");
            n = strlen(va);
            if (q[SP_OUTS] > 0) {
                double ip = q[SP_OUTS] / 3.0;
                snprintf(va + n, sizeof(va) - n, "\n%s\n%d\n%d\n%.2f", avg, b[SB_HR], b[SB_R], 9.0 * q[SP_ER] / ip);
                n = strlen(vb);
                snprintf(vb + n, sizeof(vb) - n, "\n%s\n%d\n%d\n%.2f", ops, b[SB_RBI], b[SB_SB], (q[SP_BB] + q[SP_H]) / ip);
            } else {
                snprintf(va + n, sizeof(va) - n, "\n%s\n%d\n%d\n%d", avg, b[SB_HR], b[SB_R], b[SB_2B]);
                n = strlen(vb);
                snprintf(vb + n, sizeof(vb) - n, "\n%s\n%d\n%d\n%d", ops, b[SB_RBI], b[SB_SB], b[SB_3B]);
            }
        } else {
            box_text(BOX_X, BOX_Y + 3 * BOX_ROW, BOX_ROW, UI_WHITE, "No season games yet");
        }
        box_text(BOX_X, BOX_Y, BOX_ROW, UI_WHITE, "%s", la);
        box_text(BOX_X + 92, BOX_Y, BOX_ROW, UI_WHITE, "%s", va);
        box_text(BOX_X + 170, BOX_Y, BOX_ROW, UI_WHITE, "%s", lb);
        box_text(BOX_X + 170 + 70, BOX_Y, BOX_ROW, UI_WHITE, "%s", vb);
        box_text(BOX_X, BOX_Y + BOX_ROW, BOX_ROW, UI_GOLD, "iWAR");
        box_text(BOX_X + 92, BOX_Y + BOX_ROW, BOX_ROW, UI_GOLD, "%.2f", sCareer.seasonIwar);
        box_text(BOX_X + 170, BOX_Y + BOX_ROW, BOX_ROW, UI_GOLD, "tWAR");
        box_text(BOX_X + 170 + 70, BOX_Y + BOX_ROW, BOX_ROW, UI_GOLD, "%.2f", sCareer.seasonTwar);
    }
    // Bottom panel: your face (sprite), then the last game or the page's note.
    if (sPage == PAGE_HUB && sConfirmLeave) {
        box_text(LOW_X, LOW_Y, LOW_ROW, UI_GOLD, "Leave Career?");
        box_text(LOW_X, LOW_Y + LOW_ROW, LOW_ROW, UI_WHITE, "It's saved.\nA Yes    B No");
    } else if (sPage == PAGE_CREATE && sNameEdit >= 0) {
        box_text(LOW_X, LOW_Y, LOW_ROW, UI_GOLD, "Your title");
        box_text(LOW_X, LOW_Y + LOW_ROW, LOW_ROW, UI_WHITE, "Up/Down letter\nLeft/Right move\nA done");
    } else if (sPage == PAGE_CREATE || sPage == PAGE_CREATE_BARS) {
        box_text(LOW_X, LOW_Y, LOW_ROW, UI_GOLD, "%s", sName);
        box_text(LOW_X, LOW_Y + LOW_ROW, LOW_ROW, UI_WHITE, "%s\n%s%s", sFamilies[sFam].colors[sColor],
                 sFamilies[sFam].name, sPool ? "\nPlace every point" : "");
    } else if (sCareer.last[0][0]) {
        box_text(LOW_X, LOW_Y, LOW_ROW, UI_GOLD, "%s", sCareer.last[0]);
        if (sCareer.hasLast) {
            box_text(LOW_X, LOW_Y + LOW_ROW, LOW_ROW, UI_GOLD, "iWAR %.1f tWAR %.1f", sCareer.lastIwar, sCareer.lastTwar);
        }
        box_text(LOW_X, LOW_Y + (sCareer.hasLast ? 2 : 1) * LOW_ROW, LOW_ROW, UI_WHITE, "%s%s%s", sCareer.last[1],
                 sCareer.last[2][0] ? "\n" : "", sCareer.last[2]);
    } else {
        box_text(LOW_X, LOW_Y, LOW_ROW, UI_GOLD, "%s", sCareer.name);
        box_text(LOW_X, LOW_Y + LOW_ROW, LOW_ROW, UI_WHITE, "No games yet");
    }
}

// The main menu has no other text: the rows are its own button pictures (labels_apply) and
// everything else is in its right-hand box.
static void draw_page(void) {
    ui_clear();
    labels_apply();
    sCardShow = 1;
    draw_card();
    sDirty = 0;
}

static void go_page(s32 page, s32 row) {
    sConfirmLeave = 0;
    sPage = page;
    sRow = row;
    sMsg[0] = '\0';
    if (page == PAGE_CREATE && row == 0) create_begin();
    if (page == PAGE_ATTR) {
        s32 i;
        for (i = 0; i < 4; i++) sAttrBase[i] = sCareer.bars[i];
    }
    port_career_layout_page(page_rows(page), row);
    sDirty = 1;
}

static void move_row(s32 d) {
    s32 n = page_rows(sPage);
    sRow = (sRow + n + d) % n;
    port_career_layout_move(sRow);
    sfx(0);
    sDirty = 1;
}

// Leaves the Career menu: the layout goes first (its task frees itself on its next frame).
static void begin_leave(s32 what) {
    ui_clear();
    port_career_layout_close();
    sLeave = what;
    sLeaveWait = 0;
    sScene = 2;
    sCardKill = sCardUp; // the matchup card frees itself
    if (what == LEAVE_LINEUP) {
        // The team-select background and the menu frame, as the game has them after team select
        // (up a few frames before the lineup screen starts, so it can switch the background).
        if (!sBgUp) {
            fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
            sBgUp = 1;
        }
    }
}

// Lineup / Positions: the game's lineup screen (scene 0xB) with the next game's teams.
static void open_lineup(s32 field) {
    setup_game(0);
    sArmed = 0;
    sLineupActive = 1;
    sLineupField = field;
    sReturnRow = HUB_LINEUP;
    sScene = 0;
    fn_2_11A0(0xB);
}

s32 port_career_lineup_active(void) {
    return sLineupActive;
}

s32 port_career_lineup_take_field_view(void) {
    if (sLineupField) {
        sLineupField = 0;
        return 1;
    }
    return 0;
}

// The lineup screen is done: keep your batting order and field positions.
void port_career_lineup_done(s32 toGame) {
    s32 i;
    s32 k;
    for (i = 0; i < 9; i++) {
        sCareer.lineupIds[i] = inMemRoster[0][i].stats.CharID;
        sCareer.lineupHand[i] = inMemRoster[0][i].stats.BattingStance + inMemRoster[0][i].stats.FieldingArm * 2;
        if (sCareer.lineupIds[i] == sCareer.body) {
            sCareer.bats = inMemRoster[0][i].stats.BattingStance;
            sCareer.throws = inMemRoster[0][i].stats.FieldingArm;
        }
        for (k = 0; k < 4; k++) {
            sCareer.lineupOrd[i][k] = lbl_80354720[0][i][k];
        }
    }
    sCareer.lineupSet = 1;
    career_save();
    sLineupActive = 0;
    sLineupField = 0;
    if (toGame) {
        // Straight into the game from the lineup screen: it's the next career game.
        sMySlot = -1;
        for (i = 0; i < 9; i++) {
            if (inMemRoster[0][i].stats.CharID == sCareer.body) sMySlot = i;
        }
        sArmed = 1;
        sFrameUp = 0;
        sBgUp = 0;
        career_log("Next game from the lineup screen. You are slot %d.", sMySlot);
        return;
    }
    sNoFadeWait = 1; // the lineup screen doesn't fade out
    // The menu frame (title tab, help bar) stays up through the lineup screen, which retitled it.
    lbl_8034E978.menu = 0;
    if (sBgUp) {
        lbl_8034E9A0._48AF = 1; // the background frees itself (fn_2_82CF0)
        sBgUp = 0;
    }
}

static void input_create(u16 pr, u16 rp) {
    if (sNameEdit >= 0) {
        s32 n = (s32)strlen(sName);
        char c = sNameEdit < n ? sName[sNameEdit] : ' ';
        static const char kAlpha[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char* at = strchr(kAlpha, c);
        s32 idx = at ? (s32)(at - kAlpha) : 0;
        if (rp & 0x8) idx = (idx + 1) % 27;
        else if (rp & 0x4) idx = (idx + 26) % 27;
        if (rp & 0xC) {
            if (sNameEdit >= n) {
                if (n < 10) { sName[n] = kAlpha[idx]; sName[n + 1] = '\0'; }
            } else {
                sName[sNameEdit] = kAlpha[idx];
            }
            sfx(0);
            sDirty = 1;
        }
        if (rp & 0x2) { if (sNameEdit < n && sNameEdit < 9) sNameEdit++; sfx(0); sDirty = 1; }
        if (rp & 0x1) { if (sNameEdit > 0) sNameEdit--; sfx(0); sDirty = 1; }
        if (pr & 0x300) {
            s32 e = (s32)strlen(sName);
            while (e > 0 && sName[e - 1] == ' ') sName[--e] = '\0';
            if (sName[0] == '\0') snprintf(sName, sizeof(sName), "ROOKIE");
            sNameEdit = -1;
            sfx(1);
            sDirty = 1;
        }
        return;
    }
    if (rp & 0x8) move_row(-1);
    else if (rp & 0x4) move_row(1);
    else if (rp & 0x3) {
        s32 d = (rp & 0x2) ? 1 : -1;
        switch (sRow) {
        case CR_BODY: sFam = (sFam + FAMILY_COUNT + d) % FAMILY_COUNT; sColor = 0; create_body_changed(); break;
        case CR_COLOR: sColor = (sColor + sFamilies[sFam].count + d) % sFamilies[sFam].count; create_body_changed(); break;
        case CR_STAR: sStar = (sStar + 12 + d) % 12; break;
        case CR_HANDS: {
            // The four bat/throw combinations, in the lineup screen's order (its X button).
            s32 n = (sBats + sThrows * 2 + 4 + d) % 4;
            sBats = n % 2;
            sThrows = n / 2;
            break;
        }
        default: return;
        }
        sfx(0);
        sDirty = 1;
    } else if (pr & 0x100) {
        if (sRow == CR_NAME) { sNameEdit = 0; sfx(1); sDirty = 1; }
        else if (sRow == CR_BARS) { sfx(1); go_page(PAGE_CREATE_BARS, 0); }
        else if (sRow == CR_CONFIRM) {
            if (sPool == 0) { create_confirm(); sfx(1); go_page(PAGE_HUB, 0); }
            else { sfx(2); }
        }
    } else if (pr & 0x200) {
        sfx(2);
        if (sCareer.created) go_page(PAGE_HUB, 0);
        else begin_leave(LEAVE_MAIN);
    }
}

static void input_create_bars(u16 pr, u16 rp) {
    if (rp & 0x8) move_row(-1);
    else if (rp & 0x4) move_row(1);
    else if ((rp & 0x3) && sRow < 4) {
        s32* b = &sBars[sRow];
        if ((rp & 0x2) && sPool > 0 && *b < 10) { (*b)++; sPool--; }
        else if ((rp & 0x1) && *b > 1) { (*b)--; sPool++; }
        sfx(0);
        sDirty = 1;
    } else if ((pr & 0x200) || ((pr & 0x100) && sRow == 4)) {
        sfx(2);
        go_page(PAGE_CREATE, CR_BARS);
    }
}

static void input_hub(u16 pr, u16 rp) {
    if (sConfirmLeave) {
        if (pr & 0x100) {
            sConfirmLeave = 0;
            career_save();
            sfx(1);
            begin_leave(LEAVE_MAIN);
        } else if (pr & 0x200) {
            sConfirmLeave = 0;
            sfx(2);
            sDirty = 1;
        }
        return;
    }
    if (rp & 0x8) move_row(-1);
    else if (rp & 0x4) move_row(1);
    else if (pr & 0x200) { sfx(2); sConfirmLeave = 1; sMsg[0] = '\0'; sDirty = 1; }
    else if (pr & 0x100) {
        sfx(1);
        switch (sRow) {
        case HUB_NEXT: begin_leave(LEAVE_GAME); break;
        case HUB_ATTR: go_page(PAGE_ATTR, 0); break;
        case HUB_LINEUP: begin_leave(LEAVE_LINEUP); break;
        case HUB_SETTINGS: go_page(PAGE_SETTINGS, 0); break;
        }
    }
}

static void input_attr(u16 pr, u16 rp) {
    if (rp & 0x8) move_row(-1);
    else if (rp & 0x4) move_row(1);
    else if ((rp & 0x3) && sRow < 4) {
        s32* b = &sCareer.bars[sRow];
        if ((rp & 0x2) && sCareer.pointsEarned - sCareer.pointsSpent > 0 && *b < 10) { (*b)++; sCareer.pointsSpent++; }
        else if ((rp & 0x1) && *b > sAttrBase[sRow]) { (*b)--; sCareer.pointsSpent--; }
        sfx(0);
        sDirty = 1;
    } else if ((pr & 0x200) || ((pr & 0x100) && sRow == 4)) {
        career_save();
        sfx(2);
        go_page(PAGE_HUB, HUB_ATTR);
    }
}

static void input_settings(u16 pr, u16 rp) {
    if (rp & 0xC) move_row((rp & 0x8) ? -1 : 1);
    else if ((rp & 0x3) && sRow == 0) {
        static const s32 opts[5] = {1, 3, 5, 7, 9};
        s32 cur = sCareer.innings >= 1 ? sCareer.innings : lbl_800E8754.innings;
        s32 k = 0;
        s32 i;
        for (i = 0; i < 5; i++) if (opts[i] == cur) k = i;
        k = (k + 5 + ((rp & 0x2) ? 1 : -1)) % 5;
        sCareer.innings = opts[k];
        sfx(0);
        sDirty = 1;
    } else if ((pr & 0x200) || ((pr & 0x100) && sRow == 1)) {
        career_save();
        sfx(2);
        go_page(PAGE_HUB, HUB_SETTINGS);
    }
}

// Scene 18 handler (lbl_2_data_138), called every frame while the Career menu is up.
void port_career_scene(void) {
    s32 port;
    u16 pr;
    u16 rp;
    switch (sScene) {
    case 0: {
        s32 page;
        s32 row;
        if (!sNoFadeWait && lbl_8037169C._13 == 0) {
            return; // as Options: wait for the scene fade (none when back from the lineup screen)
        }
        sNoFadeWait = 0;
        changeScene(1, 6);
        career_load();
        sUiCount = 0;
        sLineupActive = 0;
        page = sCareer.created ? PAGE_HUB : PAGE_CREATE;
        row = (page == PAGE_HUB && sReturnRow >= 0) ? sReturnRow : 0;
        sReturnRow = -1;
        sConfirmLeave = 0;
        sMsg[0] = '\0';
        sPage = page;
        sRow = row;
        if (page == PAGE_CREATE) create_begin();
        // The next game's teams, for the logos (the game picks each team's logo variant).
        sLogo[0] = sLogo[1] = -1;
        if (sCareer.stage != STAGE_SEASON_DONE) {
            setup_game(0);
            sLogo[0] = (u8)lbl_8034E9A0.captainVariant[0];
            sLogo[1] = (u8)lbl_8034E9A0.captainVariant[1];
        }
        // The main menu's layout: background, button plates and highlight (menus: rep 71EC4).
        port_career_layout_open(page_rows(page), row);
        if (!sCardUp) {
            sCardUp = 1;
            sCardKill = 0;
            fn_800B0A5C_insertQueue((void*)card_init, 0x1000);
        }
        sDirty = 1;
        sScene = 1;
        return;
    }
    case 1:
        break;
    case 2:
        if (++sLeaveWait < 2 || port_career_layout_up() || sCardUp) {
            return;
        }
        labels_restore(); // the main menu's own words back, before any other screen draws them
        sScene = 0;
        switch (sLeave) {
        case LEAVE_MAIN:
            fn_2_11A0(5);
            break;
        case LEAVE_GAME:
            setup_game(1);
            port_menus_start_game();
            break;
        case LEAVE_LINEUP:
            open_lineup(0); // R / L flip between batting order and field positions
            break;
        }
        sLeave = 0;
        return;
    default:
        return;
    }
    if (!port_career_layout_up()) {
        return; // the layout builds on its first frame
    }
    if (sDirty) {
        draw_page();
    }
    if (port_career_layout_busy()) {
        return; // the highlight is moving
    }
    port = lbl_8034E9A0.ports[0] < 4 ? lbl_8034E9A0.ports[0] : 0;
    pr = lbl_8034E9A0.input[port].pressed;
    rp = lbl_8034E9A0.input[port].repeat | pr;
    switch (sPage) {
    case PAGE_CREATE: input_create(pr, rp); break;
    case PAGE_CREATE_BARS: input_create_bars(pr, rp); break;
    case PAGE_HUB: input_hub(pr, rp); break;
    case PAGE_ATTR: input_attr(pr, rp); break;
    case PAGE_SETTINGS: input_settings(pr, rp); break;
    }
    if (sScene == 1 && sDirty) {
        draw_page();
    }
}
