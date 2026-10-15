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
    fprintf(stderr, "[career] new career, player body %d\n", sCareer.body);
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
        if (v != NULL && atoi(v) >= 1 && atoi(v) <= 9) {
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
        if (p->played && p->battersFaced > 0) {
            career_log("  Pitching: %d outs, %d K, %d H, %d BB, %d HR, %d ER", p->outsPitched, p->strikeouts,
                       p->hitsAllowed, p->walks, p->homeRunsAllowed, p->_04);
        }
    }
    g.twar = (g.won == 1 ? 3.0f : (g.won == 0 ? -1.0f : 0.0f)) + 0.25f * (f32)(g.runsFor - g.runsAgainst) -
             0.5f * lbl_80353A90.errors[0] + 0.25f * (f32)teamHr;
    return g;
}

static s32 chapter_points(f32 iwar) {
    if (iwar >= 18.0f) return 4;
    if (iwar >= 12.0f) return 3;
    if (iwar >= 7.0f) return 2;
    if (iwar >= 3.0f) return 1;
    return 0;
}

static const char* recruit_tier(f32 twar) {
    if (twar >= 9.0f) return "up to Tier 3 (sub-captain)";
    if (twar >= 4.0f) return "up to Tier 2 (unique player)";
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
    career_log("Final: %d-%d %s", lbl_80353A90.runs[0][0], lbl_80353A90.runs[1][0],
               lbl_80353A90.winner == 0 ? "WIN" : (lbl_80353A90.winner == 1 ? "LOSS" : "TIE"));
    g = score_game(sMySlot);
    career_log("  iWAR %.2f, tWAR %.2f", g.iwar, g.twar);
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
