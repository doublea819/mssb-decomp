// user.ini: PC-only options (`key = value` lines, `#`/`;` comments, `[section]`
// headers ignored). Path: $MSSB_USER_INI, else <user data folder>/user.ini.
//
//   skipfe = true        boot straight into an exhibition game (no menus)
//   captain1 = mario     team captains (character names, see port/game/skipfe.c)
//   captain2 = bowser
//   team1 = monty,toad  other players of team 1 (test option; team2 likewise)
//   stadium = mario      mario, bowser, wario, yoshi, peach, dk (or 0..5)
//   unlockall = false    keep the save's character/star unlocks (default: all unlocked)
//   innings = 3          game length (1, 3, 5, 7 or 9)
//   human2 = true        a human on port 2 plays team 2 (online play)
//   seed = 12345         seed for the random team picks (online play)
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 64

static struct {
    char key[32];
    char value[64];
} s_entries[MAX_KEYS];
static int s_count;

static char* trim(char* s)
{
    while (isspace((unsigned char)*s))
        s++;
    char* e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1]))
        *--e = '\0';
    return s;
}

static char s_userPath[1024];

// The user data folder (saves, user.ini, career.sav).
const char* port_user_path(void)
{
    return s_userPath;
}

void port_user_ini_load(const char* userPath)
{
    char path[1024];
    if (userPath != NULL)
        snprintf(s_userPath, sizeof(s_userPath), "%s", userPath);
    const char* env = getenv("MSSB_USER_INI");
    if (env != NULL)
        snprintf(path, sizeof(path), "%s", env);
    else if (userPath != NULL)
        snprintf(path, sizeof(path), "%s/user.ini", userPath);
    else
        return;
    FILE* f = fopen(path, "r");
    if (f == NULL)
        return;
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL && s_count < MAX_KEYS)
    {
        char* l = trim(line);
        if (*l == '\0' || *l == '#' || *l == ';' || *l == '[')
            continue;
        char* eq = strchr(l, '=');
        if (eq == NULL)
            continue;
        *eq = '\0';
        snprintf(s_entries[s_count].key, sizeof(s_entries[0].key), "%s", trim(l));
        snprintf(s_entries[s_count].value, sizeof(s_entries[0].value), "%s", trim(eq + 1));
        s_count++;
    }
    fclose(f);
    fprintf(stderr, "[port] user.ini: %s (%d settings)\n", path, s_count);
}

const char* port_user_ini_get(const char* key)
{
    for (int i = 0; i < s_count; i++)
        if (strcasecmp(s_entries[i].key, key) == 0)
            return s_entries[i].value;
    return NULL;
}

int port_user_ini_bool(const char* key)
{
    const char* v = port_user_ini_get(key);
    return v != NULL && (strcasecmp(v, "true") == 0 || strcasecmp(v, "yes") == 0 || strcmp(v, "1") == 0);
}
