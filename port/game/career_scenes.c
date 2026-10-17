// Career Mode cutscene script (docs: "MSB Career Mode - Cutscene Script Matrix").
// Your player is silent; 3-6 lines a scene. Toadsworth's announcer lines are Lakitu's.
#include "career_scenes.h"

#include <stddef.h>

enum { T_MARIO, T_PEACH, T_WARIO, T_DK, T_YOSHI, T_BOWSER, T_COUNT }; // career.c TEAM_*

#define MA CHAR_ID_MARIO
#define LU CHAR_ID_LUIGI
#define PE CHAR_ID_PEACH
#define DA CHAR_ID_DAISY
#define YO CHAR_ID_YOSHI
#define BI CHAR_ID_BIRDO
#define WA CHAR_ID_WARIO
#define WL CHAR_ID_WALUIGI
#define DK CHAR_ID_DK
#define DI CHAR_ID_DIDDY
#define BO CHAR_ID_BOWSER
#define JR CHAR_ID_BOWSERJR
#define HB CHAR_ID_BRO_HAMMER
#define DB CHAR_ID_DRYBONES_GRAY
#define END {W_END, NULL}

// ---------------------------------------------------------------- prologue
static const SceneLine sTryout[] = {
    {W_LAKITU, "Welcome, hopefuls, to the Mushroom Kingdom open tryout! The captains are watching from the stands."},
    {W_LAKITU, "One game. Play well, and someone may pick you for the season."},
    {JR, "Tryout? I don't need a tryout. I'm just here to embarrass all of you."},
    {JR, "Especially you, {BODY}. You look like every other {BODY} I've ever beaten."},
    {W_LAKITU, "Er... play ball!"},
    END,
};

static const SceneLine sPickMario[] = {
    {MA, "Wahoo! {NAME}, that was something else!"},
    {LU, "Mario's been watching you all game. He never watches anyone all game."},
    {MA, "Come play with us. But everyone will be watching you now. Ready for that?"},
    {JR, "Hmph. Enjoy it while it lasts, Mario's new pet."},
    END,
};
static const SceneLine sPickPeach[] = {
    {PE, "{NAME}! You played beautifully today."},
    {DA, "Beautifully? They played like a champ! We want you at the castle."},
    {PE, "Our team plays with heart. I think you'll fit right in."},
    {W_LAKITU, "Splendid! The castle team has a new player!"},
    END,
};
static const SceneLine sPickYoshi[] = {
    {YO, "Yoshi! Yoshi!"},
    {BI, "He says you run like a Yoshi. That's the nicest thing he says about anyone."},
    {YO, "(offers you a melon)"},
    {BI, "That means you're on the team. Welcome to Yoshi Park, {NAME}!"},
    END,
};
static const SceneLine sPickWario[] = {
    {WA, "Wah ha ha! Nobody else wants you? Perfect!"},
    {WL, "We'll take the {BODY}. Cheap."},
    {WA, "One coin a season. Not two. ONE. You're welcome."},
    {WA, "And when you're famous, I'm taking all the credit. Wah ha ha!"},
    END,
};
static const SceneLine sPickDK[] = {
    {W_NARR, "The stadium empties. Nobody picked you. You take the long way home, through the jungle."},
    {DI, "(drops from a vine) Hey! You're the {BODY} from the tryout!"},
    {DK, "Oooh oooh! (thumps chest, holds out a banana)"},
    {DI, "DK says the tryout doesn't matter. He liked how you never quit."},
    {DI, "Come on. Welcome to the jungle, {NAME}!"},
    END,
};

// ---------------------------------------------------------------- Mario path
static const SceneLine sM_Yoshi[] = {
    {MA, "First road trip, {NAME}! Yoshi's team is fast. Don't blink."},
    {YO, "Yoshi! (points at you, then at Mario, then laughs)"},
    {BI, "He says Mario picks a new favorite every year. Let's see if you last."},
    END,
};
static const SceneLine sM_YoshiW[] = {{YO, "(sad melon) Yoshi..."}, {MA, "That's how we answer the doubters!"}, END};
static const SceneLine sM_YoshiL[] = {{BI, "Not so special after all."}, {MA, "Shake it off. Every pro loses a series."}, END};
static const SceneLine sM_Peach[] = {
    {PE, "{NAME}, I hoped you'd join us at the castle. Mario got to you first."},
    {MA, "Hey, no hard feelings, Princess! May the best team win."},
    {DA, "Oh, it will. And it's gonna be us."},
    END,
};
static const SceneLine sM_PeachW[] = {{PE, "You've grown so much already. Mario chose well."}, END};
static const SceneLine sM_PeachL[] = {{DA, "Told you!"}, {LU, "Mario's quiet. That's never good."}, END};
static const SceneLine sM_DK[] = {
    {DK, "OOH OOH! (pounds the ground)"},
    {DI, "DK wants a rematch from last year. You're just in the way, {NAME}."},
    {MA, "Last year we won by one run. This year, let's make it more."},
    END,
};
static const SceneLine sM_DKW[] = {{DI, "That {BODY} is the real deal, DK."}, {DK, "(grumbles, eats banana)"}, END};
static const SceneLine sM_DKL[] = {{MA, "The jungle got us. Next chapter, we're back."}, END};
static const SceneLine sM_Wario[] = {
    {WA, "Mario! And Mario's little helper! Wah ha ha!"},
    {WL, "I hear the crowd thinks the {BODY} is carrying you now, Mario."},
    {MA, "Good. That means it's working."},
    END,
};
static const SceneLine sM_WarioW[] = {{WA, "I want a rematch! And a refund!"}, {MA, "Kingdom Cup, here we come!"}, END};
static const SceneLine sM_WarioL[] = {{WL, "Wah! The great Mario, beaten!"}, {MA, "One more push, {NAME}. The season's not over."}, END};

// ---------------------------------------------------------------- Peach path
static const SceneLine sP_Yoshi[] = {
    {PE, "Our first trip together, {NAME}! Yoshi's team is lovely, but they never stop running."},
    {DA, "So we run faster. Easy."},
    {YO, "Yoshi! (bows to Peach, sticks tongue out at you)"},
    END,
};
static const SceneLine sP_YoshiW[] = {{DA, "See? Easy!"}, {PE, "I knew you'd fit in."}, END};
static const SceneLine sP_YoshiL[] = {{PE, "It's all right. A castle isn't built in a day."}, END};
static const SceneLine sP_Mario[] = {
    {MA, "Princess! And the {BODY} from the tryout. I almost picked you, {NAME}."},
    {DA, "Almost doesn't count, Mario."},
    {PE, "Let's show him what he passed up."},
    END,
};
static const SceneLine sP_MarioW[] = {{LU, "Mario, I think we made a mistake."}, {MA, "Mamma mia..."}, END};
static const SceneLine sP_MarioL[] = {{MA, "Good series! But this is still my stadium."}, {PE, "We'll be back, Mario."}, END};
static const SceneLine sP_DK[] = {
    {W_LAKITU, "Princess, the jungle is no place for royalty! Mind the bananas!"},
    {DI, "Royal visit! DK, get the good bananas!"},
    {DK, "(offers Peach a banana, ignores you entirely)"},
    END,
};
static const SceneLine sP_DKW[] = {{DA, "That's how a princess plays the jungle!"}, {DK, "(sulks in a tree)"}, END};
static const SceneLine sP_DKL[] = {{W_LAKITU, "I did say mind the bananas."}, END};
static const SceneLine sP_Wario[] = {
    {WA, "Princess! Your team's worth a fortune. How much for the {BODY}?"},
    {PE, "{NAME} is not for sale, Wario."},
    {WL, "Everyone's for sale! Wah!"},
    END,
};
static const SceneLine sP_WarioW[] = {{PE, "Some things money can't buy."}, {DA, "Like that series!"}, END};
static const SceneLine sP_WarioL[] = {{WA, "Wah ha ha! Ka-ching!"}, {PE, "Chin up, {NAME}. The Cup is what matters."}, END};

// ---------------------------------------------------------------- Yoshi path
static const SceneLine sY_Peach[] = {
    {BI, "Road trip! Yoshi packed nothing but fruit."},
    {PE, "Yoshi, you brought the speedy {BODY}! We nearly asked first."},
    {YO, "(hides you behind his back) Yoshi!"},
    END,
};
static const SceneLine sY_PeachW[] = {{BI, "Family wins together!"}, {PE, "You've found a good home, {NAME}."}, END};
static const SceneLine sY_PeachL[] = {{YO, "(shares his last melon with you)"}, {BI, "That's Yoshi for 'we will get them next time.'"}, END};
static const SceneLine sY_Mario[] = {
    {MA, "Yoshi, old buddy! Ready to lose at my place?"},
    {YO, "(flutter-jumps in place, very offended)"},
    {BI, "Mario rode Yoshi for years. Tonight Yoshi rides you, Mario."},
    END,
};
static const SceneLine sY_MarioW[] = {{MA, "You've got a real gem there, Yoshi."}, {YO, "YOSHI!"}, END};
static const SceneLine sY_MarioL[] = {{BI, "Mario's lucky. That's all. Right, {NAME}?"}, END};
static const SceneLine sY_DK[] = {
    {DI, "Yoshi! Wanna trade? Fruit for bananas?"},
    {YO, "(already eating Diddy's bananas)"},
    {DK, "OOH! (that's a declaration of war)"},
    END,
};
static const SceneLine sY_DKW[] = {{BI, "We ate their snacks AND won the series."}, {DI, "Not cool!"}, END};
static const SceneLine sY_DKL[] = {{DK, "(takes his bananas back, one by one)"}, END};
static const SceneLine sY_Wario[] = {
    {WA, "A dinosaur, a pink dinosaur, and a {BODY}. What a circus!"},
    {BI, "Excuse me? Pink is a power color."},
    {YO, "(stares Wario down, chewing slowly)"},
    END,
};
static const SceneLine sY_WarioW[] = {{WL, "Beaten by a fruit stand!"}, {BI, "Kingdom Cup, baby!"}, END};
static const SceneLine sY_WarioL[] = {{WA, "Wah ha ha! Back to the swamp!"}, {BI, "We're not done, {NAME}."}, END};

// ---------------------------------------------------------------- Wario path
static const SceneLine sW_Yoshi[] = {
    {WA, "Listen up, one-coin wonder. Yoshi's team is all legs. Run faster than a dinosaur."},
    {WL, "Or trip them. Trip works too."},
    {BI, "Wario got the {BODY} nobody wanted? Cute."},
    END,
};
static const SceneLine sW_YoshiW[] = {{WA, "Wah ha ha! Best coin I ever spent!"}, {WL, "You spent a coin?"}, END};
static const SceneLine sW_YoshiL[] = {{WA, "I want my coin back! ...Fine. Keep it. For now."}, END};
static const SceneLine sW_Peach[] = {
    {PE, "Wario, be nice to {NAME}. They deserve better than one coin."},
    {WA, "Better? They get to wear the W! Priceless!"},
    {DA, "I'd have picked you, {NAME}. Just saying."},
    END,
};
static const SceneLine sW_PeachW[] = {{WA, "You hear that, Princess? MY bargain!"}, {PE, "You have a good player, Wario. Pay them more."}, END};
static const SceneLine sW_PeachL[] = {{WL, "Beaten by flowers. Wah!"}, {WA, "Nobody saw that. NOBODY."}, END};
static const SceneLine sW_Mario[] = {
    {WA, "MARIO! I have waited all season for this!"},
    {MA, "Wario! Is that the {BODY} you got for a coin? Lucky find."},
    {WA, "Lucky? I am a GENIUS. Win this, and I'll double your pay. Two coins!"},
    END,
};
static const SceneLine sW_MarioW[] = {{WA, "WAH HA HA! TWO COINS! ...Okay, one and a half."}, {MA, "Mamma mia, that kid's good."}, END};
static const SceneLine sW_MarioL[] = {{MA, "Good effort, Wario!"}, {WA, "(smashes his own cap)"}, END};
static const SceneLine sW_DK[] = {
    {WL, "Last stop before the Cup. Monkeys. Ugh."},
    {DI, "We heard about you, {NAME}. Wario actually smiles now. It's creepy."},
    {WA, "I do NOT smile. Win, and I'll stop not smiling."},
    END,
};
static const SceneLine sW_DKW[] = {{WA, "(almost smiles) ...Kingdom Cup. Let's go get my trophy. OUR trophy. MY trophy."}, END};
static const SceneLine sW_DKL[] = {{WA, "Bah! Bananas everywhere! We still get the Cup, right? Right?!"}, END};

// ---------------------------------------------------------------- DK path
static const SceneLine sD_Yoshi[] = {
    {DI, "First game since the tryout, {NAME}. Everyone's gonna remember it."},
    {BI, "Oh! The {BODY} who did nothing at the tryout! Hi!"},
    {DK, "(cracks knuckles, stands in front of you)"},
    END,
};
static const SceneLine sD_YoshiW[] = {{DI, "Remember THAT instead!"}, {DK, "OOH OOH! (victory chest pounds)"}, END};
static const SceneLine sD_YoshiL[] = {{DK, "(pats your head, a bit too hard)"}, {DI, "DK says one series at a time."}, END};
static const SceneLine sD_Peach[] = {
    {PE, "DK! And... oh, {NAME}. I'm sorry nobody picked you at the tryout."},
    {DI, "DK picked them. DK's somebody."},
    {DK, "(nods, very seriously)"},
    END,
};
static const SceneLine sD_PeachW[] = {{PE, "I was wrong about you, {NAME}. Everyone was."}, {DI, "Not DK!"}, END};
static const SceneLine sD_PeachL[] = {{DA, "No shame, jungle team."}, {DK, "(shares a banana with you anyway)"}, END};
static const SceneLine sD_Mario[] = {
    {MA, "The tryout stadium! Welcome back, {NAME}."},
    {LU, "Last time here, you couldn't buy a hit."},
    {DI, "Last time, we weren't with them."},
    END,
};
static const SceneLine sD_MarioW[] = {{MA, "I should have picked you. Wahoo, well played!"}, {DK, "(roars at the stands where the tryout was)"}, END};
static const SceneLine sD_MarioL[] = {{DI, "This place again. Next time, {NAME}. Next time."}, END};
static const SceneLine sD_Wario[] = {
    {WA, "Monkey business! Hey, {BODY}, I'd have signed you for a coin. Now you're with apes."},
    {DI, "And you'll lose to the apes."},
    {DK, "(eats Wario's garlic)"},
    END,
};
static const SceneLine sD_WarioW[] = {{WA, "MY GARLIC! MY SERIES!"}, {DI, "Kingdom Cup, here comes the jungle!"}, END};
static const SceneLine sD_WarioL[] = {{WA, "Wah ha ha!"}, {DK, "(silently takes Wario's cap)"}, {DI, "We're still going to the Cup, {NAME}."}, END};

// [your team][opponent team]: arrival, won, lost
static const SceneLine* const sChapter[T_COUNT][T_COUNT][3] = {
    [T_MARIO] = {[T_YOSHI] = {sM_Yoshi, sM_YoshiW, sM_YoshiL}, [T_PEACH] = {sM_Peach, sM_PeachW, sM_PeachL},
                 [T_DK] = {sM_DK, sM_DKW, sM_DKL}, [T_WARIO] = {sM_Wario, sM_WarioW, sM_WarioL}},
    [T_PEACH] = {[T_YOSHI] = {sP_Yoshi, sP_YoshiW, sP_YoshiL}, [T_MARIO] = {sP_Mario, sP_MarioW, sP_MarioL},
                 [T_DK] = {sP_DK, sP_DKW, sP_DKL}, [T_WARIO] = {sP_Wario, sP_WarioW, sP_WarioL}},
    [T_YOSHI] = {[T_PEACH] = {sY_Peach, sY_PeachW, sY_PeachL}, [T_MARIO] = {sY_Mario, sY_MarioW, sY_MarioL},
                 [T_DK] = {sY_DK, sY_DKW, sY_DKL}, [T_WARIO] = {sY_Wario, sY_WarioW, sY_WarioL}},
    [T_WARIO] = {[T_YOSHI] = {sW_Yoshi, sW_YoshiW, sW_YoshiL}, [T_PEACH] = {sW_Peach, sW_PeachW, sW_PeachL},
                 [T_MARIO] = {sW_Mario, sW_MarioW, sW_MarioL}, [T_DK] = {sW_DK, sW_DKW, sW_DKL}},
    [T_DK] = {[T_YOSHI] = {sD_Yoshi, sD_YoshiW, sD_YoshiL}, [T_PEACH] = {sD_Peach, sD_PeachW, sD_PeachL},
              [T_MARIO] = {sD_Mario, sD_MarioW, sD_MarioL}, [T_WARIO] = {sD_Wario, sD_WarioW, sD_WarioL}},
};

// ---------------------------------------------------------------- postseason
static const SceneLine sFest[] = {
    {W_LAKITU, "The Star Festival! Every team invites its favorite stars for one night of friendly baseball."},
    {W_VOICE, "Our invites, our rules. Pick a tough crowd, {NAME}. Last chance to sign someone great."},
    END,
};
static const SceneLine sFestW[] = {{W_OPP, "Good game! If you've got a spot, I'm listening."}, END};
static const SceneLine sFestL[] = {{W_OPP, "Fun night! Maybe one of the others wants in."}, END};

static const SceneLine sBowser[] = {
    {W_NARR, "The lights go out. The ground shakes."},
    {BO, "GWAHAHA! A Star Festival, and no invite for the KING?!"},
    {BO, "My team plays you. Right now. Loser cleans up the fireworks!"},
    {W_VOICE, "Where's Junior?"},
    {BO, "He said a game that doesn't count is... pathetic. KIDS!"},
    END,
};
static const SceneLine sBowserW[] = {
    {HB, "You beat the King. I've never seen that. I want to play for a winner."},
    {BO, "TRAITOR!"},
    END,
};
static const SceneLine sBowserL[] = {
    {BO, "GWAHAHA!"},
    {DB, "(rattles over to you) ...Bowser doesn't need me anymore. Can I come?"},
    END,
};
static const SceneLine sJrW[] = {
    {JR, "Papa. You lost to a {BODY}?"},
    {JR, "I'm taking the team for the Kingdom Cup. Real games. Games that count."},
    {BO, "...Okay, Junior. Papa will carry the bats."},
    {JR, "And you, {NAME}. I said at the tryout I'd embarrass you. I meant the Cup."},
    END,
};
static const SceneLine sJrL[] = {
    {JR, "Papa. You beat a {BODY}, and that's it?"},
    {JR, "I'm taking the team for the Kingdom Cup. Real games. Games that count."},
    {BO, "...Okay, Junior. Papa will carry the bats."},
    {JR, "And you, {NAME}. I said at the tryout I'd embarrass you. I meant the Cup."},
    END,
};
static const SceneLine sSeed[] = {
    {W_LAKITU, "The Kingdom Cup! Bowser Jr.'s team takes the top seed. {CAPTAIN}'s team is seed {SEED}!"},
    {W_VOICE, "We're on the other side of the bracket from Junior. Win, and we meet him in the final."},
    END,
};
static const SceneLine sQF[] = {{W_VOICE, "{OPP}'s team. We've seen them before. One game, no second chances."}, END};
static const SceneLine sSF[] = {
    {JR, "Too easy. Hurry up, {NAME}."},
    {W_VOICE, "One win from the final, {NAME}. Junior's already waiting."},
    END,
};
static const SceneLine sFinal[] = {
    {JR, "Too easy. Hurry up, {NAME}."},
    {JR, "My castle. My Cup. You're just one more {BODY}."},
    {BO, "GO, JUNIOR! (waving a giant foam claw)"},
    {W_VOICE, "One of many, Junior. That's what you never got. Play ball!"},
    END,
};
static const SceneLine sOver[] = {
    {W_OPP, "Good game, {NAME}. You made us earn it."},
    {W_VOICE, "We came this far together. Next season, we go all the way."},
    {W_NARR, "Your season ends in the {ROUND}. A new tryout awaits."},
    END,
};
#define CHAMP(name, who, line)                                                                                  \
    static const SceneLine name[] = {                                                                      \
        {JR, "No... I was the one who belonged. Not you."},                                                \
        {W_VOICE, "Kingdom Cup champions! {NAME}, you did this."},                                         \
        {who, line},                                                                                       \
        {W_LAKITU, "And now, a tradition! The champions face the All-Stars, every captain and sub-captain, at Mario Stadium."}, \
        END,                                                                                               \
    }
CHAMP(sChampMario, MA, "Everyone was watching. And you showed them!");
CHAMP(sChampPeach, PE, "I believed in you from the first pitch.");
CHAMP(sChampYoshi, BI, "Yoshi's crying. Happy tears. Mostly melon.");
CHAMP(sChampWario, WA, "Best coin I EVER spent! ...You're getting two now. Don't push it.");
CHAMP(sChampDK, DI, "Nobody picked you. DK did. Now look at us!");
static const SceneLine sEpilogue[] = {
    {MA, "That's the best I've seen from a {BODY}. From anyone."},
    {PE, "The Kingdom has a new captain. If you'll have the job."},
    {W_VOICE, "You started as one of many. Now there's only one {NAME}."},
    {W_NARR, "{NAME}, Captain. The end. Play again to build a new legend."},
    END,
};

const SceneLine* career_scene_lines(u32 id) {
    u32 kind = id >> 16;
    u32 a = (id >> 8) & 0xFF;
    u32 b = id & 0xFF;
    switch (kind) {
    case SC_TRYOUT: return sTryout;
    case SC_PICK: {
        static const SceneLine* const k[T_COUNT] = {sPickMario, sPickPeach, sPickWario, sPickDK, sPickYoshi, NULL};
        return a < T_COUNT ? k[a] : NULL;
    }
    case SC_ARRIVE: return (a < T_COUNT && b < T_COUNT) ? sChapter[a][b][0] : NULL;
    case SC_RESULT: {
        u32 opp = b & 0x7F;
        return (a < T_COUNT && opp < T_COUNT) ? sChapter[a][opp][(b & 0x80) ? 1 : 2] : NULL;
    }
    case SC_FEST: return sFest;
    case SC_FEST_END: return b ? sFestW : sFestL;
    case SC_BOWSER: return sBowser;
    case SC_BOWSER_END: return b ? sBowserW : sBowserL;
    case SC_JR: return b ? sJrW : sJrL;
    case SC_SEED: return sSeed;
    case SC_ROUND: return b == 0 ? sQF : sSF;
    case SC_FINAL: return sFinal;
    case SC_OVER: return sOver;
    case SC_CHAMP: {
        static const SceneLine* const k[T_COUNT] = {sChampMario, sChampPeach, sChampWario, sChampDK, sChampYoshi, NULL};
        return a < T_COUNT ? k[a] : NULL;
    }
    case SC_EPILOGUE: return sEpilogue;
    }
    return NULL;
}
