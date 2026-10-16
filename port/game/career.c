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

// Main menu, Career picked: set up the next career game. Returns TRUE when a game is set up.
BOOL port_career_setup_next_game(void) {
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
    g = score_game(sMySlot);
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
    {"Koopa Troopa", 2, {CHAR_ID_KOOPA_GREEN, CHAR_ID_KOOPA_RED}, {"Green", "Red"}},
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
#define UI_LINES 20
static u16 sUiBuf[UI_LINES][64];
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
                 c == '+')
            g = (u16)(c - 0x21);
        else g = 0x4002; // space (and anything the font may not have)
        out[n++] = g;
    }
    out[n] = 0x4000; // end of text (control code 0); a 0 is a glyph, not the end
}

static void ui_clear(void) {
    s32 i;
    for (i = 0; i < sUiCount; i++) {
        if (sUiEntry[i] >= 0 && lbl_80366B18.entries[sUiEntry[i]].text == sUiBuf[i]) {
            lbl_80366B18.entries[sUiEntry[i]].state = 0;
        }
    }
    sUiCount = 0;
}

#define UI_WHITE 0xFFFFFFFF
#define UI_GOLD 0xFFD830FF
#define UI_GRAY 0xB0B0B0FF
#define UI_CURSOR 0x60FF60FF

static void ui_line(s32 x, s32 y, u32 color, const char* fmt, ...) __attribute__((format(printf, 4, 5)));
static void ui_line(s32 x, s32 y, u32 color, const char* fmt, ...) {
    char buf[96];
    va_list ap;
    s32 k;
    TextEntry* e;
    if (sUiCount >= UI_LINES) {
        return;
    }
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    for (k = 0; k < 30; k++) {
        if (lbl_80366B18.entries[k].state == 0) {
            break;
        }
    }
    if (k >= 30) {
        return;
    }
    encode(sUiBuf[sUiCount], 64, buf);
    e = &lbl_80366B18.entries[k];
    memset(e, 0, sizeof(*e));
    e->text = sUiBuf[sUiCount];
    e->x = (u16)x;
    e->y = (u16)y;
    e->layer = 8;
    e->fontSize = 1;
    e->color = color;
    e->shadowColor = 0x000000FF;
    e->shadowX = 2;
    e->shadowY = 2;
    e->lineSpacing = 2;
    e->charLimit = -1;
    e->state = 2;
    sUiEntry[sUiCount++] = k;
}

// --- menu state
enum { PAGE_CREATE, PAGE_HUB, PAGE_ATTR, PAGE_LINEUP, PAGE_POSITIONS, PAGE_SETTINGS };
enum { CR_BODY, CR_COLOR, CR_NAME, CR_STAR, CR_BAR0, CR_BAR1, CR_BAR2, CR_BAR3, CR_CONFIRM, CR_ROWS };
enum { HUB_NEXT, HUB_ATTR, HUB_LINEUP, HUB_POSITIONS, HUB_SETTINGS, HUB_SAVE, HUB_ROWS };

static s32 sScene;       // scene step
static s32 sPage;
static s32 sRow;
static s32 sDirty;
static s32 sNameEdit;    // editing the name: cursor position, -1 off
static char sMsg[64];    // one-line status ("Saved")
static s32 sConfirmLeave; // hub: "Leave Career?" prompt up
// Create Character working copy
static s32 sFam, sColor, sStar, sBars[4], sPool;
static char sName[12];
// Attributes page
static s32 sAttrBase[4], sAttrSpent;

static void sfx(s32 kind) {
    static const u16 ids[3] = {0x1B7, 0x1B8, 0x1B9}; // move, confirm, back
    sndFXStartEx(ids[kind], lbl_800EFBA4[kind], 0x3F, 0);
}

static void create_begin(void) {
    s32 base[4];
    s32 i;
    sFam = family_of(sCareer.body, &sColor);
    sStar = sCareer.star;
    snprintf(sName, sizeof(sName), "%s", sCareer.name[0] ? sCareer.name : "ROOKIE");
    body_bars(sFamilies[sFam].ids[sColor], base);
    for (i = 0; i < 4; i++) sBars[i] = base[i];
    sPool = 0;
    sNameEdit = -1;
}

// Changing body/color resets the allocation to that body's own bars.
static void create_body_changed(void) {
    s32 i;
    body_bars(sFamilies[sFam].ids[sColor], sBars);
    for (i = 0; i < 4; i++) {
        if (sBars[i] < 1) sBars[i] = 1;
    }
    sPool = 0;
}

static void create_confirm(void) {
    s32 newBody = sFamilies[sFam].ids[sColor];
    s32 i;
    if (sCareer.team >= 0 && newBody != sCareer.body) {
        for (i = 1; i < 9; i++) {
            if (sCareer.roster[i] == sCareer.body) sCareer.roster[i] = newBody;
        }
    }
    sCareer.body = newBody;
    sCareer.star = sStar;
    for (i = 0; i < 4; i++) sCareer.bars[i] = sBars[i];
    snprintf(sCareer.name, sizeof(sCareer.name), "%s", sName);
    sCareer.created = 1;
    career_save();
    career_log("Created %s: %s %s, star of %s, bars B%d P%d F%d S%d", sCareer.name, sFamilies[sFam].colors[sColor],
               sFamilies[sFam].name, sCharName[sStarChars[sStar]], sBars[0], sBars[1], sBars[2], sBars[3]);
}

static void draw_page(void) {
    s32 x = 64;
    s32 y = 56;
    s32 i;
    ui_clear();
    if (sPage == PAGE_CREATE) {
        ui_line(x, y, UI_GOLD, "CREATE YOUR PLAYER");
        y += 34;
        for (i = 0; i < CR_ROWS; i++) {
            u32 c = (i == sRow) ? UI_CURSOR : UI_WHITE;
            const char* arrow = (i == sRow) ? "> " : "  ";
            switch (i) {
            case CR_BODY: ui_line(x, y, c, "%sBody          %s", arrow, sFamilies[sFam].name); break;
            case CR_COLOR: ui_line(x, y, c, "%sColor         %s", arrow, sFamilies[sFam].colors[sColor]); break;
            case CR_NAME: {
                char shown[24];
                if (sNameEdit >= 0) {
                    s32 n = (s32)strlen(sName);
                    s32 k;
                    s32 o = 0;
                    for (k = 0; k <= n && k < 10 && o < 22; k++) {
                        if (k == sNameEdit) shown[o++] = '(';
                        shown[o++] = k < n ? sName[k] : ' ';
                        if (k == sNameEdit) shown[o++] = ')';
                    }
                    shown[o] = '\0';
                } else {
                    snprintf(shown, sizeof(shown), "%s", sName);
                }
                ui_line(x, y, c, "%sName          %s", arrow, shown);
                break;
            }
            case CR_STAR: ui_line(x, y, c, "%sStar Special  %s's star", arrow, sCharName[sStarChars[sStar]]); break;
            case CR_BAR0: case CR_BAR1: case CR_BAR2: case CR_BAR3:
                ui_line(x, y, c, "%s%-13s %d", arrow, sBarName[i - CR_BAR0], sBars[i - CR_BAR0]);
                break;
            case CR_CONFIRM:
                ui_line(x, y, sPool == 0 ? c : UI_GRAY, "%sConfirm", arrow);
                break;
            }
            y += 26;
        }
        ui_line(x, y + 8, UI_GOLD, "Points to place: %d", sPool);
        ui_line(x, 404, UI_GRAY, sNameEdit >= 0 ? "Up/Down letter  Left/Right move  A done"
                                                : "Up/Down choose  Left/Right change  A select  B back");
    } else if (sPage == PAGE_HUB) {
        s32 opp = sCareer.stage == STAGE_CHAPTERS ? career_chapter_team(sCareer.chapter) : -1;
        ui_line(x, y, UI_GOLD, "CAREER  %s", sCareer.name);
        y += 30;
        if (sCareer.stage == STAGE_PROLOGUE) {
            ui_line(x, y, UI_WHITE, "Next: Tryout at Mario Stadium vs Bowser Jr.");
        } else if (opp >= 0) {
            ui_line(x, y, UI_WHITE, "Next: %s's team, game %d of 3, at %s", sTeamName[opp], sCareer.game + 1,
                    sStadiumName[opp]);
        } else {
            ui_line(x, y, UI_WHITE, "Regular season complete");
        }
        y += 22;
        ui_line(x, y, UI_WHITE, "Team: %s   Record %d-%d   Points %d", sCareer.team >= 0 ? sTeamName[sCareer.team] : "none yet",
                sCareer.wins, sCareer.losses, sCareer.pointsEarned - sCareer.pointsSpent);
        y += 40;
        for (i = 0; i < HUB_ROWS; i++) {
            static const char* const rows[HUB_ROWS] = {"Next Game", "Attributes", "Lineup", "Positions", "Settings", "Save"};
            ui_line(x + 16, y, i == sRow ? UI_CURSOR : UI_WHITE, "%s%s", i == sRow ? "> " : "  ", rows[i]);
            y += 28;
        }
        for (i = 0; i < sRecapCount && i < 4; i++) {
            ui_line(330, 166 + 22 * i, i == 0 ? UI_GOLD : UI_WHITE, "%s", sRecap[i]);
        }
        if (sConfirmLeave) {
            ui_line(x, 356, UI_GOLD, "Leave Career and go back to the main menu?");
            ui_line(x, 380, UI_WHITE, "Your career is saved when you leave.");
            ui_line(x, 404, UI_CURSOR, "A Yes, leave     B No, stay");
        } else {
            if (sMsg[0]) ui_line(x, 380, UI_GOLD, "%s", sMsg);
            ui_line(x, 404, UI_GRAY, "A select  B main menu");
        }
    } else if (sPage == PAGE_ATTR) {
        s32 left = sCareer.pointsEarned - sCareer.pointsSpent;
        ui_line(x, y, UI_GOLD, "ATTRIBUTES");
        y += 34;
        for (i = 0; i < 4; i++) {
            ui_line(x, y, i == sRow ? UI_CURSOR : UI_WHITE, "%s%-10s %d / 10", i == sRow ? "> " : "  ", sBarName[i],
                    sCareer.bars[i]);
            y += 28;
        }
        ui_line(x, y, sRow == 4 ? UI_CURSOR : UI_WHITE, "%sDone", sRow == 4 ? "> " : "  ");
        ui_line(x, y + 40, UI_GOLD, "Points to spend: %d", left);
        ui_line(x, y + 64, UI_GRAY, "Boosts unlock once every bar is maxed");
        ui_line(x, 404, UI_GRAY, "Right add a point  Left undo  B back");
    } else if (sPage == PAGE_LINEUP || sPage == PAGE_POSITIONS) {
        ui_line(x, y, UI_GOLD, sPage == PAGE_LINEUP ? "LINEUP" : "POSITIONS");
        y += 34;
        for (i = 0; i < 9; i++) {
            s32 id = sCareer.roster[i];
            ui_line(x, y, id == sCareer.body ? UI_GOLD : UI_WHITE, "%d. %s%s", i + 1, id >= 0 ? sCharName[id] : "-",
                    id == sCareer.body ? "  (you)" : (i == 0 ? "  (captain)" : ""));
            y += 24;
        }
        ui_line(x, y + 10, UI_GRAY, "Editing comes in the next build");
        ui_line(x, 404, UI_GRAY, "B back");
    } else if (sPage == PAGE_SETTINGS) {
        s32 inn = sCareer.innings >= 1 ? sCareer.innings : lbl_800E8754.innings;
        ui_line(x, y, UI_GOLD, "SETTINGS");
        y += 34;
        ui_line(x, y, sRow == 0 ? UI_CURSOR : UI_WHITE, "%sInnings   %d", sRow == 0 ? "> " : "  ", inn);
        y += 28;
        ui_line(x, y, sRow == 1 ? UI_CURSOR : UI_WHITE, "%sDone", sRow == 1 ? "> " : "  ");
        ui_line(x, y + 40, UI_GRAY, "CPU difficulty comes in the next build");
        ui_line(x, 404, UI_GRAY, "Left/Right change  B back");
    }
    sDirty = 0;
}

static void go_page(s32 page) {
    sConfirmLeave = 0;
    sPage = page;
    sRow = 0;
    sMsg[0] = '\0';
    if (page == PAGE_CREATE) create_begin();
    if (page == PAGE_ATTR) {
        s32 i;
        for (i = 0; i < 4; i++) sAttrBase[i] = sCareer.bars[i];
        sAttrSpent = sCareer.pointsSpent;
    }
    sDirty = 1;
}

static void leave_to_main_menu(void) {
    ui_clear();
    sScene = 0;
    fn_2_11A0(5);
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
            // trim trailing spaces
            s32 e = (s32)strlen(sName);
            while (e > 0 && sName[e - 1] == ' ') sName[--e] = '\0';
            if (sName[0] == '\0') snprintf(sName, sizeof(sName), "ROOKIE");
            sNameEdit = -1;
            sfx(1);
            sDirty = 1;
        }
        return;
    }
    if (rp & 0x8) { sRow = (sRow + CR_ROWS - 1) % CR_ROWS; sfx(0); sDirty = 1; }
    else if (rp & 0x4) { sRow = (sRow + 1) % CR_ROWS; sfx(0); sDirty = 1; }
    else if (rp & 0x3) {
        s32 d = (rp & 0x2) ? 1 : -1;
        switch (sRow) {
        case CR_BODY: sFam = (sFam + FAMILY_COUNT + d) % FAMILY_COUNT; sColor = 0; create_body_changed(); break;
        case CR_COLOR: sColor = (sColor + sFamilies[sFam].count + d) % sFamilies[sFam].count; create_body_changed(); break;
        case CR_STAR: sStar = (sStar + 12 + d) % 12; break;
        case CR_BAR0: case CR_BAR1: case CR_BAR2: case CR_BAR3: {
            s32* b = &sBars[sRow - CR_BAR0];
            if (d > 0 && sPool > 0 && *b < 10) { (*b)++; sPool--; }
            else if (d < 0 && *b > 1) { (*b)--; sPool++; }
            break;
        }
        default: break;
        }
        sfx(0);
        sDirty = 1;
    } else if (pr & 0x100) {
        if (sRow == CR_NAME) { sNameEdit = 0; sfx(1); sDirty = 1; }
        else if (sRow == CR_CONFIRM && sPool == 0) { create_confirm(); sfx(1); go_page(PAGE_HUB); }
    } else if (pr & 0x200) {
        sfx(2);
        if (sCareer.created) go_page(PAGE_HUB);
        else leave_to_main_menu();
    }
}

static void input_hub(u16 pr, u16 rp) {
    if (sConfirmLeave) {
        if (pr & 0x100) {
            sConfirmLeave = 0;
            career_save();
            sfx(1);
            leave_to_main_menu();
        } else if (pr & 0x200) {
            sConfirmLeave = 0;
            sfx(2);
            sDirty = 1;
        }
        return;
    }
    if (rp & 0x8) { sRow = (sRow + HUB_ROWS - 1) % HUB_ROWS; sfx(0); sDirty = 1; }
    else if (rp & 0x4) { sRow = (sRow + 1) % HUB_ROWS; sfx(0); sDirty = 1; }
    else if (pr & 0x200) { sfx(2); sConfirmLeave = 1; sMsg[0] = '\0'; sDirty = 1; }
    else if (pr & 0x100) {
        sfx(1);
        switch (sRow) {
        case HUB_NEXT:
            ui_clear();
            sScene = 0;
            port_career_setup_next_game();
            port_menus_start_game();
            break;
        case HUB_ATTR: go_page(PAGE_ATTR); break;
        case HUB_LINEUP: go_page(PAGE_LINEUP); break;
        case HUB_POSITIONS: go_page(PAGE_POSITIONS); break;
        case HUB_SETTINGS: go_page(PAGE_SETTINGS); break;
        case HUB_SAVE:
            career_save();
            snprintf(sMsg, sizeof(sMsg), "Saved");
            sDirty = 1;
            break;
        }
    }
}

static void input_attr(u16 pr, u16 rp) {
    if (rp & 0x8) { sRow = (sRow + 4) % 5; sfx(0); sDirty = 1; }
    else if (rp & 0x4) { sRow = (sRow + 1) % 5; sfx(0); sDirty = 1; }
    else if ((rp & 0x3) && sRow < 4) {
        s32* b = &sCareer.bars[sRow];
        if ((rp & 0x2) && sCareer.pointsEarned - sCareer.pointsSpent > 0 && *b < 10) { (*b)++; sCareer.pointsSpent++; }
        else if ((rp & 0x1) && *b > sAttrBase[sRow]) { (*b)--; sCareer.pointsSpent--; }
        sfx(0);
        sDirty = 1;
    } else if ((pr & 0x200) || ((pr & 0x100) && sRow == 4)) {
        career_save();
        sfx(2);
        go_page(PAGE_HUB);
        sRow = HUB_ATTR;
    }
}

static void input_settings(u16 pr, u16 rp) {
    if (rp & 0xC) { sRow ^= 1; sfx(0); sDirty = 1; }
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
        go_page(PAGE_HUB);
        sRow = HUB_SETTINGS;
    }
}

// Scene 18 handler (lbl_2_data_138), called every frame while the Career menu is up.
void port_career_scene(void) {
    s32 port;
    u16 pr;
    u16 rp;
    switch (sScene) {
    case 0:
        if (lbl_8037169C._13 == 0) {
            return; // as Options: wait for the scene fade
        }
        changeScene(1, 6);
        career_load();
        sUiCount = 0;
        go_page(sCareer.created ? PAGE_HUB : PAGE_CREATE);
        sScene = 1;
        return;
    case 1:
        break;
    default:
        return;
    }
    port = lbl_8034E9A0.ports[0] < 4 ? lbl_8034E9A0.ports[0] : 0;
    pr = lbl_8034E9A0.input[port].pressed;
    rp = lbl_8034E9A0.input[port].repeat | pr;
    switch (sPage) {
    case PAGE_CREATE: input_create(pr, rp); break;
    case PAGE_HUB: input_hub(pr, rp); break;
    case PAGE_ATTR: input_attr(pr, rp); break;
    case PAGE_SETTINGS: input_settings(pr, rp); break;
    default:
        if (pr & 0x300) { sfx(2); go_page(PAGE_HUB); }
        break;
    }
    if (sScene == 1 && sDirty) {
        draw_page();
    }
}
