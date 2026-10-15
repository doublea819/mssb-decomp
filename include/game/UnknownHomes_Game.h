#ifndef __UNKNOWN_HOMES_GAME_H_
#define __UNKNOWN_HOMES_GAME_H_

#include "mssbTypes.h"
#include "Dolphin/pad.h"

#define SQRT2_LINKAGE extern
#include "math.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"

#define SINF(x) ((f32)sin(x))
#define COSF(x) ((f32)cos(x))
#define ATAN2F(y, x) ((f32)atan2((y), (x)))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define BATTER_MAX_CHARGE (1.f)
#define BATTER_MIN_CHARGE (0.f)
#define PLAYERS_PER_TEAM (9)
#define TEAMS_PER_GAME (2)

#define VEC_ADD(dst, a, b)  \
(dst)->x = (a)->x + (b)->x; \
(dst)->y = (a)->y + (b)->y; \
(dst)->z = (a)->z + (b)->z

#define VEC_SUB(dst, a, b)  \
(dst)->x = (a)->x - (b)->x; \
(dst)->y = (a)->y - (b)->y; \
(dst)->z = (a)->z - (b)->z

#define VEC_SCALE(dst, src, scale) \
(dst)->x = (src)->x * (scale); \
(dst)->y = (src)->y * (scale); \
(dst)->z = (src)->z * (scale)

#define VEC_MULT(dst, a, b) \
(dst)->x = (a)->x * (b)->x; \
(dst)->y = (a)->y * (b)->y; \
(dst)->z = (a)->z * (b)->z

#define VEC_COPY(dst, src) \
(dst)->x = (src)->x; \
(dst)->y = (src)->y; \
(dst)->z = (src)->z

#define VEC_DISTANCE(a, b) \
dolsqrtf2(                 \
    SQ((a)->x - (b)->x) +  \
    SQ((a)->y - (b)->y) +  \
    SQ((a)->z - (b)->z))

#define VEC_DISTANCE_XZ(a, b) \
dolsqrtf2(                 \
    SQ((a)->x - (b)->x) +  \
    SQ((a)->z - (b)->z))
    
#define VEC_LENGTH(a) \
dolsqrtf2(                 \
    SQ((a)->x) +  \
    SQ((a)->y) +  \
    SQ((a)->z))

#define VEC_LENGTH_XZ(a) \
dolsqrtf2(                 \
    SQ((a)->x) +  \
    SQ((a)->z))

typedef struct _VecXZ {
    f32 x, z;
} VecXZ;

typedef Vec VecXYZ; // same object as Dolphin Vec

typedef struct _Orientationf {
    s16 yaw, pitch, roll;
} Orientationf;

typedef struct _InMemBatterType {
    /*0x00*/ VecXZ batterPos;
    /*0x08*/ VecXYZ batPosition; // with x offset
    artificial_padding(0x08, 0x24, VecXYZ);
    /*0x24*/ VecXYZ hitContactPos;
    /*0x30*/ f32 rightNiceThreshold[4];
    /*0x40*/ f32 contactQualityAbsolute;
    /*0x44*/ f32 contactQuality;
    /*0x48*/ f32 predictedPitchXWhenBallReachesBatter;
    /*0x4C*/ VecXYZ batPosition2;
    /*0x58*/ f32 chargeUp;
    /*0x5C*/ f32 chargeDown;
    /*0x60*/ s16 rosterID;
    /*0x62*/ E(s16, CHAR_ID) charID;
    /*0x64*/ s16 charIDForScoutFlagMission;
    /*0x66*/ s16 framesSinceStartOfSwing;
    /*0x68*/ s16 frameSwung;
    /*0x6A*/ s16 framesBuntHeld;
    // min Frames Until Can Swing Again: [0]slap [1]charge/Star
    /*0x6C*/ s16 frameDelay[2];
    /*0x70*/ s16 frameFullyCharged;
    /*0x72*/ s16 frameChargeDownBegins;
    /*0x74*/ s16 chargeFrames;
    /*0x76*/ s16 _76;
    /*0x78*/ u8 aiControlledInd;
    /*0x79*/ u8 aiLevel;
    /*0x7A*/ u8 easyBatting;
    /*0x7B*/ E(u8, BATTING_HAND) batterHand;
    /*0x7C*/ u8 hitPower_raw[2];
    /*0x7E*/ u8 contactSize_raw[2];
    /*0x80*/ u8 hitPower_capped[2];
    /*0x82*/ u8 contactSize_capped[2];
    /*0x84*/ u8 buntingContactSize;
    /*0x85*/ u8 trajectoryPushPull;
    /*0x86*/ u8 trajectoryHighLow;
    /*0x87*/ u8 captainStarHitPitch;
    /*0x88*/ E(u8, REGULAR_STAR_SWING) noncaptainStarSwing;
    /*0x89*/ E(u8, CHARACTER_CLASS) characterClass;
    /*0x8A*/ bool trimmedBat;
    /*0x8B*/ E(u8, BAT_CONTACT_TYPE) hitGeneralType;
    /*0x8C*/ u8 _8C;
    /*0x8D*/ u8 swingInd;
    /*0x8E*/ u8 isBunting;
    /*0x8F*/ E(u8, BUNT_STATUS) buntStatus;
    /*0x90*/ u8 missedBuntStatus;
    /*0x91*/ u8 contactMadeInd;
    /*0x92*/ E(u8, HIT_CONTACT_TYPE) contactType;
    /*0x93*/ u8 hitByPitch;
    /*0x94*/ E(u8, HIT_TRAJECTORY) hitTrajectory;
    /*0x95*/ u8 _95; // always0_cutHitPowerInHalf
    /*0x96*/ u8 _96;
    /*0x97*/ u8 displayContactSprite; // displays nice/perfect on screen
    /*0x98*/ u8 _98;
    /*0x99*/ E(u8, DID_SWING_TYPE) missSwingOrBunt;
    /*0x9A*/ u8 noSwingAnimationInd;
    /*0x9B*/ u8 Stored_Frame_SwingContact_SinceMiss;
    /*0x9C*/ u8 _9C;
    /*0x9D*/ E(u8, CHARGE_SWING_STAGE) chargeStatus;
    /*0x9E*/ bool isFullyCharged;
    /*0x9F*/ u8 countUpUntilChargeEnables;
    /*0xA0*/ bool didNonCaptainStarSwingConnect;
    /*0xA1*/ bool isStarSwing;
    /*0xA2*/ E(u8, CAPTAIN_STAR_TYPE) captainStarSwingActivated;
    /*0xA3*/ u8 lightFireballStunID;
    /*0xA4*/ u8 starSwing_starsHaveBeenSpent;
    /*0xA5*/ bool moonShotInd;
    /*0xA6*/ u8 beginningOfABAnimationOccuring;
    /*0xA7*/ u8 batterIsBeingCentredInd;
    /*0xA8*/ u8 invisibleBallForPeachStarHit;
    /*0xA9*/ E(u8, STICK_SIDEWAYS_INPUT) inputDirection;
    /*0xAA*/ u8 chemLinksOnBase;
    /*0xAB*/ u8 runnersOnBase;
    /*0xAC*/ E(s8, HIT_TYPE) hitType;
    /*0xAD*/ E(u8, BALL_HITTABLE) isBallInHittableZone;
    /*0xAE*/ u8 swingMissThatWasHittable;
    /*0xAF*/ E(u8, REGULAR_STAR_SWING) nonCaptainStarSwingActivated;
} InMemBatterType; // size: 0xb0

typedef struct _InMemRunnerType {
    /*0x000*/ VecXYZ position;
    /*0x00C*/ VecXYZ positionStored;
    /*0x018*/ VecXYZ velocity;
    /*0x024*/ VecXYZ velocityStored;
    /*0x030*/ f32 runningAngle;
    /*0x034*/ f32 angleToBall;
    /*0x038*/ f32 distanceFromBall;
    /*0x03C*/ VecXYZ currentBaseCoordinates;
    /*0x048*/ VecXYZ nextBaseCoordinates;
    /*0x054*/ f32 slidingAdjustment_backwards; // 0.03f
    /*0x058*/ f32 slidingAdjustment_forwards;  // 0.03f
    /*0x05C*/ f32 percentFromCurrentBase_slideAdj;
    /*0x060*/ f32 percentTowardsNextBase_slideAdj;
    /*0x064*/ f32 fractionalBasesRan;
    /*0x068*/ f32 percentTowardsNextBase;
    /*0x06C*/ f32 calculatedLengthOfCurrentBaseline;
    /*0x070*/ f32 fractionOfCalculatedBaselineRan;
    /*0x074*/ f32 distToCurrentBase;
    /*0x078*/ f32 distToNextBase;
    /*0x07C*/ f32 fractionalBasesRan_stored;
    /*0x080*/ f32 percentTowardsNextBase_stored;
    /*0x084*/ f32 groundVelocity[4];
    /*0x094*/ f32 acceleration;
    /*0x098*/ f32 baseAcceleration;                        // between 0.005 and 0.01
    /*0x09C*/ f32 baseAccelerationWhileChaingingDirection; // 0.005
    /*0x0A0*/ f32 maximumBaseVelocity;
    /*0x0A4*/ f32 percentRanPerFrame_slideAdj;
    /*0x0A8*/ f32 velocityPercent_stamAdj;
    /*0x0AC*/ f32 accelerationPercent_stamAdj;
    /*0x0B0*/ f32 roundingStrengthPercent;                    // unsure
    /*0x0B4*/ f32 overrun1B_someDistConst_proportionPerFrame; // maybe
    /*0x0B8*/ f32 overrun1B_somePositionControl;
    /*0x0BC*/ f32 leadoffDistancePercent;
    /*0x0C0*/ f32 mashVeloAdjustment;
    /*0x0C4*/ f32 maxMashVeloAdjustment; // 0.02
    /*0x0C8*/ f32 mashPercent;
    /*0x0CC*/ f32 percentAddedPerMash;                  // 0.2
    /*0x0D0*/ f32 stamina_MashPercentTakenAwayPerFrame; // 0.2
    /*0x0D4*/ f32 staminaMult;
    /*0x0D8*/ f32 accelerationStaminaEffect;
    /*0x0DC*/ f32 accelerationStaminaEffectWhileChangingDirection;
    /*0x0E0*/ s16 rosterID;
    /*0x0E2*/ s16 charID;
    /*0x0E4*/ s16 unused_starMissionCharID;
    /*0x0E6*/ s16 baseStandingOn;
    /*0x0E8*/ s16 baseStandingOn_Stored;
    /*0x0EA*/ s16 framesToNextBase;
    /*0x0EC*/ s16 framesToPreviousBase; // maybe
    /*0x0EE*/ E(s16, FORCE_OUT_TYPE) forceOutCd;
    /*0x0F0*/ E(s16, PREVENT_PASSING_TYPE) restrictedMovementCodes;
    /*0x0F2*/ E(s16, PREVENT_PASSING_TYPE) restrictedMovementCodes_stored;
    /*0x0F4*/ s16 framesSinceOut;
    /*0x0F6*/ s16 stamina;
    /*0x0F8*/ s16 baseNumberEarned_NotIncludingFieldersChoice;
    /*0x0FA*/ s16 timeStandingOnBase;
    /*0x0FC*/ s16 pitcherWhoLetRunnerOnBase;
    /*0x0FE*/ s16 baseReachedAtTimeOfThrow;
    /*0x100*/ s16 actionFrames_countUp;
    /*0x102*/ s16 actionFrames_countDown;
    /*0x104*/ s16 overrunBaseFrames_countUp;
    /*0x106*/ s16 overrunBaseFrames_countDown;
    /*0x108*/ s16 runningToDugoutFrameCounter;
    /*0x10A*/ s16 framesToReachDugout; // maybe
    /*0x10C*/ s16 leadoffDurationFrames;
    /*0x10E*/ s16 leadOffTotalFrameCountDown;
    /*0x110*/ s16 _110;
    /*0x112*/ s16 framesSinceLastDirectionChange;
    /*0x114*/ s16 slideHomeFrames_CountDown;
    /*0x116*/ s16 framesSinceStealStarted;
    /*0x118*/ s16 _118;
    /*0x11A*/ u8 unused_batterHandednessForCCS; // maybe
    /*0x11B*/ u8 aIStrength0Special3Weak;
    /*0x11C*/ E(u8, BATTING_HAND) battingHand;
    /*0x11D*/ u8 weight;
    /*0x11E*/ E(u8, CHARACTER_CLASS) characterClass;
    /*0x11F*/ u8 _11f;
    /*0x120*/ u8 speed;
    /*0x121*/ u8 _121; // 10
    /*0x122*/ u8 delayBeforeStartingToRun;
    /*0x123*/ E(u8, RUNNER_STATUS) runnerOnFieldOrOutOrScored;
    /*0x124*/ u8 startingBase_baseAchieved;
    /*0x125*/ u8 currentBase;
    /*0x126*/ u8 nextBase;
    /*0x127*/ u8 baseRunningTowards;
    /*0x128*/ E(u8, TAG_UP_TYPE) tagUpInd;
    /*0x129*/ u8 batterStayInBattersBoxReason;
    /*0x12A*/ u8 unused_AIRelated;
    /*0x12B*/ u8 relatedToRunnerPos;
    /*0x12C*/ u8 outType;
    /*0x12D*/ u8 forcedToAdvanceInd; // maybe
    /*0x12E*/ u8 unused_someBaseNum;
    /*0x12F*/ s8 baseOfFailedBodyCheck; // maybe
    /*0x130*/ u8 tagType;               // 1=Running 2=Sliding
    /*0x131*/ u8 runnerDidntReachOnError;
    /*0x132*/ u8 isEligibleToScore; // maybe
    /*0x133*/ u8 leadOffStatus;
    /*0x134*/ u8 unused_const_1;
    /*0x135*/ u8 runningDirectionDesired;
    /*0x136*/ u8 nextDirectionBeingProcessed;
    /*0x137*/ u8 runningDirectionCode;
    /*0x138*/ u8 runnerDirectionCode_stored;
    /*0x139*/ u8 offsetFromNormalRunningPathInd; // maybe
    /*0x13A*/ u8 actionCode;
    /*0x13B*/ u8 actionInForwardDirectionInd;
    /*0x13C*/ u8 actionStage;
    /*0x13D*/ u8 forceOutType_unsed;
    /*0x13E*/ u8 baseRoundingState;
    /*0x13F*/ u8 overrun1st_doneChecking;
    /*0x140*/ u8 overRun1BStage;
    /*0x141*/ u8 overrunning1BIndicator;
    /*0x142*/ u8 overrunBaseStage;
    /*0x143*/ u8 offsetPositionForRoundingInd;
    /*0x144*/ u8 roundingInitiaializedInd;
    /*0x145*/ u8 runningToDugoutInd;
    /*0x146*/ u8 runningToDugoutStage;
    /*0x147*/ u8 turnaroundCode;
    /*0x148*/ u8 turningAroundInd; // maybe
    /*0x149*/ u8 newButtonThisFrame_forMashPurposes;
    /*0x14A*/ u8 framesSinceLastMash;
    /*0x14B*/ u8 FramesUntilNotSprinting;        // 6?
    /*0x14C*/ u8 someCollisionCheck;             // maybe
    /*0x14D*/ u8 furthestBaseForcedToGoToOnWalk; // steal related
    /*0x14E*/ u8 stealingStatus;
    /*0x14F*/ u8 framesSinceStealInput;
    /*0x150*/ u8 someCountdown_unused;
    /*0x151*/ u8 _151;
    /*0x152*/ u8 miniGamePlayerNum;
    /*0x153*/ u8 scoredOnGRD; // maybe
} InMemRunnerType;            // size: 0x154

typedef struct _CoordAndDist {
    VecXYZ pos;
    f32 dist;
} CoordAndDist;

typedef struct {
    /*0x000*/ VecXYZ startOfWallJumpChecksMaybe[33];
    artificial_padding(0, 0x198, VecXYZ[33]);
    /*0x198*/ VecXYZ velocity;
    /*0x1A4*/ VecXYZ acceleration;
    /*0x1B0*/ f32 gravity; // 0.00275f
    /*0x1B4*/ f32 threeFrameLookback[2];
    /*0x1BC*/ f32 twoFrameLookback[2];
    /*0x1C4*/ f32 throwYAtSelectedFuturePoint;
    /*0x1C8*/ VecXZ ballLandingSpotOrHeldSpot;
    /*0x1D0*/ f32 hitLandingSpotDistFromHome;
    /*0x1D4*/ CoordAndDist futureCoordsAndDist[360];
} pastAndFutureCoordsWallJumpRelated;

typedef struct _matchShorts {
    /*0x00*/ s16 framesAfterReceivingThrow; // unsure
    /*0x02*/ s16 ballAndFielderOnBaseFrames;
    /*0x04*/ s16 ballOverWallFrames;
    /*0x06*/ Orientationf ballSpinAngle;
    /*0x0C*/ s16 _0C;
    /*0x0E*/ s16 framesSinceFoulCalled;
    /*0x10*/ s16 framesSinceLastThrow; // unsure
    /*0x12*/ s16 framesOnGround;
    /*0x14*/ s16 bananaHitStartFrame;
    /*0x16*/ s16 bananaHitEndFrame;
    /*0x18*/ s16 garlicHitFramesUntilHitGroundForSplit;
    /*0x1A*/ s16 garlicHitFramesSinceSplit;
    /*0x1C*/ s16 framesInsidePlant;
} matchShorts;

typedef enum{
    /* 0x0*/ BALL_STATE_HIT,
    /* 0x1*/ BALL_STATE_HELD,
    /* 0x2*/ BALL_STATE_THROWN,
    /* 0x3*/ BALL_STATE_LOOSE,
} BallStateE;

typedef struct _InMemBallType {
    /*0x0000*/ VecXYZ AtBat_Contact_BallPos;
    /*0x000C*/ VecXYZ offsetWhilePickedUpHistory[4];
    /*0x003C*/ VecXYZ pastCoordinates[27];
    /*0x0180*/ pastAndFutureCoordsWallJumpRelated physicsSubstruct;
    /*0x19D4*/ f32 maxYOfHit;
    /*0x19D8*/ VecXZ ballWillHitBallPos;
    /*0x19E0*/ f32 wallAndBallIntersectionDistFromHome;
    /*0x19E4*/ f32 _19E4;
    /*0x19E8*/ f32 _19E8;
    /*0x19EC*/ VecXYZ throwDestination;
    /*0x19F8*/ VecXZ throwTarget;
    /*0x1A00*/ f32 ballDistanceFromHome;
    /*0x1A04*/ f32 ballDistanceFromBase[4];
    /*0x1A14*/ f32 ballVelocity;
    /*0x1A18*/ VecXZ ballVelocityPercent;
    /*0x1A20*/ f32 ballHitGrroundDistanceFromHome;
    /*0x1A24*/ f32 distLandingSpotToMound;
    /*0x1A28*/ f32 groundYForBounces;
    /*0x1A2C*/ VecXZ landingSpotLocation;
    /*0x1A34*/ VecXZ throwStartingLocation;
    /*0x1A3C*/ VecXYZ deadballLastLoc;
    /*0x1A48*/ f32 someYCoord;
    /*0x1A4C*/ f32 throwDistance;
    /*0x1A50*/ VecXZ ballPickedUpCaught;
    /*0x1A58*/ f32 ballEnergy;
    /*0x1A5C*/ f32 hittingAddedGravityFactor;
    /*0x1A60*/ VecXZ savedVelocity;
    /*0x1A68*/ VecXYZ warioStarHitCoords[15];
    /*0x1B1C*/ VecXZ peachDaisyStarHitFielderLoc;
    /*0x1B24*/ VecXZ unused_garlicHitRelated;
    /*0x1B2C*/ VecXYZ diveCatchLocationOffset;
    /*0x1B38*/ VecXYZ fielderActionCatchCoords;
    /*0x1B44*/ s32 collisionCode;
    /*0x1B48*/ s32 maybeCollisionRelated; // previous frame's collisionCode
    /*0x1B4C*/ s32 StaticRandomInt1;
    /*0x1B50*/ s32 StaticRandomInt2;
    /*0x1B54*/ u32 StaticRandomInt1_prePitch;
    /*0x1B58*/ s16 airResistance; // 40
    /*0x1B5A*/ s16 _1B58;
    /*0x1B5C*/ s16 frameBallWillHitWall; // unused
    /*0x1B5E*/ s16 hangtimeOfHit;
    /*0x1B60*/ s16 framesUntilBallHitsGround;
    /*0x1B62*/ s16 framesUntilThrowReachesDest;
    /*0x1B64*/ s16 totalFramesAtPlay;
    /*0x1B66*/ s16 framesSinceHit; // +100 For Pickoff
    /*0x1B68*/ s16 pitchHangtimeCounter;
    /*0x1B6A*/ s16 postPitchResultCounter;
    /*0x1B6C*/ s16 framesSinceThrowStarted;
    /*0x1B6E*/ s16 timeSinceBallPickedUp;
    /*0x1B70*/ s16 framesSincePickOff;
    /*0x1B72*/ s16 framesSinceBallHitGroundOrWasCaught;
    /*0x1B74*/ s16 framesSinceLastBounce;
    /*0x1B76*/ s16 framesSinceBallHitWall;
    /*0x1B78*/ s16 fielderWBallIndex;
    /*0x1B7A*/ E(s16, BALL_RESULT_TYPE) AtBat_ContactResult;
    /*0x1B7C*/ s16 fairBallInd;
    /*0x1B7E*/ s16 fielderAboutToGetBall_hasBall;
    /*0x1B80*/ sAng ballAngleFromHome;
    /*0x1B82*/ sAng ballTravelAngle;
    /*0x1B84*/ s16 landingSpotAngle;
    /*0x1B86*/ s16 baseBallAndFielderAreOn;
    /*0x1B88*/ s16 _1B88; // -1
    /*0x1B8A*/ s16 fielderBeingThrownTo;
    /*0x1B8C*/ s16 ballBounceState; // unsure
    /*0x1B8E*/ s16 fielderWithBallIndexStored;
    /*0x1B90*/ s16 fielderWithBallIndexStored2;
    /*0x1B92*/ s16 fielderWhoGotLastOut; // unsure
    /*0x1B94*/ s16 throwingFielder;      // unsure, Maybe Cut off Related
    /*0x1B96*/ s16 collisionRelated;
    /*0x1B98*/ s16 _1B98; // unused_frameHitGetsAboveY=1.3
    /*0x1B9A*/ s16 Hit_VerticalAngle;
    /*0x1B9C*/ sAng Hit_HorizontalAngle;
    /*0x1B9E*/ s16 Hit_HorizontalPower; // bODBasePoints
    /*0x1BA0*/ matchShorts matchFramesAndBallAngle;
    /*0x1BBE*/ u8 ballZoneAwayFromHome;
    /*0x1BBF*/ u8 landingSpotZoneAwayFromHome;
    /*0x1BC0*/ u8 _1BC0; // seeminglyAlways1_ballCollideWallRelated;
    /*0x1BC1*/ u8 someCollisionVariable;
    /*0x1BC2*/ u8 thrownBallHasHitGround;
    /*0x1BC3*/ u8 hitClassification1;
    /*0x1BC4*/ u8 hitClassification2;
    /*0x1BC5*/ u8 hitClassification3;
    /*0x1BC6*/ u8 ballInitialHitDoneInd;
    /*0x1BC7*/ u8 howFoulTheBallWillBe;
    /*0x1BC8*/ u8 always0_fairFoulRelated;
    /*0x1BC9*/ E(u8, BallStateE) ballState;
    /*0x1BCA*/ u8 ballIsLooseInd_unused;
    /*0x1BCB*/ u8 IsAntichemistryThrow;
    /*0x1BCC*/ u8 hitWallInd;
    /*0x1BCD*/ u8 homeRunClassification;
    /*0x1BCE*/ u8 lineDriveThroughPitcherInd;
    /*0x1BCF*/ u8 maybeBuntInd;
    /*0x1BD0*/ u8 groundRuleDoubleInd; // unsure
    /*0x1BD1*/ u8 deadBallReason;
    /*0x1BD2*/ u8 deadBallRBIsAddedInd;
    /*0x1BD3*/ u8 maybebuntOn2Strikes;
    /*0x1BD4*/ u8 ballOnMoundInd;
    /*0x1BD5*/ u8 throwHasLastedEstimatedNOfFrames;
    /*0x1BD6*/ u8 framesOnGroundUntilPickedUp;
    /*0x1BD7*/ u8 numberOfThrowsDuringPlay;
    /*0x1BD8*/ u8 numFieldersWhoHandledBallDuringPlay;
    /*0x1BD9*/ u8 numThrowsDuringPlay;
    /*0x1BDA*/ u8 bobbleLocation_1fair_2foul;
    /*0x1BDB*/ u8 _1BDB;
    /*0x1BDC*/ u8 homeRunInd;
    /*0x1BDD*/ s8 ballZoneWhenCaught; // -1: none
    /*0x1BDE*/ u8 ballStoppingCode1ReallySlow2Stopped;
    /*0x1BDF*/ u8 _1BDF;
    /*0x1BE0*/ u8 throwTimeEstimatesCompleteInd;
    /*0x1BE1*/ u8 looseBall_codeForHowLongUntilSomeoneWillGetIt; // unsure
    /*0x1BE2*/ u8 ballZoneFromHomeAtStartOfThrow;
    /*0x1BE3*/ u8 looseBall_5FrameCountdown;
    /*0x1BE4*/ u8 ballIsRollingIndicator;
    /*0x1BE5*/ u8 inAirOrBefore2ndBounceOrLowBallEnergy;
    /*0x1BE6*/ u8 hardHitIndicator;
    /*0x1BE7*/ u8 currentStarSwing;
    /*0x1BE8*/ u8 currentStarSwing2;
    /*0x1BE9*/ u8 directionOfBananaHit;
    /*0x1BEA*/ u8 knockoutProcessedFlag;
    /*0x1BEB*/ u8 warioWaluGarlicIsActive;
    /*0x1BEC*/ u8 warioWaluStarHitDirection;
    /*0x1BED*/ u8 autoFielderAvoidDropSpotForPeachesStarHit;
    /*0x1BEE*/ u8 bODQualifyingHitInd;
    /*0x1BEF*/ u8 fielderActionOccuring;
    /*0x1BF0*/ u8 catchAnimationTotalFrames;
    /*0x1BF1*/ u8 someCollisionInd;
    /*0x1BF2*/ u8 hitNoteBlockInd;
    /*0x1BF3*/ u8 pauseBallMovementWhenInPlant;
    /*0x1BF4*/ u8 ballCughtByPlantInd;
    /*0x1BF5*/ u8 frameCountdownAfterLeavingPlant;
} InMemBallType; // size: 0x1BF8

typedef enum {
    /* 0x0 */ PITCHER_ACTION_STATE_NONE,
    /* 0x0 */ PITCHER_ACTION_STATE_TRANSITION = PITCHER_ACTION_STATE_NONE,
    /* 0x1 */ PITCHER_ACTION_STATE_PRE_PITCH,
    /* 0x2 */ PITCHER_ACTION_STATE_WINDUP,
    /* 0x3 */ PITCHER_ACTION_STATE_IN_AIR,
    /* 0x4 */ PITCHER_ACTION_STATE_NO_CONTACT,
    /* 0x5 */ PITCHER_ACTION_STATE_HIT,
    /* 0x6 */ PITCHER_ACTION_STATE_POST_HIT,
    /* 0x7 */ PITCHER_ACTION_STATE_HIT_BY_PITCH,
} PITCHER_ACTION_STATE;

typedef struct _InMemPitcherType {
    /*0x000*/ VecXYZ ballCurrentPosition;
    /*0x00C*/ VecXYZ ballLastPosition;
    /*0x018*/ VecXYZ ballVelocity;
    /*0x024*/ f32 pitchStartingPosition_AIMaxCurve; // unsure
    /*0x028*/ f32 eggBallBounceYHeight;             // unsure
    /*0x02C*/ f32 frontOfPlateZ;                    // unsure
    /*0x030*/ VecXYZ _30;
    /*0x03C*/ f32 _3C[6];
    /*0x054*/ VecXZ estimatedEndingPos;
    /*0x05C*/ f32 pitchCurveVeloV1;
    /*0x060*/ f32 _60;
    /*0x064*/ f32 pitchCurveVeloV2;
    /*0x068*/ f32 _68;
    /*0x06C*/ VecXZ pitcherCoord;
    /*0x074*/ VecXZ centerOfStrikeZone;
    /*0x07C*/ f32 strikeZoneLeft;
    /*0x080*/ f32 strikeZoneRight;
    /*0x084*/ f32 beginningOfStrikeCheckZ; // 1.05
    /*0x088*/ f32 endingOfStrikeCheckZ;    // 0.5
    /*0x08C*/ VecXZ pitcher;
    /*0x094*/ VecXYZ pitchRelease;
    /*0x0A0*/ f32 pitchLinearInterpolateX;
    /*0x0A4*/ f32 pitchLinearInterpolateY;
    /*0x0A8*/ f32 frontOfPlateZ2;
    /*0x0AC*/ f32 pitchSpeedScaler;
    /*0x0B0*/ f32 pitchZ_whenAirResistanceStarts;
    /*0x0B4*/ f32 airResistance_veloAdj;
    /*0x0B8*/ f32 moundZ; // 18.44
    /*0x0BC*/ f32 decelerationFactor;
    /*0x0C0*/ f32 verticalOffsetParabolaMidpoint;
    /*0x0C4*/ f32 verticalGlobalParabolicVelo;
    /*0x0C8*/ f32 pitchY_parabolicAdjustment;
    /*0x0CC*/ f32 horizontalOffsetParabolaMidpoint;
    /*0x0D0*/ f32 horizontalGlobalParabolicVelo;
    /*0x0D4*/ f32 pitchX_parabolicAdjustment;
    /*0x0D8*/ f32 pitchXPosition;  // unsure
    /*0x0DC*/ f32 pitchXPosition2; // unsure
    /*0x0E0*/ f32 pitchChargeUp;
    /*0x0E4*/ f32 pitchChargeUpAnimationProportion; // unsure
    /*0x0E8*/ VecXYZ starPitchPositionAdjustment;
    /*0x0F4*/ VecXYZ _F4;
    /*0x100*/ f32 bulletPitchLoopAngleRadians;
    /*0x104*/ f32 _104;
    /*0x108*/ f32 eggBallBounceZLoc;
    /*0x10C*/ f32 _10C[3];
    /*0x118*/ s16 rosterID;
    /*0x11A*/ E(s16, CHAR_ID) charID;
    /*0x11C*/ s16 scoutFlagRelated;
    /*0x11E*/ s16 pitchTotalTimeCounter;
    /*0x120*/ s16 currentStateFrameCounter;
    /*0x122*/ s16 frameWhenUnhittable;
    /*0x124*/ s16 _122;
    /*0x126*/ s16 windupCountdownUntilBallReleased;
    /*0x128*/ s16 pitchWindUpCountDown;
    /*0x12A*/ s16 curvePitchWindupFrames;
    /*0x12C*/ s16 _12C;
    /*0x12E*/ s16 pickOffLoc; // 4noThrow/5Steal;
    /*0x130*/ s16 framesSinceAtBatEnded;
    /*0x132*/ s16 framesUntilBallReachesBatterZ;
    /*0x134*/ s16 framesUntilPitchGetsToBatter;
    /*0x136*/ s16 unknownFrameCounter;
    /*0x138*/ s16 framesSinceFirstEggBounce;
    /*0x13A*/ s16 ballBouncePeakZ;
    /*0x13C*/ s16 warioWaluStarHasPlayedSound;
    /*0x13E*/ E(u8, PITCHER_ACTION_STATE) pitcherActionState;
    /*0x13F*/ u8 AIInd; // unsure
    /*0x140*/ u8 aiLevel;
    /*0x141*/ u8 handedness;
    /*0x142*/ u8 curveBallSpeed;
    /*0x143*/ u8 fastBallSpeed;
    /*0x144*/ u8 cursedBallStat;
    /*0x145*/ u8 curveControlStat;
    /*0x146*/ u8 curveStat;
    /*0x147*/ u8 captainStarPitch;
    /*0x148*/ u8 nonCaptainStarPitch;
    /*0x149*/ E(u8, CHARACTER_CLASS) charClass;
    /*0x14A*/ u8 pitchSpeed;
    /*0x14B*/ u8 calced_cursedBall;
    /*0x14C*/ u8 calced_curveControl;
    /*0x14D*/ u8 calced_curve;
    /*0x14E*/ u8 strikeOutOrWalk;
    /*0x14F*/ u8 strikeZoneProcessNumber;
    /*0x150*/ u8 specialPitchTypeCode;
    /*0x151*/ u8 frameBallCanStartBeingControlled; // unsure
    /*0x152*/ u8 pitchInAirInd;
    /*0x153*/ u8 cancelParabolicAdjustmentInd;
    /*0x154*/ u8 pitchDidntResultInLiveBallInd;
    /*0x155*/ u8 framesUntilUnhittable;
    /*0x156*/ u8 calledStrikeInd;
    /*0x157*/ u8 strikeInd;
    /*0x158*/ u8 miniGameRelated;
    /*0x159*/ u8 nPitchesThisAB;
    /*0x15A*/ u8 nPickoffAttempts;
    /*0x15B*/ u8 _15B;
    /*0x15C*/ u8 _15C;
    /*0x15D*/ u8 _15D;
    /*0x15E*/ u8 pitchDeliveryAnimationPlaying;
    /*0x15F*/ u8 ChargePitchType;
    /*0x160*/ u8 framesAHeldForChargePitches;
    /*0x161*/ u8 TypeOfPitch;
    /*0x162*/ u8 ballHaloTrainInd_unused;
    /*0x163*/ u8 overChargeInd;
    /*0x164*/ u8 starPitchInd;
    /*0x165*/ u8 starPitchType;
    /*0x166*/ u8 warioWaluStarAnimationStage;
    /*0x167*/ u8 warioWaluStarPitchRightLeft;
    /*0x168*/ u8 peachDaisyStarAnimationOn;
    /*0x169*/ u8 peachDaisyAnimationHappened;
    /*0x16A*/ u8 anyCurveInput;
    /*0x16B*/ u8 bulletPitchStageCode;
    /*0x16C*/ u8 bulletPitchFrameCounter;
    /*0x16D*/ u8 bulletPitchLoopFrames;
    /*0x16E*/ u8 bulletPitchLoopStartingFrame;
    /*0x16F*/ u8 _16F;
    /*0x170*/ u8 _170;
    /*0x171*/ u8 eggBallBounceNumber;
    /*0x172*/ u8 pitcherOffCenter;
    /*0x173*/ u8 playStartOfGameAnimation; // unsure
    /*0x174*/ u8 nonCaptainStarPitchTriggeredType;
    /*0x175*/ u8 walkedInRunInd;
    /*0x176*/ u8 unused_pitcherIsFielder; // unsure
} InMemPitcherType;                       // size: 0x178

// One g_Fielders entry (9 of them, stride 0x268). Merged from the per-unit views.
typedef struct _InMemFielderType {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ f32 height;
    /*0x010*/ f32 _010;
    /*0x014*/ VecXYZ dest; // destination
    /*0x020*/ u8 _020[0x30 - 0x20];
    /*0x030*/ f32 velX;
    /*0x034*/ f32 velZ;
    /*0x038*/ f32 _038; // previous velocity x?
    /*0x03C*/ f32 _03C; // previous velocity z?
    /*0x040*/ u8 _040[0x48 - 0x40];
    /*0x048*/ f32 facing; // rotation about y
    /*0x04C*/ u8 _04C[0x50 - 0x4C];
    /*0x050*/ f32 speed;
    /*0x054*/ u8 _054[0x58 - 0x54];
    /*0x058*/ f32 maxSpeed;
    /*0x05C*/ f32 velocityPerWeight; // maxSpeed / _1D1
    /*0x060*/ u8 _060[0x68 - 0x60];
    /*0x068*/ f32 distToDest;
    /*0x06C*/ u8 _06C[0x70 - 0x6C];
    /*0x070*/ f32 _070;
    /*0x074*/ f32 _074;
    /*0x078*/ u8 _078[0x07C - 0x078];
    /*0x07C*/ f32 _07C;
    /*0x080*/ u8 _080[0x084 - 0x080];
    /*0x084*/ f32 distToFielder[9];
    /*0x0A8*/ f32 distToBase[4];
    /*0x0B8*/ f32 _0B8;
    /*0x0BC*/ u8 _0BC[0x0D4 - 0x0BC];
    /*0x0D4*/ f32 _0D4;
    /*0x0D8*/ f32 _0D8;
    /*0x0DC*/ u8 _0DC[0x0E8 - 0x0DC];
    /*0x0E8*/ f32 reach[9]; // per-character reach table scaled by the character size; [3] is the catch height
    /*0x10C*/ VecXYZ throwTarget;
    /*0x118*/ u8 _118[0x120 - 0x118];
    /*0x120*/ f32 _120;
    /*0x124*/ f32 _124;
    /*0x128*/ u8 _128[0x15C - 0x128];
    /*0x15C*/ f32 _15C;
    /*0x160*/ u8 _160[0x16C - 0x160];
    /*0x16C*/ f32 _16C;
    /*0x170*/ u8 _170[0x174 - 0x170];
    /*0x174*/ f32 _174;
    /*0x178*/ s16 rosterID;
    /*0x17A*/ s16 charID; // also the action id (lbl_3_data_7E34 index)
    /*0x17C*/ s16 starMissionCharID;
    /*0x17E*/ s16 framesToDest;
    /*0x180*/ u8 _180[0x18C - 0x180];
    /*0x18C*/ s16 coveringBase;
    /*0x18E*/ u8 _18E[0x192 - 0x18E];
    /*0x192*/ s16 _192;
    /*0x194*/ s16 throwTimer;
    /*0x196*/ s16 _196;
    /*0x198*/ u8 _198[0x1A0 - 0x198];
    /*0x1A0*/ s16 _1A0;
    /*0x1A2*/ u8 _1A2[0x1A4 - 0x1A2];
    /*0x1A4*/ s16 _1A4;
    /*0x1A6*/ u8 _1A6[0x1AA - 0x1A6];
    /*0x1AA*/ s16 _1AA;
    /*0x1AC*/ s16 _1AC;
    /*0x1AE*/ u8 _1AE[0x1B4 - 0x1AE];
    /*0x1B4*/ s16 _1B4;
    /*0x1B6*/ u8 _1B6[0x1B8 - 0x1B6];
    /*0x1B8*/ s16 _1B8;
    /*0x1BA*/ u8 _1BA[0x1BE - 0x1BA];
    /*0x1BE*/ s16 _1BE;
    /*0x1C0*/ s16 _1C0;
    /*0x1C2*/ s16 _1C2; // angle
    /*0x1C4*/ u8 aiLevel;
    /*0x1C5*/ u8 _1C5;
    /*0x1C6*/ u8 _1C6;
    /*0x1C7*/ u8 handedness;
    /*0x1C8*/ u8 characterClass;
    /*0x1C9*/ u8 weight;
    /*0x1CA*/ u8 catchType;     // 5 with magical catch, else the weight
    /*0x1CB*/ u8 wallAbility;   // 1 wall splat, 2 wall jump, 3 clamber
    /*0x1CC*/ u8 superJump;
    /*0x1CD*/ u8 throwStrength; // from the throwing-arm stat
    /*0x1CE*/ u8 throwingArm;
    /*0x1CF*/ u8 _1CF;
    /*0x1D0*/ u8 speedStat;
    /*0x1D1*/ u8 _1D1;
    /*0x1D2*/ u8 _1D2;
    /*0x1D3*/ u8 _1D3[0x1D7 - 0x1D3]; // [0]: lbl_3_data_3C40 state index (fn_3_5985C)
    /*0x1D7*/ u8 _1D7;
    /*0x1D8*/ u8 _1D8[0x1DF - 0x1D8];
    /*0x1DF*/ u8 throwing;
    /*0x1E0*/ u8 _1E0;
    /*0x1E1*/ u8 _1E1;
    /*0x1E2*/ u8 _1E2;
    /*0x1E3*/ u8 _1E3;
    /*0x1E4*/ u8 _1E4;
    /*0x1E5*/ u8 _1E5;
    /*0x1E6*/ u8 _1E6;
    /*0x1E7*/ u8 _1E7;
    /*0x1E8*/ u8 _1E8[0x1EC - 0x1E8];
    /*0x1EC*/ u8 _1EC;
    /*0x1ED*/ u8 _1ED;
    /*0x1EE*/ u8 _1EE;
    /*0x1EF*/ u8 _1EF;
    /*0x1F0*/ u8 _1F0[0x1F5 - 0x1F0];
    /*0x1F5*/ s8 _1F5; // base
    /*0x1F6*/ u8 _1F6;
    /*0x1F7*/ s8 _1F7;
    /*0x1F8*/ u8 _1F8;
    /*0x1F9*/ u8 _1F9[0x1FC - 0x1F9];
    /*0x1FC*/ u8 _1FC; // nonzero: keep the model facing as is (fn_3_6AF9C)
    /*0x1FD*/ u8 _1FD;
    /*0x1FE*/ u8 _1FE;
    /*0x1FF*/ u8 _1FF;
    /*0x200*/ u8 _200;
    /*0x201*/ u8 _201[0x203 - 0x201];
    /*0x203*/ u8 _203;
    /*0x204*/ u8 _204;
    /*0x205*/ u8 _205;
    /*0x206*/ u8 _206[0x20A - 0x206];
    /*0x20A*/ u8 _20A; // nonzero: model keeps its animation rotation (fn_3_6B144)
    /*0x20B*/ u8 _20B[0x20D - 0x20B];
    /*0x20D*/ u8 minigamePlayer; // roster slot in minigames
    /*0x20E*/ u8 _20E;
    /*0x20F*/ u8 _20F;
    /*0x210*/ u8 knockback;
    /*0x211*/ u8 _211;
    /*0x212*/ u8 _212; // state
    /*0x213*/ u8 _213; // runner index
    /*0x214*/ u8 _214; // lbl_3_data_4860 index
    /*0x215*/ u8 _215;
    /*0x216*/ u8 _216[0x218 - 0x216];
    /*0x218*/ u8 opponentIdx; // 0 for the captain, else 1..n
    /*0x219*/ u8 _219[0x248 - 0x219];
    /*0x248*/ f32 _248;
    /*0x24C*/ s16 _24C;
    /*0x24E*/ u8 _24E[0x25A - 0x24E];
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B[0x25E - 0x25B];
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F[0x262 - 0x25F];
    /*0x262*/ u8 _262;
    /*0x263*/ u8 _263;
    /*0x264*/ u8 _264[0x268 - 0x264];
} InMemFielderType; // size: 0x268

// g_UnkAnimation_31EAC entry: per-fielder animation state (stride 0x54).
typedef struct FielderAnimState {
    /*0x00*/ f32 _00;
    /*0x04*/ u8 _04[0x10 - 0x4];
    /*0x10*/ f32 _10;
    /*0x14*/ f32 _14;
    /*0x18*/ f32 _18;
    /*0x1C*/ f32 _1C;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 _24;
    /*0x28*/ f32 rotY;
    /*0x2C*/ Vec _2C; // joint position (getAnimRelatedCoordinates)
    /*0x38*/ s16 _38;
    /*0x3A*/ s16 _3A;
    /*0x3C*/ s16 _3C;
    /*0x3E*/ s16 _3E;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 _43;
    /*0x44*/ u8 _44;
    /*0x45*/ u8 _45;
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 _48;
    /*0x49*/ u8 _49;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 _50;
    /*0x51*/ u8 _51;
    /*0x52*/ u8 _52[0x54 - 0x52];
} FielderAnimState; // size: 0x54

// lbl_3_common_bss_321A0 entry: per-runner animation state (stride 0x20, 4 entries).
typedef struct RunnerAnimState {
    /*0x00*/ f32 _00;
    /*0x04*/ u8 _04[0x10 - 0x4];
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x16 - 0x12];
    /*0x16*/ s16 _16;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 _1D;
    /*0x1E*/ u8 _1E[0x20 - 0x1E];
} RunnerAnimState; // size: 0x20

// g_UnkThrowing_31ACC (0x14 bytes).
typedef struct ThrowState {
    /*0x00*/ f32 _00;
    /*0x04*/ f32 _04;
    /*0x08*/ f32 _08;
    /*0x0C*/ s16 _0C;
    /*0x0E*/ u8 _0E;
    /*0x0F*/ u8 _0F;
    /*0x10*/ u8 _10[0x14 - 0x10];
} ThrowState; // size: 0x14

// lbl_3_common_bss_32220 (batter idle/celebration animation state).
typedef struct GameBss32220 {
    /*0x0*/ s16 _00; // idle frames
    /*0x2*/ s16 _02;
    /*0x4*/ s16 _04;
    /*0x6*/ s16 _06;
    /*0x8*/ u8 _08;
    /*0x9*/ u8 _09;
    /*0xA*/ u8 state;
    /*0xB*/ u8 _0B;
    /*0xC*/ s8 _0C;
    /*0xD*/ u8 _0D;
    /*0xE*/ u8 _0E[0x10 - 0xE];
} GameBss32220; // size: 0x10

// lbl_3_common_bss_32230 (pitcher animation state).
typedef struct GameBss32230 {
    /*0x0*/ s16 _00;
    /*0x2*/ u8 _02;
    /*0x3*/ u8 _03;
} GameBss32230; // size: 0x4

// lbl_3_common_bss_32234 (end-of-minigame reactions).
typedef struct GameBss32234 {
    /*0x0*/ u8 _00;
    /*0x1*/ u8 _01;
    /*0x2*/ u8 result[4]; // per player: reaction (0, 1, 2)
    /*0x6*/ u8 _06[2];
} GameBss32234; // size: 0x8 (the replay snapshot copies the first 6 bytes)

extern InMemPitcherType g_Pitcher;
extern InMemBallType g_Ball;
extern InMemRunnerType g_Runners[4];
extern InMemBatterType g_Batter;

extern VecXYZ maybeInitialBatPos;
extern f32 charSizeMultipliers[NUM_CHOOSABLE_CHARACTERS][2];

#define FRAME_COUNT_HIT_WINDOW 15

// 0 is slap, 1 is charge
extern s16 hittableFrameInd[2][FRAME_COUNT_HIT_WINDOW];
/*
= {
    { // slap
        false, false, true, true, // frames 0-3
        true, true, true, true,   // frames 4-7
        true, true, true, false,  // frames 8-11
        false, false, false,      // frames 12-14
    },
    { // charge/star
        false, false, false, true, // frames 0-3
        true, true, true, true,    // frames 4-7
        true, true, false, false,  // frames 8-11
        false, false, false,       // frames 12-14
    },
};
*/

// indexed by trimmed bat
typedef struct _BatNearFarReach {
    f32 near, far;
} BatNearFarReach;

extern BatNearFarReach batContactRange[2];
/*
= {
    // full-length bat
    { -0.85f, 0.15f },
    // trimmed bat
    { -0.35f, 0.35f },
}
*/

typedef struct _HitFloats {
    /*0x00*/ f32 minStarHitVelo;
    /*0x04*/ f32 DKStarAngleDelta;
    /*0x08*/ f32 DKStarHangtimePercentStart;
    /*0x0C*/ f32 DKStarHangtimePercentEnd;
    /*0x10*/ f32 eggVeloMaintainedOnBounce;
    /*0x14*/ f32 bulletStarEnergyMultiplier;
    /*0x18*/ f32 garlicSpreadLower;
    /*0x1C*/ f32 garlicSpreadUpper;
    /*0x20*/ f32 overChargeLerpBtwnSlapAndChargePower;
    /*0x24*/ f32 regularBoxSpeedMult;
    /*0x28*/ f32 centeringBoxSpeedMult;
    /*0x2C*/ f32 moonshotMult;
} HitFloats;

extern HitFloats g_hitFloats;
/*
 = {
    0.05f,  // minStarHitVelo
    0.008f, // DKStarAngleDelta
    0.25f,  // DKStarHangtimePercentStart
    0.95f,  // DKStarHangtimePercentEnd
    0.8f,   // eggVeloMaintainedOnBounce
    4.f,    // bulletStarEnergyMultiplier
    0.2f,   // garlicSpreadLower
    0.3f,   // garlicSpreadUpper
    0.5f,   // overChargeLerpBtwnSlapAndChargePower
    1.f,    // regularBoxSpeedMult
    3.f,    // centeringBoxSpeedMult
    1.5f    // moonshotMult
};
*/

typedef struct _HitShorts {
    /*0x00*/ s16 frameChargeDownEnds;
    /*0x02*/ s16 framesUntilChargeIsEnabled;
    /*0x04*/ s16 _04;
    /*0x06*/ s16 framesOnGroundBeforeCheckingMinStarVelo;
    /*0x08*/ s16 fireballStunFrames;
    /*0x0A*/ s16 unused_alternateFireballStunFrames;
    /*0x0C*/ s16 NEggBounces;
    /*0x0E*/ s16 _0C;
    /*0x10*/ s16 framesBeforeGroundWhenGarlicSplits;
    /*0x12*/ s16 FrameWhenPeachHitAppearsAgain;
    /*0x14*/ s16 FrameWhenDaisyHitAppearsAgain; // unsure
    /*0x16*/ s16 _16;
    /*0x18*/ s16 _18;
    /*0x1A*/ s16 regularHitGamePause;
    /*0x1C*/ s16 captainStarHitGamePause;
    /*0x1E*/ s16 moonshotGamePause;
} HitShorts;

extern HitShorts g_hitShorts;
/*
= {
    180, // frameChargeDownEnds
    12,  // framesUntilChargeIsEnabled
    6,   // _04
    3,   // framesOnGroundBeforeCheckingMinStarVelo
    90,  // fireballStunFrames
    60,  // unused_alternateFireballStunFrames
    2,   // NEggBounces
    30,  // _0C
    120, // framesBeforeGroundWhenGarlicSplits
    1,   // FrameWhenPeachHitAppearsAgain
    1,   // FrameWhenDaisyHitAppearsAgain
    160, // _16
    160, // _18
    1,   // regularHitGamePause
    50,  // captainStarHitGamePause
    50   // moonshotGamePause
};
*/

typedef struct _GameControlOptions {
    /*0x000*/ bool autoRunning;
    /*0x001*/ bool autoFielding;
    /*0x002*/ bool dropSpot;
    /*0x003*/ bool _3;
    /*0x004*/ bool easyBatting;
    /*0x005*/ bool _5;
    /*0x006*/ bool _6;
} GameControlOptions; // size: 0x7

typedef struct _GameInitOptions {
    /*0x000*/ u8 inningSetting;
    /*0x001*/ u8 _1;
    /*0x002*/ u8 _2;
    /*0x003*/ u8 _3;
    /*0x004*/ u8 starSkillsSetting;
    /*0x005*/ u8 runsNeededForMercy;
    /*0x006*/ u8 _6;
    /*0x007*/ u8 _7;
    /*0x008*/ u8 _8;
    /*0x009*/ GameControlOptions controlOptions[4];
    /*0x025*/ u8 _25;
    /*0x026*/ u8 _26;
    /*0x027*/ u8 _27;
    /*0x028*/ u8 _28;
    /*0x029*/ u8 _29;
    /*0x02A*/ s16 _2A;
    /*0x02C*/ s16 _2C;
    /*0x02E*/ s16 _2E;
    /*0x030*/ s16 _30;
    /*0x032*/ u8 _32;
    /*0x033*/ u8 _33;
    /*0x034*/ u8 _34;
    /*0x035*/ u8 _35;
    /*0x036*/ u8 _36;
    /*0x037*/ u8 _37;
    /*0x038*/ u8 _38;
    /*0x039*/ u8 _39;
    /*0x03A*/ u8 _3A;
    /*0x03B*/ u8 _3B;
    /*0x03C*/ u8 _3C;
    /*0x03D*/ u8 _3D;
    /*0x03E*/ u8 _3E;
    /*0x03F*/ u8 _3F;
    /*0x040*/ u8 _40;
    /*0x041*/ u8 _41;
    /*0x042*/ u8 _42;
    /*0x043*/ u8 _43;
    /*0x044*/ u8 _44;
    /*0x045*/ u8 _45;
    /*0x046*/ u8 _46;
    /*0x047*/ u8 _47;
    /*0x048*/ u8 _48;
    /*0x049*/ u8 _49;
    /*0x04A*/ u8 _4A;
    /*0x04B*/ u8 _4B;
    /*0x04C*/ u8 _4C;
    /*0x04D*/ u8 _4D;
    /*0x04E*/ u8 _4E;
    /*0x04F*/ u8 _4F;
    /*0x050*/ u8 _50;
    /*0x051*/ u8 _51;
    /*0x052*/ u8 _52;
    /*0x053*/ u8 _53;
    /*0x054*/ u8 _54;
    /*0x055*/ u8 _55;
    /*0x056*/ u8 _56;
    /*0x057*/ u8 _57;
    /*0x058*/ u8 _58;
    /*0x059*/ u8 _59;
    /*0x05A*/ u8 _5A;
    /*0x05B*/ u8 _5B;
    /*0x05C*/ u8 _5C;
    /*0x05D*/ u8 _5D;
    /*0x05E*/ u8 _5E;
    /*0x05F*/ u8 _5F;
} GameInitOptions; // size: 0x60

extern GameInitOptions gameInitOptions;

typedef enum {
    INPUT_BUTTON_LEFT = PAD_BUTTON_LEFT,
    INPUT_BUTTON_RIGHT = PAD_BUTTON_RIGHT,
    INPUT_BUTTON_DOWN = PAD_BUTTON_DOWN,
    INPUT_BUTTON_UP = PAD_BUTTON_UP,
    INPUT_TRIGGER_Z = PAD_TRIGGER_Z,
    INPUT_TRIGGER_R = PAD_TRIGGER_R,
    INPUT_TRIGGER_L = PAD_TRIGGER_L,
    INPUT_BUTTON_A = PAD_BUTTON_A,
    INPUT_BUTTON_B = PAD_BUTTON_B,
    INPUT_BUTTON_X = PAD_BUTTON_X,
    INPUT_BUTTON_Y = PAD_BUTTON_Y,
    INPUT_BUTTON_MENU = PAD_BUTTON_MENU,
    INPUT_BUTTON_START = PAD_BUTTON_START,
} INPUT_BUTTON;

typedef struct _InputStruct {
    /*0x00*/ sAng controlStickAngle;
    /*0x02*/ s16 controlStickMagnitude;
    /*0x04*/ E(u16, INPUT_BUTTON) buttonInput;
    /*0x06*/ E(u16, INPUT_BUTTON) newButtonInput; // pressed this frame
    /*0x08*/ u16 _08; // held direction mask (read as u16)
    /*0x0A*/ s8 right_left;
    /*0x0B*/ s8 up_down;
    /*0x0C*/ u8 rightTriggerDistance; // analog 0..255
    /*0x0D*/ u8 leftTriggerDistance;
    /*0x0E*/ u8 _0E; // cleared each frame (fn_3_6D304)
    /*0x0F*/ u8 _0F;
} InputStruct;        // size: 0x10

typedef enum _PRACTICE_TYPE {
    PRACTICE_TYPE_PITCHING,
    PRACTICE_TYPE_BATTING,
    PRACTICE_TYPE_FIELDING,
    PRACTICE_TYPE_BASERUNNING,
    PRACTICE_TYPE_FREEPLAY
} PRACTICE_TYPE;

typedef enum _PRACTICE_STATE {
    PRACTICE_STATE_0,
    PRACTICE_STATE_1,
    PRACTICE_STATE_2,
    PRACTICE_STATE_3,
    PRACTICE_STATE_4,
    PRACTICE_STATE_5,
    PRACTICE_STATE_6,
    PRACTICE_STATE_7,
    PRACTICE_STATE_8
    /*
        0_switchToTopMenu4/switchToSubMenu+loadfield,goTo1/newAB?=0,
        1_/checkSomething,delay,goTo2=1,
        2_changeScene,goTo3/subMenuControl=2,
        3_delay30Frames,goTo4/switchToField,goTo4=3,
        4_mainMenuControl/loadPracticeOnField=4,
        5_checkSomething,goTo6/returnToTopMenu,goTo6=5,
        6_setPracticeConsts,goTo0/returnToTopMenu2,goTo7=6,
        7_exitToMenuQuestion/returnToTopMenu3,goTo0=7,
        8_exitToMainMenu=8
    */
} PRACTICE_STATE;

typedef enum _TUTORIAL_STATE {
    TUTORIAL_STATE_0,
    TUTORIAL_STATE_1,
    TUTORIAL_STATE_2,
    TUTORIAL_STATE_3,
    /*
        menu/na=0,
        givingInstruction=1,
        transitionToPlayerControl=2,
        playerHasControl=3
    */
} TUTORIAL_STATE;

typedef struct _PracticeStruct {
    /*0x000*/ InputStruct inputs[2];
    /*0x020*/ s16* commandList; // tutorial command script
    /*0x024*/ int homeAway;
    artificial_padding(0x24, 0x140, int);
    /*0x140*/ u16 totalFrames;
    /*0x142*/ u16 framesInCurrTransitionState;
    /*0x144*/ u16 framesSincePracticeMenuDefaultTransition;
    /*0x146*/ frame_t practiceMenu_framesOnCurrMenuScreen;
    /*0x148*/ u16 frames_sinceMovedToFromMenu;
    /*0x14A*/ frame_t _14A;
    /*0x14C*/ frame_t frames_sinceTimeCalled;
    /*0x14E*/ frame_t frames_onPauseScreen;
    /*0x150*/ frame_t frames_onPauseScreen2; // used For Allowing Cursor To Move
    /*0x152*/ frame_t _152;                  // count To 60 then Set Hit Vars For Fielding Practice
    /*0x154*/ frame_t _154;
    /*0x156*/ frame_t _156;
    /*0x158*/ frame_t _158;
    /*0x15A*/ frame_t someCharID1;
    /*0x15C*/ frame_t someCharID2;
    /*0x15E*/ frame_t someCharID3;
    /*0x160*/ frame_t someCharID4;
    /*0x162*/ frame_t framesOnAllInstructions; // unsure
    /*0x164*/ frame_t _164;
    /*0x166*/ frame_t framesOnCurrInstruction;
    /*0x168*/ frame_t laukituTextChannelIndex;
    /*0x16A*/ frame_t lakituTextIndex;
    /*0x16C*/ frame_t lakituTextIndex_stored;
    /*0x16E*/ frame_t diagramTextChannelIndex;
    /*0x170*/ frame_t diagramTitleTextIndex;
    /*0x172*/ frame_t diagramTitleTextIndex_stored;
    /*0x174*/ frame_t cpuCommandDuration;
    /*0x176*/ frame_t maybeInputResetCountdown;
    /*0x178*/ u16 maybePreviousInput[2]; // per input: held buttons of the scripted CPU input
    /*0x17C*/ frame_t cpu_inputDuration[2];  // per input: frames left to hold maybePreviousInput
    /*0x180*/ frame_t practice_hitHorizontalPower;
    /*0x182*/ frame_t practice_hitVerticalAngle;
    /*0x184*/ frame_t practice_hitHorizontalAngle;
    /*0x186*/ frame_t _186;
    /*0x188*/ frame_t _188;
    /*0x18A*/ s16 maybeCommandData[4]; // unsure
    /*0x192*/ u8 _192;
    /*0x193*/ E(u8, PRACTICE_TYPE) practiceType_2;
    /*0x194*/ u8 practiceLevel;
    /*0x195*/ E(u8, PRACTICE_STATE) practiceState;
    /*0x196*/ E(u8, TUTORIAL_STATE) tutorialState;
    /*0x197*/ u8 _197;
    /*0x198*/ E(u8, PRACTICE_TYPE) practiceType_1;
    /*0x199*/ E(u8, PRACTICE_TYPE) practiceType;
    /*0x19A*/ u8 subMenuCursor;
    /*0x19B*/ u8 _19B;
    /*0x19C*/ u8 _19C;
    /*0x19D*/ u8 _19D;
    /*0x19E*/ u8 pauseMenuLoading; // unsure
    /*0x19F*/ u8 _19F;
    /*0x1A0*/ u8 _1A0;
    /*0x1A1*/ u8 aIEnabled;
    /*0x1A2*/ u8 practiceBatterHandedness; // unsure
    /*0x1A3*/ u8 freePracticeInd_writeOnly;
    /*0x1A4*/ u8 _1A4;
    /*0x1A5*/ u8 _1A5;
    /*0x1A6*/ u8 _1A6;
    /*0x1A7*/ u8 _1A7;
    /*0x1A8*/ u8 _1A8;
    /*0x1A9*/ u8 _1A9;
    /*0x1AA*/ u8 transitioningIndicator; // unsure
    /*0x1AB*/ u8 startRunners[4]; // per base slot (0 = batter): occupied at practice start
    /*0x1AF*/ u8 returnToPracticeMenuState;
    /*0x1B0*/ u8 _1B0;
    /*0x1B1*/ u8 _1B1;
    /*0x1B2*/ u8 levelCleared[4][4]; // [practiceType][level], copied from the save
    /*0x1C2*/ s8 instructionNumber;
    /*0x1C3*/ u8 readyToMoveToNextInstruction; // unsure
    /*0x1C4*/ u8 practice_runner_countInputForMashing;
    /*0x1C5*/ u8 practice_fielding_enableSprinting;
    /*0x1C6*/ u8 _1C6;
    /*0x1C7*/ u8 _1C7;
    /*0x1C8*/ u8 guidedPracticeCompletionRelated;
    /*0x1C9*/ u8 guidedPracticeCompletionRelated2;
    /*0x1CA*/ u8 guidedPracticeCounter;
    /*0x1CB*/ u8 _1CB;
    /*0x1CC*/ u8 currentMessageDoneTyping;
    /*0x1CD*/ u8 commandIndex;
    /*0x1CE*/ u8 allInstructionsComplete;
    /*0x1CF*/ u8 instructionComplete_readyToAdvance;
    /*0x1D0*/ u8 allowPlayToEndIndicator;
    /*0x1D1*/ u8 maybeControlFlag1;
    /*0x1D2*/ u8 textRelatedIndicator;
    /*0x1D3*/ u8 maybeControlFlag2;
    /*0x1D4*/ u8 loadingGuidedPractice; // unsure
    /*0x1D5*/ u8 _1D5;
    /*0x1D6*/ u8 practiceLevel_2;
    /*0x1D7*/ u8 _1D7;
    /*0x1D8*/ u8 _1D8;
    /*0x1D9*/ u8 _1D9;
    /*0x1DA*/ u8 _1DA;
    /*0x1DB*/ u8 _1DB;
    /*0x1DC*/ u8 _1DC;
    /*0x1DD*/ u8 _1DD;
    /*0x1DE*/ u8 _1DE;
    /*0x1DF*/ u8 _1DF;
    /*0x1E0*/ u8 _1E0;
    /*0x1E1*/ u8 hitVariablesSetIndicator;
    /*0x1E2*/ u8 _1E2;
    /*0x1E3*/ u8 aiBuntIndicator; // unsure
    /*0x1E4*/ u8 _1E4;
    /*0x1E5*/ u8 _1E5;
    /*0x1E6*/ u8 _1E6;
    /*0x1E7*/ u8 _1E7;
    /*0x1E8*/ u8 _1E8;
    /*0x1E9*/ u8 _1E9;
    /*0x1EA*/ u8 _1EA;
    /*0x1EB*/ u8 _1EB;
    /*0x1EC*/ u8 _1EC;
    /*0x1ED*/ u8 _1ED;
    /*0x1EE*/ u8 _1EE;
    /*0x1EF*/ u8 rosterID; // unsure
} PracticeStruct;          // size: 0x1f0

extern PracticeStruct g_Practice;

#define ACTIVE_TUTORIAL() (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0)

extern u8 buntPower[5][2];

extern VecXYZ s_ballCurveData[2];
/*
 =
{
    {
        0.5f, 0.001f, 0.003f
    },
    {
        0.25f, 0.006f, 0.008f
    }
}
*/

extern const f32 contactQual; // = 100.f;

#define ANG4K_DEG(v) (s16)((v) * (360.f / 4096.f))
#define ANG4K_RAD(v) (s16)((v) * ((2.f * PI) / 4096.f))

typedef enum _FIELDING_ABILITY {
    FIELDING_ABILITY_WALL_SPLAT,
    FIELDING_ABILITY_WALL_JUMP,
    FIELDING_ABILITY_WALL_CLAMBER,
    FIELDING_ABILITY_SLIDING_CATCH,
    FIELDING_ABILITY_LASER,
    FIELDING_ABILITY_QUICK_THROW,
    FIELDING_ABILITY_SUPER_JUMP,
    FIELDING_ABILITY_MAGICAL_CATCH,
    FIELDING_ABILITY_TONGUE_CATCH,
    FIELDING_ABILITY_SUCTION,
    FIELDING_ABILITY_SUPER_CATCH,
    FIELDING_ABILITY_BALL_DASH,
    FIELDING_ABILITY_BODY_CHECK,
    FIELDING_ABILITY_SUPER_CURVE,
} FIELDING_ABILITY;

typedef enum _GAME_STATUS {
    /* 0x00 */ GAME_STATUS_DEFAULT,
    /* 0x01 */ GAME_STATUS_AT_BAT,
    /* 0x02 */ GAME_STATUS_LIVE_BALL,
    /* 0x03 */ GAME_STATUS_INNING_TRANSITION,
    /* 0x04 */ GAME_STATUS_LOAD_GAME,
    /* 0x05 */ GAME_STATUS_GAME_START_MOVIE,
    /* 0x06 */ GAME_STATUS_TRANSITION_TO_MINIGAME_START,
    /* 0x07 */ GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY,
    /* 0x08 */ GAME_STATUS_TRANSITION,
    /* 0x09 */ GAME_STATUS_END_OF_GAME, // unsure
    /* 0x0A */ GAME_STATUS_0xA,
    /* 0x0B */ GAME_STATUS_PAUSED,
    /* 0x0C */ GAME_STATUS_0xC,
    /* 0x0D */ GAME_STATUS_HOW_TO_PLAY_SCREEN,
    /* 0x0E */ GAME_STATUS_MVP_END_GAME,
    /* 0x0F */ GAME_STATUS_TRANSITION_MINIGAME_POSTGAME,
    /* 0x10 */ GAME_STATUS_0x10,
    /* 0x11 */ GAME_STATUS_0x11,
    /* 0x12 */ GAME_STATUS_0x12,
    /* 0x13 */ GAME_STATUS_HOMERUN_END,
    /* 0x14 */ GAME_STATUS_HOMERUN_LAP,
    /* 0x15 */ GAME_STATUS_BATTER_CELEBRATION, // post replay
    /* 0x16 */ GAME_STATUS_STAR_CHANCE_VS,
    /* 0x17 */ GAME_STATUS_CHAMPIONSHIP,
    /* 0x18 */ GAME_STATUS_0x18,
    /* 0x19 */ GAME_STATUS_MINIGAME_NEW_ROUND,             // unsure
    /* 0x1A */ GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING, // unsure
    /* 0x1B */ GAME_STATUS_0x1B,
    /* 0x1C */ GAME_STATUS_MINIGAME_SELECT,
    /* 0x1D */ GAME_STATUS_TOY_STADIUM_LOAD,
    /* 0x1E */ GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT,
    /* 0x1F */ GAME_STATUS_0x1F,
    /* 0x20 */ GAME_STATUS_0x20,
    /* 0x21 */ GAME_STATUS_MINIGAME_READY,
    /* 0x22 */ GAME_STATUS_MINIGAME_POST_MENU,
    /* 0x23 */ GAME_STATUS_0x23,
    /* 0x24 */ GAME_STATUS_0x24,
    /* 0x25 */ GAME_STATUS_0x25,
    /* 0x26 */ GAME_STATUS_0x26,
    /* 0x27 */ GAME_STATUS_0x27,
} GAME_STATUS;

typedef enum _SCENE_ID {
    /* 0 */ SCENE_ID_0,
    /* 1 */ SCENE_ID_AT_BAT,
    /* 2 */ SCENE_ID_LIVE_BALL,
    /* 3 */ SCENE_ID_REPLAY_AT_BAT,
    /* 4 */ SCENE_ID_REPLAY_LIVE_BALL,
} SCENE_ID;

typedef enum _SECONDARY_GAME_MODE {
    /* 0x00 */ SECONDARY_GAME_MODE_NONE, // also exhibition
    /* 0x01 */ SECONDARY_GAME_MODE_TOY_FIELD,
    /* 0x02 */ SECONDARY_GAME_MODE_MINI_GAME_MENU,
    /* 0x03 */ SECONDARY_GAME_MODE_BOBOMB_DERBY,
    /* 0x04 */ SECONDARY_GAME_MODE_WALLBALL,
    /* 0x05 */ SECONDARY_GAME_MODE_BARREL_BATTER,
    /* 0x06 */ SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT,
    /* 0x07 */ SECONDARY_GAME_MODE_PIRANHA_PANIC,
    /* 0x08 */ SECONDARY_GAME_MODE_STAR_DASH,
    /* 0x09 */ SECONDARY_GAME_MODE_0x9,
    /* 0x0A */ SECONDARY_GAME_MODE_PRACTICE_MENU,
    /* 0x0B */ SECONDARY_GAME_MODE_PRACTICE_PITCHING,
    /* 0x0C */ SECONDARY_GAME_MODE_PRACTICE_BATTING,
    /* 0x0D */ SECONDARY_GAME_MODE_PRACTICE_FIELDING,
    /* 0x0E */ SECONDARY_GAME_MODE_PRACTICE_BASERUNNING,
    /* 0x0F */ SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING,
    /* 0x10 */ SECONDARY_GAME_MODE_FREE_FIELDING,
    /* 0x11 */ SECONDARY_GAME_MODE_RETURN_TO_MENU,
    /* 0x12 */ SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN,
} SECONDARY_GAME_MODE;

typedef enum _TRANSITION_CALCULATION_TYPE {
    TRANSITION_CALCULATION_TYPE_0,
    TRANSITION_CALCULATION_TYPE_1,
    TRANSITION_CALCULATION_TYPE_2,
    TRANSITION_CALCULATION_TYPE_3,
    TRANSITION_CALCULATION_TYPE_4,
    TRANSITION_CALCULATION_TYPE_5,
    TRANSITION_CALCULATION_TYPE_6,
    TRANSITION_CALCULATION_TYPE_7,
    TRANSITION_CALCULATION_TYPE_8,
    TRANSITION_CALCULATION_TYPE_9,
    TRANSITION_CALCULATION_TYPE_10,
    TRANSITION_CALCULATION_TYPE_11,
} TRANSITION_CALCULATION_TYPE;

typedef enum _WIN_TYPE {
    WIN_TYPE_0,
    WIN_TYPE_1,
    WIN_TYPE_2,
    WIN_TYPE_3,
    WIN_TYPE_4,
    WIN_TYPE_5,
    WIN_TYPE_6,
} WIN_TYPE;

typedef struct _LogoInfoStruct {
    int ID;
    int variationID;
    int captain;  // unsure
} LogoInfoStruct; // size: 0xC

typedef struct _GameControlsStruct {
    /*0x000*/ s32 _000; // a team index (0/1), compared with g_Scores.winningTeam
    /*0x004*/ int teamBatting;
    /*0x008*/ int teamFielding;
    /*0x00C*/ int homeTeamBattingInd_fieldingTeam;
    /*0x010*/ int awayTeamBattingInd_battingTeam;
    /*0x014*/ u32 AIDifficulty0Special3Weak[2];
    /*0x01C*/ s32 _01C[2]; // per team, from g_d_GameSettings.maybeHomeAway[]
    /*0x024*/ LogoInfoStruct logo[2];
    /*0x03C*/ int battingOrderAndPositionMapping[2][10][2]; // first Pair Is Pitcher
    /*0x0DC*/ int currentBatterPerTeam[2];
    /*0x0E4*/ u32 runnerAIInd[2];
    /*0x0EC*/ u32 teams[2]; // vague name, unsure
    /*0x0F4*/ s32 Team_CaptainRosterLoc[2];
    /*0x0FC*/ u16 FrameCountOfCurrentPitch;
    /*0x0FE*/ u16 FrameCountOfCurrentAtBat_Copy;
    /*0x100*/ s16 CountdownUntilFade;
    /*0x102*/ s16 _102;
    /*0x104*/ s16 framePlayEnd;
    /*0x106*/ s16 _106;
    /*0x108*/ s16 _108;
    /*0x10A*/ s16 bOD_framesInLiveBallScene;
    /*0x10C*/ s16 frameCountdownAtBeginningOfAtBatLockout;
    /*0x10E*/ u16 scoreBook_teamDisplayed;
    /*0x110*/ u16 scoreBook_batter_pitcherStatsDisplayed;
    /*0x112*/ u16 scoreBook_scrollIndex;
    /*0x114*/ s16 _114;
    /*0x116*/ s16 scoreBook_logoFadeDirectionLeft_Right;
    /*0x118*/ s16 _118;
    /*0x11A*/ s16 _11A;
    /*0x11C*/ s16 _11C;
    /*0x11E*/ E(u8, GAME_STATUS) gameStatus;
    /*0x11F*/ E(u8, GAME_STATUS) gameStatus_prev;
    /*0x120*/ E(u8, SCENE_ID) sceneID;
    /*0x121*/ E(u8, SECONDARY_GAME_MODE) secondaryGameMode;
    /*0x122*/ u8 framesOfExitingToMenu;
    /*0x123*/ u8 _123;
    /*0x124*/ u8 _124;
    /*0x125*/ E(u8, TRANSITION_CALCULATION_TYPE) _125;
    /*0x126*/ u8 homeRunWordAnimationCompletedInd;
    /*0x127*/ u8 EventTriggers_EndOfGame;
    /*0x128*/ u8 _128;
    /*0x129*/ u8 EventTriggers_GameHasStarted; // unsure
    /*0x12A*/ u8 playBatterWalkupAnimation;
    /*0x12B*/ u8 pre_PostMiniGameInd;        // unsure
    /*0x12C*/ u8 minigameLastTurnSuccessInd; // unsure
    /*0x12D*/ u8 hudElementLoadingInd;
    /*0x12E*/ u8 hudLoadingRelated; // unsure
    /*0x12F*/ u8 _12F;
    /*0x130*/ E(u8, WIN_TYPE) winType;
    /*0x131*/ u8 _131[2]; // per team
    /*0x133*/ u8 _133[2]; // per team
    /*0x135*/ u8 _135;
    /*0x136*/ u8 _136;
    /*0x137*/ s8 playOverFadeOutStarted; // also: scorebook team selection (-1: none)
    /*0x138*/ u8 playOver;
    /*0x139*/ u8 playOverInd;
    /*0x13A*/ u8 walkOffWinInd; // unsure
    /*0x13B*/ u8 gameOverInd;
    /*0x13C*/ u8 scoutFlag_VsScreenInd;
    /*0x13D*/ u8 _13D; // set when the MVP counts for the record (fn_3_759BC)
    /*0x13E*/ u8 _13E[2]; // per team: AI controlled (also selects the alternate logo frame)
    /*0x140*/ u8 _140[2];
    /*0x142*/ u8 teamAIInd[2];
    /*0x144*/ u8 autoFielding[2];
    /*0x146*/ u8 batterHandedness[2];
    /*0x148*/ u8 battingAIInd[2]; // unsure
    /*0x14A*/ u8 TeamStars[2];
    /*0x14C*/ u8 IsStarChance;
    /*0x14D*/ u8 stadiumStarObtained;
    /*0x14E*/ u8 PauseSimulationFrameCount;
    /*0x14F*/ u8 freeFieldingPracticeInd;
    /*0x150*/ frame_t frame_exitMenuShowing;
    /*0x152*/ frame_t frames_memoryCardWriteOnMVP; // unsure
    /*0x154*/ u8 endGameStage;
    /*0x155*/ u8 rosterLoc_skippingCap; // unsure
    /*0x156*/ u8 _156;
    /*0x157*/ u8 _157;
} GameControlsStruct; // size: 0x158

extern GameControlsStruct g_GameLogic;

typedef enum _CHALLENGE_CAPTAIN {
    CHALLENGE_CAPTAIN_MARIO,
    CHALLENGE_CAPTAIN_PEACH,
    CHALLENGE_CAPTAIN_WARIO,
    CHALLENGE_CAPTAIN_DK,
    CHALLENGE_CAPTAIN_YOSHI,
    CHALLENGE_CAPTAIN_BOWSER,
} CHALLENGE_CAPTAIN;

typedef enum _CHARACTER_VARIANT_CLASSIFICATION {
    CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_UNIQUE_NON_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT,
    CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_VARIANT,
} CHARACTER_VARIANT_CLASSIFICATION;

typedef enum _STAR_MISSION_TRACKING {
    STAR_MISSION_TRACKING_NOT_COMPLETED = 0,
    STAR_MISSION_TRACKING_TRACK1_COMPLETION = 1,
    STAR_MISSION_TRACKING_COMPLETED_SAVED = 254,
    STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY = 255,
} STAR_MISSION_TRACKING;

typedef enum _CHALLENGE_RECRUITMENT_CD {
    CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED,
    CHALLENGE_RECRUITMENT_CD_RECRUITED,
    CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM,
} CHALLENGE_RECRUITMENT_CD;

typedef enum _FIELDING_ABILITIES {
    FIELDING_ABILITIES_WALL_SPLAT = 0x1,
    FIELDING_ABILITIES_WALL_JUMP = 0x2,
    FIELDING_ABILITIES_CLAMBER = 0x4,
    FIELDING_ABILITIES_SLIDING_CATCH = 0x8,
    FIELDING_ABILITIES_LASER = 0x10,
    FIELDING_ABILITIES_QUICK_THROW = 0x20,
    FIELDING_ABILITIES_SUPER_JUMP = 0x40,
    FIELDING_ABILITIES_MAGICAL_CATCH = 0x80,
    FIELDING_ABILITIES_TONGUE_CATCH = 0x100,
    FIELDING_ABILITIES_SUCTION = 0x200,
    FIELDING_ABILITIES_SUPER_CATCH = 0x400,
    FIELDING_ABILITIES_BALL_DASH = 0x800,
    FIELDING_ABILITIES_BODY_CHECK = 0x1000,
    FIELDING_ABILITIES_SUPER_CURVE = 0x2000,
    FIELDING_ABILITIES_UNASSIGNED = 0x4000,
    FIELDING_ABILITIES_UNASSIGNED2 = 0x8000,
} FIELDING_ABILITIES;

typedef struct _starMissionTrackingPair {
    /*0x000*/ E(u8, STAR_MISSION_TRACKING) starMissionStatus;
    /*0x001*/ u8 shownOnPauseMenu;
} starMissionTrackingPair;

// This is pack disabled in ghidra.
typedef struct _ChallengeTrackingStruct {
    /*0x000*/ PTR32(void) scoutFlagPointer; // ScoutFlagTable; PTR32: saved (MenuCtx.chars[].limits)
    /*0x004*/ E(u8, CHALLENGE_CAPTAIN) challengeCaptain; // Created by retype action
    /*0x005*/ E(s8, CHARACTER_VARIANT_CLASSIFICATION) variantClassification;
    /*0x006*/ u8 scoutFlagsAchieved;
    /*0x007*/ u8 _7;
    /*0x008*/ u8 _8;
    /*0x009*/ starMissionTrackingPair inGameMissionTracker[10];
    /*0x01D*/ starMissionTrackingPair saveFileMissionTracker[10];
    /*0x031*/ E(u8, CHALLENGE_RECRUITMENT_CD) _31;
    /*0x032*/ u8 _32;
    /*0x033*/ u8 _33;
} ChallengeTrackingStruct; // size: 0x34

#include "game/character_stats.h" // StatTable, ChemistryTable, CharacterStats

extern CharacterStats inMemRoster[TEAMS_PER_GAME][PLAYERS_PER_TEAM];

typedef struct _UnkSimulationRelatedStruct {
    /*0x00*/ u32 _00; // frameCountRelated
    /*0x04*/ u8 _04;  // loadingStateRelated?
    /*0x05*/ u8 _05;  // highLevelSimulationIndicator
    /*0x06*/ u8 _06;  // highLevelSimulationSomething
    /*0x07*/ u8 _07;
    /*0x08*/ u8 _08; // endDemo?
    /*0x09*/ u8 _09;
    // padding 2 bytes
} UnkSimulationRelatedStruct; // size: 0xC

extern UnkSimulationRelatedStruct unkSimulationRelatedStruct;

extern f32 vecDotProduct(VecXYZ* a, VecXYZ* b);

extern ChallengeTrackingStruct starMissionCompletionTracker[54];

typedef struct _SomeStarDashStruct {
    /*0x000*/ s16 _0[2];
    /*0x004*/ u8 _4[6];
    /*0x00A*/ u8 _pad_A[2]; // 2 bytes of padding for f32 alignment
    /*0x00C*/ f32 _A;
    /*0x010*/ u8 pad[24];
} SomeStarDashStruct; // size: 0x28

typedef struct _UnkStarDashFloatStruct {
    /*0x000*/ f32 _0;
    /*0x004*/ f32 _4;
    /*0x008*/ f32 _8;
    /*0x00C*/ f32 _C;
    /*0x010*/ f32 _10;
    /*0x014*/ f32 _14;
    /*0x018*/ f32 _18;
    /*0x01C*/ f32 _1C;
    /*0x020*/ s16 _20;
} UnkStarDashFloatStruct; // size: 0x24 (0x22 + tail padding)

typedef struct _MaybeWallBallStruct {
    /*0x000*/ f32 _0; // start of wall ball struct?
    /*0x004*/ f32 _4;
    /*0x008*/ f32 zPositionOfSomeWall;
    /*0x00C*/ f32 _C;
    /*0x010*/ f32 _10;
    /*0x014*/ f32 _14;
    /*0x018*/ f32 _18;
    /*0x01C*/ f32 _1C;
    /*0x020*/ f32 _20;
    /*0x024*/ s16 _24;
    /*0x026*/ s16 _26;
    /*0x028*/ u8 _28;
    /*0x029*/ u8 coinGenerationCategory;
    /*0x02A*/ u8 coinRelated[26];
} MaybeWallBallStruct; // size: 0x44

typedef struct _BB_barrelStruct {
    /*0x000*/ VecXYZ currentPos;
    /*0x00C*/ VecXYZ desiredPos;
    /*0x018*/ VecXYZ posAtStartOfTurn;
    /*0x024*/ f32 velo_bounceUpOnBlowUp;
    /*0x028*/ f32 _28;
    /*0x02C*/ s16 animationCounter;
    /*0x02E*/ s16 delayUntilBlownUp;
    /*0x030*/ u8 barrelState;
    /*0x031*/ u8 barrelColour;
    /*0x032*/ u8 replacingBarrelInd;
    /*0x033*/ u8 pad;
} BB_barrelStruct; // size: 0x34

typedef struct _UnkStructMinigame {
    /*0x000*/ VecXYZ _0;
    /*0x00C*/ VecXYZ _C;
    /*0x018*/ s32 coins[10]; // coin pool indices carried by this object (rep_3520)
    /*0x040*/ u8 _40[4];
    /*0x044*/ VecXYZ _44;
    /*0x050*/ VecXYZ _50;
    /*0x05C*/ VecXYZ _5C;
} UnkStructMinigame; // size: 0x68

// Per-player arrays (index = player slot 0..3).
typedef struct _MiniGameControlStruct {
    /*0x00*/ s8 characterIndex[4];
    /*0x04*/ u8 charID[4]; // index into lbl_800E8558 (fn_3_90CB0)
    /*0x08*/ u8 _08[4];
    /*0x0C*/ u8 battingHandedness[4];
    /*0x10*/ u8 aIStrength[4];
    /*0x14*/ s8 turnOrder[4]; // [0] batter, [1] pitcher, then the fielders
    /*0x18*/ s8 _18[4];
    /*0x1C*/ u8 _1C[4];
    /*0x20*/ u8 _20[4];
    /*0x24*/ u8 _24[4];
    /*0x28*/ s8 fieldOrder[4]; // [0] pitcher, then the fielders
} MiniGameControlStruct; // size: 0x2C

/*foul	1
caught	2
groundRuleDouble	4
homerun	6	*/
typedef enum _TOY_FIELD_RESULT {
    TOY_FIELD_RESULT_FOUL = 1,
    TOY_FIELD_RESULT_CAUGHT = 2,
    TOY_FIELD_RESULT_GROUND_RULE_DOUBLE = 4,
    TOY_FIELD_RESULT_HOMERUN = 6
} TOY_FIELD_RESULT;

/*None	0
BobOmbDerby	1
WallBall	2
BarrelBatter	3
ChainChompSprint	4
PiranhaPanic	5
StarDash	6
MarioGrandPrix	7	*/

typedef enum _MINI_GAME_ID {
    MINI_GAME_ID_NONE = 0,
    MINI_GAME_ID_BOBOMB_DERBY = 1,
    MINI_GAME_ID_WALLBALL = 2,
    MINI_GAME_ID_BARREL_BATTER = 3,
    MINI_GAME_ID_CHAINCHOMP_SPRINT = 4,
    MINI_GAME_ID_PIRANHA_PANIC = 5,
    MINI_GAME_ID_STAR_DASH = 6,
    MINI_GAME_ID_MARIO_GRAND_PRIX = 7
} MINI_GAME_ID;

/*multiplayer/ChallengeEasy	0
ChallengeNormal	1
challengeHard	2
soloNonChallenge	3	*/
typedef enum _MINIGAME_DIFFICULTY {
    MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_EASY = 0,
    MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_NORMAL = 1,
    MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD = 2,
    MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE = 3
} MINIGAME_DIFFICULTY;

/*calculateNewWalls	0
dropInNewWalls	1
pitchOrWaitingForPitch	2	*/

typedef enum _WALL_BALL_GAME_STATE {
    WALL_BALL_GAME_STATE_CALCULATE_NEW_WALLS = 0,
    WALL_BALL_GAME_STATE_DROP_IN_NEW_WALLS = 1,
    WALL_BALL_GAME_STATE_PITCH_OR_WAITING_FOR_PITCH = 2
} WALL_BALL_GAME_STATE;

typedef struct _MiniGameResultSlot {
    /*0x0*/ u8 player;
    /*0x1*/ u8 taken;
} MiniGameResultSlot; // size: 0x2

typedef struct _MiniGamePointsPair {
    /*0x0*/ s16 current;
    /*0x2*/ s16 latest;
} MiniGamePointsPair; // size: 0x4

typedef struct _MiniGameRoleStreak {
    /*0x0*/ u8 role;
    /*0x1*/ u8 count;
} MiniGameRoleStreak; // size: 0x2

typedef struct _MiniGameSlot9 {
    /*0x0*/ s8 _0; // character id, < 0: none
    /*0x1*/ u8 _1;
    /*0x2*/ s8 _2;
    /*0x3*/ s8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
    /*0x6*/ s8 _6;
    /*0x7*/ s8 _7;
    /*0x8*/ u8 _8;
} MiniGameSlot9; // size: 0x9

typedef struct _MiniGameStruct {
    /*0x000*/ u8 _0;
    /*0x001*/ u8 _1;
    /*0x002*/ u8 _2;
    /*0x003*/ u8 _3;
    /*0x004*/ u8 _4;
    /*0x005*/ u8 _5;
    /*0x006*/ u8 _6;
    /*0x007*/ u8 _7;
    /*0x008*/ u8 _8;
    /*0x009*/ u8 _9;
    /*0x00A*/ u8 _A;
    /*0x00B*/ u8 _B;
    /*0x00C*/ u8 _C;
    /*0x00D*/ u8 _D;
    /*0x00E*/ u8 _E;
    /*0x00F*/ u8 _F;
    /*0x010*/ u8 _10;
    /*0x011*/ u8 _11;
    /*0x012*/ u8 _12;
    /*0x013*/ u8 _13;
    /*0x014*/ u8 _14;
    /*0x015*/ u8 _15;
    /*0x016*/ u8 _16;
    /*0x017*/ u8 _17;
    /*0x018*/ u8 _18;
    /*0x019*/ u8 _19;
    /*0x01A*/ u8 _1A;
    /*0x01B*/ u8 _1B;
    /*0x01C*/ s16 _1C;
    /*0x01E*/ s16 _1E;
    /*0x020*/ u8 _20;
    /*0x021*/ u8 _21;
    /*0x022*/ u8 _22;
    /*0x023*/ u8 _23;
    /*0x024*/ u8 _24;
    /*0x025*/ u8 _25;
    /*0x026*/ u8 _26;
    /*0x027*/ u8 _27;
    /*0x028*/ u8 _28;
    /*0x029*/ u8 _29;
    /*0x02A*/ u8 _2A;
    /*0x02B*/ u8 _2B;
    /*0x02C*/ u8 _2C;
    /*0x02D*/ u8 _2D;
    /*0x02E*/ u8 _2E;
    /*0x02F*/ u8 _2F;
    /*0x030*/ u8 _30;
    /*0x031*/ u8 _31;
    /*0x032*/ u8 _32;
    /*0x033*/ u8 _33;
    /*0x034*/ u8 _34;
    /*0x035*/ u8 _35[3];
    /*0x038*/ f32 _38;
    /*0x03C*/ f32 _3C;
    /*0x040*/ f32 _40[4];
    /*0x050*/ s16 _50;
    /*0x052*/ s16 _52;
    /*0x054*/ s16 _54;
    /*0x056*/ s16 _56;
    /*0x058*/ s16 _58;
    /*0x05A*/ s16 _5A[4];
    /*0x062*/ u8 _62;
    /*0x063*/ u8 _63;
    /*0x064*/ u8 _64;
    /*0x065*/ u8 _65;
    /*0x066*/ u8 _66;
    /*0x067*/ u8 _67;
    /*0x068*/ u8 _68;
    /*0x069*/ u8 _69;
    /*0x06A*/ u8 _6A;
    /*0x06B*/ u8 _6B[5];
    /*0x070*/ u8 _70[26];
    /*0x08A*/ s16 _8A[8];
    /*0x09A*/ u8 _9A[14];
    /*0x0A8*/ f32 _A8;
    /*0x0AC*/ f32 _AC;
    /*0x0B0*/ f32 _B0;
    /*0x0B4*/ f32 _B4;
    /*0x0B8*/ f32 _B8;
    /*0x0BC*/ f32 _BC;
    /*0x0C0*/ f32 _C0;
    /*0x0C4*/ s32 _C4;

    /*0x0C8*/ SomeStarDashStruct _CA;
    /*0x0F0*/ SomeStarDashStruct _F2;
    /*0x118*/ SomeStarDashStruct _11A;
    /*0x140*/ SomeStarDashStruct _142;
    /*0x168*/ SomeStarDashStruct _16A;
    /*0x190*/ SomeStarDashStruct _192;
    /*0x1B8*/ SomeStarDashStruct _1BA;
    /*0x1E0*/ SomeStarDashStruct _1E2;
    /*0x208*/ SomeStarDashStruct _20A;
    /*0x230*/ s16 _230;
    /*0x232*/ s16 _232[2];
    /*0x236*/ u8 _236[2];
    /*0x238*/ UnkStarDashFloatStruct _238;
    /*0x25C*/ SomeStarDashStruct _25A;
    /*0x284*/ SomeStarDashStruct _282;
    /*0x2AC*/ SomeStarDashStruct _2AA;
    /*0x2D4*/ SomeStarDashStruct _2D2;
    /*0x2FC*/ SomeStarDashStruct _2FA;
    /*0x324*/ SomeStarDashStruct _322;
    /*0x34C*/ u8 pad[2];
    /*0x34E*/ u8 _34E[40];
    /*0x376*/ u8 _376[40];
    /*0x39E*/ u8 _39E[40];
    /*0x3C6*/ u8 _3C6[40];
    /*0x3EE*/ u8 _3EE[40];
    /*0x416*/ u8 _416[40];
    /*0x43E*/ u8 _43E[40];
    /*0x466*/ u8 _466[40];
    /*0x48E*/ u8 _48E[40];
    /*0x4B6*/ u8 _4B6[40];
    /*0x4DE*/ u8 _4DE[40];
    /*0x506*/ u8 _506[40];
    /*0x52E*/ u8 _52E[40];
    /*0x556*/ u8 _556[40];
    /*0x57E*/ u8 _57E[40];
    /*0x5A6*/ u8 _5A6[40];
    /*0x5CE*/ u8 _5CE[40];
    /*0x5F6*/ u8 _5F6[40];
    /*0x61E*/ u8 _61E[40];
    /*0x646*/ u8 _646[40];
    /*0x66E*/ u8 _66E[40];
    /*0x696*/ u8 _696[40];
    /*0x6BE*/ u8 _6BE[40];
    /*0x6E6*/ u8 _6E6[2];
    /*0x6E8*/ f32 _6E8;
    /*0x6EC*/ f32 _6EC;
    /*0x6F0*/ f32 _6F0;
    /*0x6F4*/ f32 _6F4;
    /*0x6F8*/ f32 _6F8;
    /*0x6FC*/ f32 _6FC;
    /*0x700*/ f32 _700;
    /*0x704*/ f32 _704;
    /*0x708*/ f32 _708;
    /*0x70C*/ f32 _70C;
    /*0x710*/ f32 _710;
    /*0x714*/ f32 _714;
    /*0x718*/ u8 pad2[12];
    /*0x724*/ s16 _724;
    /*0x726*/ s16 _726;
    /*0x728*/ s16 _728;
    /*0x72A*/ u8 _72A;
    /*0x72B*/ u8 _72B;
    /*0x72C*/ MaybeWallBallStruct wallBallStruct;
    /*0x770*/ u8 _770[16];
    /*0x780*/ u8 _780;
    /*0x781*/ u8 _781;
    /*0x782*/ u8 _782;
    /*0x783*/ u8 _783;
    /*0x784*/ u8 _784;
    /*0x785*/ u8 _785;
    /*0x786*/ u8 _786;
    /*0x787*/ u8 _787;
    /*0x788*/ u8 _788;
    /*0x789*/ u8 _789;
    /*0x78A*/ u8 _78A;
    /*0x78B*/ u8 _78B;
    /*0x78C*/ u8 _78C;
    /*0x78D*/ u8 _78D;
    /*0x78E*/ u8 _78E;
    /*0x78F*/ u8 _78F;
    /*0x790*/ u8 _790;
    /*0x791*/ u8 _791;
    /*0x792*/ u8 _792;
    /*0x793*/ u8 _793;
    /*0x794*/ u8 _794;
    /*0x795*/ u8 _795;
    /*0x796*/ u8 _796;
    /*0x797*/ u8 _797;
    /*0x798*/ u8 _798;
    /*0x799*/ u8 _799;
    /*0x79A*/ u8 _79A;
    /*0x79B*/ u8 _79B;
    /*0x79C*/ u8 _79C;
    /*0x79D*/ u8 _79D;
    /*0x79E*/ u8 _79E;
    /*0x79F*/ u8 _79F;
    /*0x7A0*/ u8 _7A0;
    /*0x7A1*/ u8 _7A1;
    /*0x7A2*/ u8 _7A2;
    /*0x7A3*/ u8 _7A3;
    /*0x7A4*/ u8 _7A4;
    /*0x7A5*/ u8 _7A5;
    /*0x7A6*/ u8 _7A6;
    /*0x7A7*/ u8 _7A7;
    /*0x7A8*/ u8 _7A8;
    /*0x7A9*/ u8 _7A9;
    /*0x7AA*/ u8 _7AA;
    /*0x7AB*/ u8 _7AB;
    /*0x7AC*/ u8 _7AC;
    /*0x7AD*/ u8 _7AD;
    /*0x7AE*/ u8 _7AE;
    /*0x7AF*/ u8 _7AF;
    /*0x7B0*/ u8 _7B0;
    /*0x7B1*/ u8 _7B1;
    /*0x7B2*/ u8 _7B2;
    /*0x7B3*/ u8 _7B3;
    /*0x7B4*/ u8 _7B4;
    /*0x7B5*/ u8 _7B5;
    /*0x7B6*/ u8 _7B6;
    /*0x7B7*/ u8 _7B7;
    /*0x7B8*/ u8 _7B8;
    /*0x7B9*/ u8 _7B9;
    /*0x7BA*/ u8 _7BA;
    /*0x7BB*/ u8 _7BB;
    /*0x7BC*/ u8 _7BC;
    /*0x7BD*/ u8 _7BD;
    /*0x7BE*/ u8 _7BE;
    /*0x7BF*/ u8 _7BF;
    /*0x7C0*/ u8 _7C0;
    /*0x7C1*/ u8 _7C1;
    /*0x7C2*/ u8 _7C2;
    /*0x7C3*/ u8 _7C3;
    /*0x7C4*/ u8 _7C4;
    /*0x7C5*/ u8 _7C5;
    /*0x7C6*/ u8 _7C6;
    /*0x7C7*/ u8 _7C7;
    /*0x7C8*/ u8 _7C8;
    /*0x7C9*/ u8 _7C9;
    /*0x7CA*/ u8 _7CA;
    /*0x7CB*/ u8 _7CB;
    /*0x7CC*/ u8 _7CC;
    /*0x7CD*/ u8 _7CD;
    /*0x7CE*/ u8 _7CE;
    /*0x7CF*/ u8 _7CF;
    /*0x7D0*/ u8 _7D0;
    /*0x7D1*/ u8 _7D1;
    /*0x7D2*/ u8 _7D2;
    /*0x7D3*/ u8 _7D3;
    /*0x7D4*/ u8 _7D4;
    /*0x7D5*/ u8 _7D5;
    /*0x7D6*/ u8 _7D6;
    /*0x7D7*/ u8 _7D7;
    /*0x7D8*/ u8 _7D8;
    /*0x7D9*/ u8 _7D9;
    /*0x7DA*/ u8 _7DA;
    /*0x7DB*/ u8 _7DB;
    /*0x7DC*/ u8 _7DC;
    /*0x7DD*/ u8 _7DD;
    /*0x7DE*/ u8 _7DE;
    /*0x7DF*/ u8 _7DF;
    /*0x7E0*/ u8 _7E0;
    /*0x7E1*/ u8 _7E1;
    /*0x7E2*/ u8 _7E2;
    /*0x7E3*/ u8 _7E3;
    /*0x7E4*/ u8 _7E4;
    /*0x7E5*/ u8 _7E5;
    /*0x7E6*/ u8 _7E6;
    /*0x7E7*/ u8 _7E7;
    /*0x7E8*/ u8 _7E8;
    /*0x7E9*/ u8 _7E9;
    /*0x7EA*/ u8 _7EA;
    /*0x7EB*/ u8 _7EB;
    /*0x7EC*/ u8 _7EC;
    /*0x7ED*/ u8 _7ED;
    /*0x7EE*/ u8 _7EE;
    /*0x7EF*/ u8 _7EF;
    /*0x7F0*/ u8 _7F0;
    /*0x7F1*/ u8 _7F1;
    /*0x7F2*/ u8 _7F2;
    /*0x7F3*/ u8 _7F3;
    /*0x7F4*/ u8 _7F4;
    /*0x7F5*/ u8 _7F5;
    /*0x7F6*/ u8 _7F6;
    /*0x7F7*/ u8 _7F7;
    /*0x7F8*/ u8 _7F8;
    /*0x7F9*/ u8 _7F9;
    /*0x7FA*/ u8 _7FA;
    /*0x7FB*/ u8 _7FB;
    /*0x7FC*/ u8 _7FC;
    /*0x7FD*/ u8 _7FD;
    /*0x7FE*/ u8 _7FE;
    /*0x7FF*/ u8 _7FF;
    /*0x800*/ u8 _800;
    /*0x801*/ u8 _801;
    /*0x802*/ u8 _802;
    /*0x803*/ u8 _803;
    /*0x804*/ u8 _804;
    /*0x805*/ u8 _805;
    /*0x806*/ u8 _806;
    /*0x807*/ u8 _807;
    /*0x808*/ u8 _808;
    /*0x809*/ u8 _809;
    /*0x80A*/ u8 _80A;
    /*0x80B*/ u8 _80B;
    /*0x80C*/ u8 _80C;
    /*0x80D*/ u8 _80D;
    /*0x80E*/ u8 _80E;
    /*0x80F*/ u8 _80F;
    /*0x810*/ u8 _810;
    /*0x811*/ u8 _811;
    /*0x812*/ u8 _812;
    /*0x813*/ u8 _813;
    /*0x814*/ u8 _814;
    /*0x815*/ u8 _815;
    /*0x816*/ u8 _816;
    /*0x817*/ u8 _817;
    /*0x818*/ u8 _818;
    /*0x819*/ u8 _819;
    /*0x81A*/ u8 _81A;
    /*0x81B*/ u8 _81B;
    /*0x81C*/ u8 _81C;
    /*0x81D*/ u8 _81D;
    /*0x81E*/ u8 _81E;
    /*0x81F*/ u8 _81F;
    /*0x820*/ u8 _820;
    /*0x821*/ u8 _821;
    /*0x822*/ u8 _822;
    /*0x823*/ u8 _823;
    /*0x824*/ u8 _824;
    /*0x825*/ u8 _825;
    /*0x826*/ u8 _826;
    /*0x827*/ u8 _827;
    /*0x828*/ u8 _828;
    /*0x829*/ u8 _829;
    /*0x82A*/ u8 _82A;
    /*0x82B*/ u8 _82B;
    /*0x82C*/ u8 _82C;
    /*0x82D*/ u8 _82D;
    /*0x82E*/ u8 _82E;
    /*0x82F*/ u8 _82F;
    /*0x830*/ u8 _830;
    /*0x831*/ u8 _831;
    /*0x832*/ u8 _832;
    /*0x833*/ u8 _833;
    /*0x834*/ u8 _834;
    /*0x835*/ u8 _835;
    /*0x836*/ u8 _836;
    /*0x837*/ u8 _837;
    /*0x838*/ u8 _838;
    /*0x839*/ u8 _839;
    /*0x83A*/ u8 _83A;
    /*0x83B*/ u8 _83B;
    /*0x83C*/ u8 _83C;
    /*0x83D*/ u8 _83D;
    /*0x83E*/ u8 _83E;
    /*0x83F*/ u8 _83F;
    /*0x840*/ u8 _840;
    /*0x841*/ u8 _841;
    /*0x842*/ u8 _842;
    /*0x843*/ u8 _843;
    /*0x844*/ u8 _844;
    /*0x845*/ u8 _845;
    /*0x846*/ u8 _846;
    /*0x847*/ u8 _847;
    /*0x848*/ u8 _848;
    /*0x849*/ u8 _849;
    /*0x84A*/ u8 _84A;
    /*0x84B*/ u8 _84B;
    /*0x84C*/ u8 _84C;
    /*0x84D*/ u8 _84D;
    /*0x84E*/ u8 _84E;
    /*0x84F*/ u8 _84F;
    /*0x850*/ u8 _850;
    /*0x851*/ u8 _851;
    /*0x852*/ u8 _852;
    /*0x853*/ u8 _853;
    /*0x854*/ u8 _854;
    /*0x855*/ u8 _855;
    /*0x856*/ u8 _856;
    /*0x857*/ u8 _857;
    /*0x858*/ u8 _858;
    /*0x859*/ u8 _859;
    /*0x85A*/ u8 _85A;
    /*0x85B*/ u8 _85B;
    /*0x85C*/ s16 _85C;
    /*0x85E*/ u8 wallBallWall2Pos;
    /*0x85F*/ u8 pad3;
    /*0x860*/ BB_barrelStruct barrels[15];
    /*0xB6C*/ UnkStructMinigame _B6C;
    /*0xBD4*/ VecXYZ _BD4;
    /*0xBE0*/ f32 _BE0;
    /*0xBE4*/ f32 _BE4;
    /*0xBE8*/ s16 _BE8;
    /*0xBEA*/ s16 _BEA;
    /*0xBEC*/ u8 _BEC;
    /*0xBED*/ u8 _BED;
    /*0xBEE*/ u8 _BEE;
    /*0xBEF*/ u8 _BEF[62];
    /*0xC2D*/ u8 _C2D[7];
    /*0xC34*/ s16 _C34;
    /*0xC36*/ s16 _C36;
    /*0xC38*/ u8 _C38;
    /*0xC39*/ u8 _C39[52];
    /*0xC6D*/ u8 _C6D[64];
    /*0xCAD*/ u8 _CAD;
    /*0xCAE*/ u8 pad4[2];
    /*0xCB0*/ f32 _CB0;
    /*0xCB4*/ f32 _CB4;
    /*0xCB8*/ f32 _CB8;
    /*0xCBC*/ f32 _CBC;
    /*0xCC0*/ f32 _CC0;
    /*0xCC4*/ f32 _CC4;
    /*0xCC8*/ f32 _CC8;
    /*0xCCC*/ s16 _CCC;
    /*0xCCE*/ u8 _CCE[2];
    /*0xCD0*/ VecXYZ wallBall_coinCoordinates[100];
    /*0x1180*/ VecXYZ wallBall_coinVelocity[100];
    /*0x1630*/ f32 _1630;
    /*0x1634*/ u8 pad10[396];
    /*0x17C0*/ s32 _17C0;
    /*0x17C4*/ s32 _17C4;
    union {
        /*0x17C8*/ s16 wallBall_coinsVisibleFrameCounter;
        /*0x17C8*/ s16 wallBall_coinFrames[100]; // per coin
    };
    /*0x1890*/ s16 miniGameCurrentPoints[4];
    /*0x1898*/ s16 miniGameLatestPoints[4];
    /*0x18A0*/ s16 _18A0;
    /*0x18A2*/ s16 bB_bombBarrelHitInd;
    /*0x18A4*/ s16 bB_bombBarrelID;
    /*0x18A6*/ s16 _18A6;
    /*0x18A8*/ s16 bODControllerInputAllowedInd;
    /*0x18AA*/ s16 framesSincePanelHit;
    /*0x18AC*/ u8 pad12[12];
    /*0x18B8*/ s16 _18B8;
    /*0x18BA*/ s16 _18BA;
    /*0x18BC*/ MiniGamePointsPair minigamePoints_current_Latest[4];
    /*0x18CC*/ MiniGameControlStruct minigameControlStruct[1];
    /*0x18F8*/ s8 minigameFielderIndex[4];
    /*0x18FC*/ s8 _18FC[4];
    /*0x1900*/ s8 _1900[4];
    /*0x1904*/ s8 minigamePlayerSelectedOrder; // the pitcher
    /*0x1905*/ s8 rosterID;
    /*0x1906*/ u8 miniGameNumberOfParticipants;
    /*0x1907*/ u8 _1907;
    /*0x1908*/ s8 _1908;
    /*0x1909*/ u8 multiPlayerInd;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 turnOverStatus;
    /*0x190C*/ u8 turnNumberWithinRound;
    /*0x190D*/ u8 _190D;
    /*0x190E*/ u8 _190E;
    /*0x190F*/ u8 _190F;
    /*0x1910*/ u8 _1910;
    /*0x1911*/ u8 _1911;
    /*0x1912*/ u8 pointsTargetReachedInd;
    /*0x1913*/ u8 _1913;
    /*0x1914*/ u8 _1914[4]; // per player
    /*0x1918*/ u8 _1918[4]; // per player
    /*0x191C*/ s8 _191C[4]; // per player: panel progress
    /*0x1920*/ E(u8, TOY_FIELD_RESULT) toyFieldBallStateResult2;
    /*0x1921*/ u8 _1921;
    /*0x1922*/ u8 _1922;
    /*0x1923*/ u8 minigameRelatedIndex;
    /*0x1924*/ u8 runnerNum;
    /*0x1925*/ u8 _1925;
    /*0x1926*/ u8 toyFieldStateInd_collisionRelated;
    /*0x1927*/ u8 reelStop[3];
    /*0x192A*/ u8 reelStart[3];
    /*0x192D*/ u8 _192D; // slot result
    /*0x192E*/ u8 reelSymbol[3];
    /*0x1931*/ u8 _1931;
    /*0x1932*/ s16 _1932;
    /*0x1934*/ u8 _1934;
    /*0x1935*/ s8 playerOrder[4];
    /*0x1939*/ u8 _1939;
    /*0x193A*/ u8 wallBall_coinsVisibleInd[30];
    /*0x1958*/ u8 _1958;
    /*0x1959*/ u8 _1959;
    /*0x195A*/ u8 _195A;
    /*0x195B*/ u8 _195B;
    /*0x195C*/ u8 _195C;
    /*0x195D*/ u8 _195D;
    /*0x195E*/ u8 _195E;
    /*0x195F*/ u8 _195F;
    /*0x1960*/ u8 _1960;
    /*0x1961*/ u8 _1961;
    /*0x1962*/ u8 _1962;
    /*0x1963*/ u8 _1963;
    /*0x1964*/ u8 _1964;
    /*0x1965*/ u8 _1965;
    /*0x1966*/ u8 _1966;
    /*0x1967*/ u8 _1967;
    /*0x1968*/ u8 _1968;
    /*0x1969*/ u8 _1969;
    /*0x196A*/ u8 _196A;
    /*0x196B*/ u8 _196B;
    /*0x196C*/ u8 _196C;
    /*0x196D*/ u8 _196D;
    /*0x196E*/ u8 _196E;
    /*0x196F*/ u8 _196F;
    /*0x1970*/ u8 _1970;
    /*0x1971*/ u8 _1971;
    /*0x1972*/ u8 _1972;
    /*0x1973*/ u8 _1973;
    /*0x1974*/ u8 _1974;
    /*0x1975*/ u8 _1975;
    /*0x1976*/ u8 _1976;
    /*0x1977*/ u8 _1977;
    /*0x1978*/ u8 _1978;
    /*0x1979*/ u8 _1979;
    /*0x197A*/ u8 _197A;
    /*0x197B*/ u8 _197B;
    /*0x197C*/ u8 _197C;
    /*0x197D*/ u8 _197D;
    /*0x197E*/ u8 _197E;
    /*0x197F*/ u8 _197F;
    /*0x1980*/ u8 _1980;
    /*0x1981*/ u8 _1981;
    /*0x1982*/ u8 _1982;
    /*0x1983*/ u8 _1983;
    /*0x1984*/ u8 _1984;
    /*0x1985*/ u8 _1985;
    /*0x1986*/ u8 _1986;
    /*0x1987*/ u8 _1987;
    /*0x1988*/ u8 _1988;
    /*0x1989*/ u8 _1989;
    /*0x198A*/ u8 _198A;
    /*0x198B*/ u8 _198B;
    /*0x198C*/ u8 _198C;
    /*0x198D*/ u8 _198D;
    /*0x198E*/ u8 _198E;
    /*0x198F*/ u8 _198F;
    /*0x1990*/ u8 _1990;
    /*0x1991*/ u8 _1991;
    /*0x1992*/ u8 _1992;
    /*0x1993*/ u8 _1993;
    /*0x1994*/ u8 _1994;
    /*0x1995*/ u8 _1995;
    /*0x1996*/ u8 _1996;
    /*0x1997*/ u8 _1997;
    /*0x1998*/ u8 _1998;
    /*0x1999*/ u8 _1999;
    /*0x199A*/ u8 pad13[4];
    /*0x199E*/ u8 _199E;
    /*0x199F*/ u8 panelHitInd;
    /*0x19A0*/ u8 _19A0;
    /*0x19A1*/ u8 _19A1;
    /*0x19A2*/ u8 _19A2;
    /*0x19A3*/ u8 _19A3;
    /*0x19A4*/ bool TF_ballDespawnedInd;
    /*0x19A5*/ u8 _19A5;
    /*0x19A6*/ u8 _19A6;
    /*0x19A7*/ u8 _19A7;
    /*0x19A8*/ u8 challenge_minigame_haven_tWonYetIndicator;
    /*0x19A9*/ u8 _19A9;
    /*0x19AA*/ u8 _19AA;
    /*0x19AB*/ u8 _19AB;
    /*0x19AC*/ f32 lastKnownBallPosX;
    /*0x19B0*/ f32 lastKnownBallPosZ;
    /*0x19B4*/ s16 toyField_selectedTurns;
    /*0x19B6*/ s16 toyField_turnNumber;
    /*0x19B8*/ s16 TF_framesSinceHittingPanel;
    /*0x19BA*/ s16 _19BA;
    /*0x19BC*/ s16 _19BC;
    /*0x19BE*/ MiniGameRoleStreak roleStreak[4]; // per player: last role (0 pitcher, 1 batter, 2 fielder) and repeat count
    /*0x19C6*/ s8 _19C6;
    /*0x19C7*/ u8 _19C7;
    /*0x19C8*/ u8 maybeTFCollisionResultState;
    /*0x19C9*/ E(u8, TOY_FIELD_RESULT) toyFieldBallStateResult;
    /*0x19CA*/ u8 toyField_next_CoinsX2_TurnNumber;
    /*0x19CB*/ u8 toyField_pointMultiplier;
    /*0x19CC*/ u8 toyfield_waitFor_CoinsX2_AnimationToEnd;
    /*0x19CD*/ u8 _19CD;
    /*0x19CE*/ u8 _19CE;
    /*0x19CF*/ u8 _19CF;
    union {
        /*0x19D0*/ s16 _19D0;
        /*0x19D0*/ u8 _19D0b[2]; // rep_AC8 uses the high byte as a flag
    };
    /*0x19D2*/ s16 _19D2[4];
    /*0x19DA*/ s8 _19DA[4];
    /*0x19DE*/ u8 _19DE;
    /*0x19DF*/ u8 _19DF;
    /*0x19E0*/ u8 _19E0;
    /*0x19E1*/ u8 _19E1;
    /*0x19E2*/ u8 _19E2;
    /*0x19E3*/ u8 _19E3;
    /*0x19E4*/ s8 _19E4; // level reached in this minigame (g_d_GameSettings._14[mode - 1])
    /*0x19E5*/ u8 _19E5;
    /*0x19E6*/ u8 _19E6;
    /*0x19E7*/ u8 _19E7;
    /*0x19E8*/ MiniGameSlot9 _19E8[4];
    /*0x1A0C*/ s8 _1A0C;
    /*0x1A0D*/ u8 _1A0D;
    /*0x1A0E*/ u8 _1A0E;
    /*0x1A0F*/ s8 _1A0F[4];
    /*0x1A13*/ u8 _1A13[4];
    union {
        /*0x1A17*/ u8 battingHandedness[9];
        struct {
            /*0x1A17*/ u8 _1A17[4]; // battingHandedness[0..3]: per player
            /*0x1A1B*/ u8 _1A1B;    // the rest are menu state (auto_00_00106DFC_text)
            /*0x1A1C*/ u8 _1A1C;
            /*0x1A1D*/ u8 _1A1D;
            /*0x1A1E*/ u8 _1A1E;
            /*0x1A1F*/ u8 _1A1F;
        };
    };
    /*0x1A20*/ u8 _1A20;
    /*0x1A21*/ u8 _1A21;
    /*0x1A22*/ u8 _1A22;
    /*0x1A23*/ u8 _1A23;
    /*0x1A24*/ u8 _1A24[2];
    /*0x1A26*/ s16 pointsReqToWin_challenge;
    /*0x1A28*/ s16 someGraphicFrameCountdown;
    /*0x1A2A*/ E(u8, MINI_GAME_ID) GameMode_MiniGame;
    /*0x1A2B*/ E(u8, MINIGAME_DIFFICULTY) soloMinigameDifficulty;
    /*0x1A2C*/ s8 _1A2C;
    /*0x1A2D*/ u8 miniGameTurnCounter;
    /*0x1A2E*/ u8 bB_pitchesRemainingInTurn;
    /*0x1A2F*/ u8 bODRoundStartingNumPitches;
    /*0x1A30*/ u8 pad17[7];
    /*0x1A37*/ u8 _1A37;
    /*0x1A38*/ u8 _1A38;
    /*0x1A39*/ u8 _1A39;
    /*0x1A3A*/ u8 _1A3A;
    /*0x1A3B*/ u8 pauseInd;
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D;
    /*0x1A3E*/ u8 _1A3E;
    /*0x1A3F*/ u8 _1A3F;
    /*0x1A40*/ u8 _1A40;
    /*0x1A41*/ u8 _1A41;
    /*0x1A42*/ u8 bODRelated;
    /*0x1A43*/ u8 _1A43;
    /*0x1A44*/ u8 _1A44;
    /*0x1A45*/ u8 _1A45;
    /*0x1A46*/ u8 _1A46[2];
    /*0x1A48*/ f32 wallBallSomeXPos;
    /*0x1A4C*/ f32 wallBallSomeZPos;
    /*0x1A50*/ f32 wallBallWaitingLocations[8];
    /*0x1A70*/ s16 wallBallPitcherRotationCounter;
    /*0x1A72*/ s16 postBallStoppedCounter;
    /*0x1A74*/ s16 wallBallPitchPower;
    /*0x1A76*/ s16 wallBallPitchPowerRemaining;
    /*0x1A78*/ s16 _1A78;
    /*0x1A7A*/ s16 wallBall_UnknownAlways0;
    /*0x1A7C*/ u8 wallBallSpecialWallPos;
    /*0x1A7D*/ u8 _1A7D;
    /*0x1A7E*/ u8 wallBallRotatePitchersInd;
    /*0x1A7F*/ E(u8, WALL_BALL_GAME_STATE) wallBallGameState;
    /*0x1A80*/ u8 _1A80;
    /*0x1A81*/ bool ballStoppedBreakingWallsInd;
    /*0x1A82*/ u8 wallIndexTracker[7];
    /*0x1A89*/ u8 wallBall_hitNoteBlock;
    /*0x1A8A*/ u8 wallBall_hitBowserWall;
    /*0x1A8B*/ s8 _1A8B;
    /*0x1A8C*/ u8 _1A8C[2];
    /*0x1A8E*/ s16 bOD_HitPowerOfEachChar[4];
    /*0x1A96*/ u8 bODBombTimers[10]; // explosion timers, 0: free (rep_31F0)
    /*0x1AA0*/ u8 bODHitHistory[4][10]; // per player, newest first (rep_31F0)
    /*0x1AC8*/ u8 bODRelated2;
    /*0x1AC9*/ u8 barrelBatter_BODPitchSelectionType;
    /*0x1ACA*/ u8 minigamePitchSpeedAdjustment;
    /*0x1ACB*/ u8 bOD_HRStreak;
    /*0x1ACC*/ u8 bODCharacterHRStreakTracker[8];
    /*0x1AD4*/ u8 bODRelated3;
    /*0x1AD5*/ u8 bOD_KingBombInd;
    /*0x1AD6*/ u8 bODAngleIndexBasedOnHitPower;
    /*0x1AD7*/ u8 bOD_hitFinishedInd;
    /*0x1AD8*/ u8 _1AD8;
    /*0x1AD9*/ u8 _1AD9;
    /*0x1ADA*/ u8 barrelBatterChargeMeter;
    /*0x1ADB*/ u8 barrelBatter_scoreCalculatedInd;
    /*0x1ADC*/ s8 barrelBatter_hitBarrelID;
    /*0x1ADD*/ u8 barrelBatter_barrelsHit;
    /*0x1ADE*/ u8 _1ADE[2];
    /*0x1AE0*/ f32 _1AE0;
    /*0x1AE4*/ f32 _1AE4;
    /*0x1AE8*/ f32 _1AE8;
    /*0x1AEC*/ f32 _1AEC;
    /*0x1AF0*/ f32 _1AF0;
    /*0x1AF4*/ f32 _1AF4;
    /*0x1AF8*/ s16 _1AF8;
    /*0x1AFA*/ s16 _1AFA;
    /*0x1AFC*/ s16 _1AFC;
    /*0x1AFE*/ u8 _1AFE[2];
    /*0x1B00*/ s16 _1B00;
    /*0x1B02*/ s16 _1B02;
    /*0x1B04*/ s16 _1B04;
    /*0x1B06*/ s16 _1B06;
    /*0x1B08*/ s16 _1B08;
    /*0x1B0A*/ s16 _1B0A;
    /*0x1B0C*/ s16 _1B0C;
    /*0x1B0E*/ s16 _1B0E;
    /*0x1B10*/ s16 _1B10;
    /*0x1B12*/ s16 _1B12;
    /*0x1B14*/ u8 _1B14;
    /*0x1B15*/ u8 _1B15[4];
    /*0x1B19*/ u8 _1B19;
    /*0x1B1A*/ u8 _1B1A;
    /*0x1B1B*/ u8 _1B1B;
    /*0x1B1C*/ u8 _1B1C;
    /*0x1B1D*/ u8 _1B1D;
    /*0x1B1E*/ u8 _1B1E;
    /*0x1B1F*/ u8 _1B1F;
    /*0x1B20*/ u8 _1B20;
    /*0x1B21*/ u8 _1B21;
    /*0x1B22*/ u8 _1B22;
    /*0x1B23*/ u8 _1B23;
    /*0x1B24*/ u8 _1B24;
    /*0x1B25*/ u8 _1B25;
    /*0x1B26*/ u8 _1B26;
    /*0x1B27*/ u8 _1B27;
    /*0x1B28*/ u8 _1B28;
    /*0x1B29*/ u8 _1B29;
    /*0x1B2A*/ u8 _1B2A;
    /*0x1B2B*/ u8 _1B2B;
    /*0x1B2C*/ u8 _1B2C;
    /*0x1B2D*/ u8 _1B2D;
    /*0x1B2E*/ u8 _1B2E;
    /*0x1B2F*/ u8 _1B2F[4]; // per runner
    /*0x1B33*/ u8 _1B33;
    /*0x1B34*/ s16 _1B34[4]; // indexed by MiniGameControlStruct._24
    /*0x1B3C*/ s16 _1B3C;
    /*0x1B3E*/ u8 _1B3E[6];
    /*0x1B44*/ s16 _1B44;
    /*0x1B46*/ u8 _1B46[6];
    /*0x1B4C*/ s16 _1B4C;
    /*0x1B4E*/ s16 _1B4E;
    /*0x1B50*/ s16 _1B50;
    /*0x1B52*/ u8 _1B52[6];
    /*0x1B58*/ u8 _1B58;
    /*0x1B59*/ u8 _1B59;
    /*0x1B5A*/ u8 _1B5A;
    /*0x1B5B*/ u8 _1B5B;
    /*0x1B5C*/ u8 _1B5C;
    /*0x1B5D*/ u8 _1B5D;
    /*0x1B5E*/ u8 _1B5E;
    /*0x1B5F*/ u8 _1B5F;
    /*0x1B60*/ u8 _1B60;
    /*0x1B61*/ u8 _1B61;
    /*0x1B62*/ u8 _1B62[30];
    /*0x1B80*/ u8 _1B80[4];
    /*0x1B84*/ u8 _1B84[1];
    /*0x1B85*/ u8 _1B85[49];
    /*0x1BB6*/ u8 _1BB6;
    /*0x1BB7*/ u8 _1BB7;
    /*0x1BB8*/ u8 _1BB8;
    /*0x1BB9*/ u8 _1BB9;
    /*0x1BBA*/ u8 _1BBA;
    /*0x1BBB*/ u8 _1BBB;
    /*0x1BBC*/ u8 _1BBC;
    /*0x1BBD*/ u8 _1BBD;
    /*0x1BBE*/ u8 _1BBE;
    /*0x1BBF*/ u8 _1BBF;
    /*0x1BC0*/ u8 _1BC0;
    /*0x1BC1*/ u8 _1BC1;
    /*0x1BC2*/ u8 _1BC2;
    /*0x1BC3*/ u8 _1BC3;
    /*0x1BC4*/ u8 _1BC4;
    /*0x1BC5*/ u8 _1BC5;
    /*0x1BC6*/ u8 _1BC6;
    /*0x1BC7*/ u8 _1BC7;
    /*0x1BC8*/ u8 _1BC8;
    /*0x1BC9*/ u8 _1BC9;
    /*0x1BCA*/ u8 _1BCA;
    /*0x1BCB*/ u8 _1BCB;
    /*0x1BCC*/ u8 _1BCC;
    /*0x1BCD*/ u8 _1BCD;
    /*0x1BCE*/ u8 _1BCE;
    /*0x1BCF*/ u8 _1BCF;
    /*0x1BD0*/ u8 _1BD0;
    /*0x1BD1*/ u8 _1BD1;
    /*0x1BD2*/ u8 _1BD2;
    /*0x1BD3*/ u8 _1BD3;
    /*0x1BD4*/ u8 _1BD4;
    /*0x1BD5*/ u8 _1BD5;
    /*0x1BD6*/ u8 _1BD6[18];
    /*0x1BE8*/ u8 _1BE8[50];
    /*0x1C1A*/ u8 _1C1A[50];
    /*0x1C4C*/ u8 _1C4C[50];
    /*0x1C7E*/ u8 _1C7E;
    /*0x1C7F*/ u8 _1C7F;
    /*0x1C80*/ u8 _1C80;
    /*0x1C81*/ u8 _1C81[9];
    /*0x1C8A*/ u8 _1C8A[4];
    /*0x1C8E*/ u8 _1C8E[4];
    /*0x1C92*/ u8 _1C92[8];
    /*0x1C9A*/ u8 _1C9A[4]; // per fielder (mode 5)
    /*0x1C9E*/ u8 _1C9E;
    /*0x1C9F*/ u8 _1C9F;
    /*0x1CA0*/ u8 _1CA0[2];
    /*0x1CA2*/ u8 _1CA2;
    /*0x1CA3*/ u8 _1CA3;
    /*0x1CA4*/ u8 _1CA4;
    /*0x1CA5*/ u8 _1CA5[4];
    /*0x1CA9*/ u8 _1CA9;
    /*0x1CAA*/ u8 _1CAA;
    /*0x1CAB*/ u8 _1CAB;
    /*0x1CAC*/ u8 _1CAC;
    /*0x1CAD*/ u8 _1CAD[4];
    /*0x1CB1*/ u8 _1CB1[7];
    /*0x1CB8*/ VecXYZ _1CB8[4]; // per fielder: separation from the other fielder
    /*0x1CE8*/ VecXYZ _1CE8;
    /*0x1CF4*/ VecXYZ _1CF4;
    /*0x1D00*/ u8 _1D00[4];
    /*0x1D04*/ VecXYZ _1D04;
    /*0x1D10*/ VecXYZ _1D10;
    /*0x1D1C*/ VecXYZ _1D1C;
    /*0x1D28*/ VecXYZ _1D28;
    /*0x1D34*/ VecXYZ _1D34;
    /*0x1D40*/ f32 _1D40;
    /*0x1D44*/ f32 _1D44;
    /*0x1D48*/ f32 _1D48;
#ifdef TARGET_PC
    /*0x1D4C*/ PTR32(f32) starDashRelated_0_5Or1_5; // 4 bytes on PC too: keeps the GameCube layout for the minigame views
#else
    /*0x1D4C*/ f32* starDashRelated_0_5Or1_5; // points at the speed multiplier (0.5 or 1.5)
#endif
    /*0x1D50*/ s16 _1D50;
    /*0x1D52*/ s16 _1D52;
    /*0x1D54*/ s16 _1D54;
    /*0x1D56*/ s16 _1D56;
    /*0x1D58*/ s16 _1D58;
    /*0x1D5A*/ s16 _1D5A;
    /*0x1D5C*/ u8 _1D5C[6];
    /*0x1D62*/ s16 _1D62;
    /*0x1D64*/ s16 _1D64;
    /*0x1D66*/ s16 _1D66;
    /*0x1D68*/ s16 _1D68;
    /*0x1D6A*/ s16 _1D6A;
    /*0x1D6C*/ u8 _1D6C;
    /*0x1D6D*/ s8 _1D6D;
    /*0x1D6E*/ u8 starDashStunType[4];
    /*0x1D72*/ u8 _1D72;
    /*0x1D73*/ u8 _1D73;
    /*0x1D74*/ u8 playerIDWithPowerup[2];
    /*0x1D76*/ s16 _1D76;
    /*0x1D78*/ u8 _1D78;
    /*0x1D79*/ u8 _1D79;
    /*0x1D7A*/ u8 _1D7A;
    /*0x1D7B*/ u8 _1D7B;
    /*0x1D7C*/ InputStruct _1D7C[4];
    /*0x1DBC*/ u8 _1DBC[4]; // per player: input driven by the CPU this frame (fn_3_12DB80)
    /*0x1DC0*/ u8 _1DC0[4];
    /*0x1DC4*/ u8 _1DC4[4];
    /*0x1DC8*/ u8 _1DC8[4];
    /*0x1DCC*/ s16 bB_cpuSwingFrame;  // pitcher frame at which the CPU swings (fn_3_12DDCC)
    /*0x1DCE*/ u16 bB_cpuStickInput;  // stick direction held with the swing
    /*0x1DD0*/ s8 bB_cpuSwingStep;
    /*0x1DD1*/ u8 bB_cpuSwingPlanned;
    /*0x1DD2*/ s8 bB_cpuPreferLow;    // sort order for the CPU's target choice (fn_3_12E084)
    /*0x1DD3*/ u8 _1DD3[0x1DF4 - 0x1DD3];
    union {
        /*0x1DF4*/ s16 _1DF4[7]; // cleared before HUD updates (fn_3_12C514)
        /*0x1DF4*/ u8 hudFlags[14]; // per-byte HUD requests (rep_31F0: [3], [4])
    };
    /*0x1E02*/ u8 _1E02;
    /*0x1E03*/ u8 _1E03;
#ifdef TARGET_PC
    /*0x1E04*/ PTR32(void) _1E04; // minigame task; PTR32 keeps the GameCube layout
#else
    /*0x1E04*/ void* _1E04; // minigame task (fn_800B0A5C_insertQueue result)
#endif
    /*0x1E08*/ MiniGameResultSlot resultSlot[4];
    /*0x1E10*/ s16 _1E10[6]; // per minigame mode (1..6): last score
    /*0x1E1C*/ u8 _1E1C[6];  // queued minigame modes, indexed by _1E2A
    /*0x1E22*/ u8 _1E22[4]; // per-player score (fn_3_E911C)
    /*0x1E26*/ u8 _1E26[4];
    /*0x1E2A*/ u8 _1E2A;    // round counter
    /*0x1E2B*/ u8 _1E2B;
} MiniGameStruct; // size: 0x1E2C
#ifdef TARGET_PC
_Static_assert(sizeof(MiniGameStruct) == 0x1E2C, "MiniGameStruct must keep its GameCube layout (minigame views overlay it)");
#endif

extern MiniGameStruct g_Minigame;

typedef struct _BatterReachStruct {
    /*0x000*/ f32 HorizontalRangeNear;
    /*0x004*/ f32 HorizontalRangeFar;
    /*0x008*/ f32 VerticalRangeFront;
    /*0x00C*/ f32 VerticalRangeBack;
    /*0x010*/ f32 batOffsetFromBatterX;
    /*0x014*/ f32 batOffsetFromBatterZ;
    /*0x018*/ f32 BoxMoveSpeed;
    /*0x01C*/ f32 PitchingHeight;
    /*0x020*/ f32 TrimmedBat;
} BatterReachStruct; // size: 0x24

extern BatterReachStruct BatterHitbox[54];

// The definition (game/auto_00_00106DFC_text.c) is u8 (s8); its callers were compiled against this one.
#ifndef MINIGAME_CHECK_AI_INPUT_DEFINED
extern u32 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(u8);
#endif

extern u8 swingSoundFrame[2][4];

// m_sound.c declares its own typed view (SndState34C58) of this object.
#ifndef M_SOUND_SNDSTATE
extern struct {
    /* 0x00 */ void* _00; // file loaded by ARAMTransfer
    /* 0x04 */ u32 _04;
    /* 0x08 */ u32 _08;
    /* 0x08 */ u32 _0C;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1C; // written to after sndFXStartEx
    /* 0x20 */ s16 _20;
    /* 0x22 */ s16 _22;
    /* 0x24 */ s16 _24;
    /* 0x26 */ u8 _26;
    /* 0x27 */ u8 _27;
    /* 0x28 */ u8 _28;
    /* 0x29 */ u8 _29;
    /* 0x2a */ u8 _2A;
    /* 0x2b */ u8 _2B;
    /* 0x2c */ u8 _2C;
    /* 0x2d */ u8 _2D;
    /* 0x2e */ u8 _2E;
    /* 0x2f */ u8 _2F;
    /* 0x30 */ u8 _30;
    /* 0x31 */ u8 _31;
    /* 0x32 */ u8 _32;
    /* 0x33 */ u8 _33;
    /* 0x34 */ u8 _34;
} lbl_3_common_bss_34C58; // size: 0x38
#endif

extern InputStruct g_Controls[];

typedef struct {
    /* 0x0 */ s16 _00;
    /* 0x2 */ u8 _02;
    /* 0x3 */ u8 _03;
    /* 0x4 */ u8 _04;
    /* 0x5 */ u8 _05;
    /* 0x6 */ u8 _06;
    /* 0x7 */ u8 _07;
    /* 0x8 */ u8 _08;
} lbl_3_common_bss_32718_struct;

extern lbl_3_common_bss_32718_struct g_UnkSound_32718;

extern struct StarPowerCosts {
    /* 0x0 */ u8 moonShotCost;
    /* 0x1 */ u8 captainStarCost;
    /* 0x2 */ u8 nonCaptain_CaptainStarCost;
    /* 0x3 */ u8 regularStarCost;
} starPowerCosts;

typedef struct {
    /* 0x00 */ f32 aIDifficultyMultiplierArray[2];
    /* 0x08 */ f32 batterAIBoxPosXVelo;
    /* 0x0C */ f32 batterAIBoxPosZVelo;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1C */ f32 _1C;
    /* 0x20 */ f32 boxHorizontalPoint;
    /* 0x24 */ f32 boxVerticalPoint;
    /* 0x28 */ f32 batterAIDesiredXPosInBox;
    /* 0x2C */ f32 batterAIDesiredZPosInBox;
    /* 0x30 */ f32 batterAITrackBallPoorlyOffset;
    /* 0x34 */ f32 aIMoundLocationX;
    /* 0x38 */ f32 aiPitchCurveEndingX;
    /* 0x3C */ f32 _3C;
    /* 0x40 */ s16 AIFrameToBeginPitch;
    /* 0x42 */ u16 _42;
    /* 0x44 */ s16 _44;
    /* 0x46 */ u8 _46;
    /* 0x47 */ u8 _47;
    /* 0x48 */ u8 _48;
    /* 0x49 */ u8 _49;
    /* 0x4A */ u8 aIPitchType;
    /* 0x4B */ u8 aiPitchCurveType;
    /* 0x4C */ s8 aiPitchDirectionInput;
    /* 0x4D */ u8 pitchAIDelayCurveStart;
    /* 0x4E */ u8 nStarPitchesThrownThisAB;
    /* 0x4F */ u8 aIPerfectCharge;
    /* 0x50 */ u8 aIMoundLocationIndex;
    /* 0x51 */ u8 aIPitchDesiredEndingLocIndex;
    /* 0x52 */ u8 aIPitcherPickOffInd;
    /* 0x53 */ u8 always0_AIPickoffRelated;
    /* 0x54 */ u8 pitcherAIPitchDownTheMiddleInd;
    /* 0x55 */ u8 aIBatterDifficulty;
    /* 0x56 */ u8 batterAIPotentialSwingTypeForCurrentPitch;
    /* 0x57 */ u8 batterAIBuntPossibility;
    /* 0x58 */ u8 batterAIBuntInd;
    /* 0x59 */ u8 _59;
    /* 0x5A */ u8 batterAIInd9PrincessStarHit;
    /* 0x5B */ u8 batterAISwingInd;
    /* 0x5C */ u8 batterAI_GuessedPitchLocZone; // unsure
    /* 0x5D */ u8 batterAIZPosition;            // unsure
    /* 0x5E */ u8 batterAIPitchGuessed;
    /* 0x5F */ u8 batterAISwingEarly1OrLate2;
    /* 0x60 */ u8 batterAIInd8_FrameBtwn10And16;
    /* 0x61 */ u8 batterAILeftRightInput; // unsure
    /* 0x62 */ u8 batterAIUpDownInput;    // unsure
    /* 0x63 */ u8 frameToStartSwing;
    /* 0x64 */ u8 someNotAISwingInd;                      // unsure
    /* 0x65 */ u8 aISwingDecisionRelated_noSwingOverride; // unsure
    /* 0x66 */ s8 batterAIABStrat;
    /* 0x67 */ u8 _67;
    /* 0x68 */ u8 aIBatterTrackingCode;
    /* 0x69 */ u8 aIDesiredFrameToSwing;
    /* 0x6A */ u8 batterAIInd10_relatedToBoxPosPrePitch;
    /* 0x6B */ u8 _6B;
    /* 0x6C */ u8 lastPitchFramesUntilPitchGetsToBatter;
    /* 0x6D */ u8 lastPitchType;
    /* 0x6E */ u8 lastPitchBallLocZone;
    /* 0x6F */ u8 lastPitchMoundZone;
    /* 0x70 */ u8 _70;
    /* 0x71 */ u8 starRelated[2]; // star related
    /* 0x73 */ u8 _73;
    /* 0x74 */ u8 _74;
    /* 0x75 */ u8 batterAIStealIndicator;
    /* 0x76 */ u8 batterAIStealingStartFrame;
    /* 0x77 */ u8 _77;
    /* 0x78 */ u8 _78;
    /* 0x79 */ u8 _79[3];
    // Per minigame player (fn_3_2DDB4 wandering AI):
    /* 0x7C */ VecXZ _7C[4]; // target position
    /* 0x9C */ s16 _9C[4];   // frames in the current state
    /* 0xA4 */ s16 _A4[4];
    /* 0xAC */ s16 _AC[4];   // heading
    /* 0xB4 */ u8 _B4[4];    // state
    /* 0xB8 */ u8 _B8[4];    // sub-state
} AIStruct; // size 0xBC

extern AIStruct g_AiLogic;

extern s16 CaptainStarSwingBattingVerticalAngleRanges[12][5][2];
extern s16 NonCaptainStarSwingBattingVerticalAngleRanges[3][5][2];
extern s16 HitVertTrajRanges[2][5][5][2];
extern s16 bB_launchAngles[2][3];
extern s16 lbl_3_data_54F8[2][2];
typedef struct {
    u8  bottom, low, mid, high, top;
} trajZones;

extern trajZones bODTrajProbabilities[5];
extern trajZones ToyFieldBattingVerticalAngleRanges[3][2][2][5];
extern trajZones BattingVerticalAngleRangeProbabilities[3][2][2][5];

typedef struct {
    u32 _0[4];
    u32 _10;
} trajOptions_s;

#include "game/replay_camera.h"

typedef struct {
    /* 0x000 */ s16 _0000;
    /* 0x002 */ u16 _0002;
    /* 0x004 */ s16 _0004[3];
    /* 0x00A */ s16 _000A[2];
    /* 0x00E */ s16 _000E;
    /* 0x010 */ s16 _0010;
    /* 0x012 */ u8 _0012;
    /* 0x013 */ u8 _0013;
    /* 0x014 */ u8 _0014;
    /* 0x015 */ u8 _0015;
    artificial_padding(0x15, 0x18, u8);
    /* 0x018 */ VecXYZ _0018;
    /* 0x024 */ VecXYZ _0024;
    /* 0x030 */ VecXYZ _030;
    /* 0x03C */ VecXYZ _03C[10];
    /* 0x0B4 */ VecXYZ _0B4;
    /* 0x0C0 */ f32 _0C0;
    /* 0x0C4 */ VecXYZ _0C4;
    /* 0x0D0 */ f32 _0D0;
    /* 0x0D4 */ f32 _0D4;
    /* 0x0D8 */ f32 _0D8;
    /* 0x0DC */ f32 _0DC;
    /* 0x0E0 */ s16 _0E0;
    /* 0x0E2 */ u8 _0E2;
    /* 0x0E3 */ u8 _0E3;
    /* 0x0E4 */ VecXYZ _0E4;
    /* 0x0F0 */ VecXYZ _0F0;
    /* 0x0FC */ VecXYZ _0FC;
    /* 0x108 */ VecXYZ _108;
    /* 0x114 */ f32 _114;
    /* 0x118 */ s16 _118;
    /* 0x11A */ s16 _11A;
#ifdef TARGET_PC
    union {
    struct {
    /* 0x11C */ u8 _11C;
    u8 _11D_[3];
    // On PC the fields below sit at their place in views[] (game/replay_camera.h),
    // whose pointers make it larger than on GameCube.
    struct {
        u8 _pc0[offsetof(lbl_3_common_bss_DE94_s2, animList)];
        /* views[0].animList */ void* _1B4; // minigame ARAM data (fn_3_106E50)
        u8 _pc1[offsetof(lbl_3_common_bss_DE94_s2, _0930) - offsetof(lbl_3_common_bss_DE94_s2, animList) - sizeof(void*)];
    /* 0xA50 */ int _A50;
    artificial_padding(0xa50, 0xa74, int);
    /* 0xA74 */ s16 _A74;
    /* 0xA76 */ s16 _A76;
    /* 0xA78 */ s16 _A78;
    /* 0xA7A */ s16 _A7A;
    /* 0xA7C */ s16 _A7C;
    /* 0xA7E */ s16 _A7E;
    /* 0xA80 */ s16 _A80;
    /* 0xA82 */ s16 _A82;
    /* 0xA84 */ s16 _A84[4];
    /* 0xA8C */ s16 _A8C[4];
    /* 0xA94 */ s16 _A94;
    /* 0xA96 */ s16 _A96;
    /* 0xA98 */ s16 _A98;
    /* 0xA9A */ s16 _A9A;
    /* 0xA9C */ s16 _A9C;
    /* 0xA9E */ s16 _A9E;
    /* 0xAA0 */ s16 _AA0;
    /* 0xAA2 */ s16 _AA2;
    /* 0xAA4 */ s16 _AA4;
    /* 0xAA6 */ s16 _AA6;
    /* 0xAA8 */ u16 _AA8; // fade-out active (fn_3_21C90)
    /* 0xAAA */ u16 _AAA; // fade-in active (fn_3_21DE4)
    /* 0xAAC */ u16 _AAC; // fade-out length in frames
    /* 0xAAE */ u16 _AAE; // fade-in length in frames
        u8 _pc2[offsetof(lbl_3_common_bss_DE94_s2, animData) - offsetof(lbl_3_common_bss_DE94_s2, _0988) - 8];
        /* views[0].animData */ void* _AB0; // 0x8000-byte heap buffer (fn_3_106DFC)
    /* 0xAB4 */ u8 _AB4;
    /* 0xAB5 */ u8 _AB5;
    /* 0xAB6 */ u8 _AB6;
    /* 0xAB7 */ u8 _AB7;
    /* 0xAB8 */ u8 _AB8;
    /* 0xAB9 */ u8 _AB9;
    /* 0xABA */ u8 _ABA;
    /* 0xABB */ u8 _ABB[4];
    /* 0xABF */ u8 _ABF;
    /* 0xAC0 */ u8 _AC0[4];
    /* 0xAC4 */ u8 _AC4;
    /* 0xAC5 */ u8 _AC5;
    /* 0xAC6 */ u8 _AC6;
    artificial_padding(0xac6, 0xac8, u8);
    /* 0xAC8 */ u8 _AC8;
    /* 0xAC9 */ u8 _AC9;
    /* 0xACA */ u8 _ACA;
    artificial_padding(0xaca, 0xad8, u8);
    /* 0xAD8 */ u8 _AD8;
        u8 _pc3[sizeof(lbl_3_common_bss_DE94_s2) - offsetof(lbl_3_common_bss_DE94_s2, _09B8) - 1];
    };
    struct {
        u8 _pc4[offsetof(lbl_3_common_bss_DE94_s2, animData)];
        /* views[1].animData */ void* _146C; // 0x8000-byte heap buffer (fn_3_106DFC)
        u8 _pc5[sizeof(lbl_3_common_bss_DE94_s2) - offsetof(lbl_3_common_bss_DE94_s2, animData) - sizeof(void*)];
    };
    u8 _pc6[2 * sizeof(lbl_3_common_bss_DE94_s2)];
    };
#else
    union {
    struct {
    /* 0x11C */ u8 _11C;
    artificial_padding(0x11C, 0x1b4, u8);
    /* 0x1B4 */ void* _1B4; // minigame ARAM data (fn_3_106E50)
    artificial_padding(0x1b4, 0xa50, void*);
    /* 0xA50 */ int _A50;
    artificial_padding(0xa50, 0xa74, int);
    /* 0xA74 */ s16 _A74;
    /* 0xA76 */ s16 _A76;
    /* 0xA78 */ s16 _A78;
    /* 0xA7A */ s16 _A7A;
    /* 0xA7C */ s16 _A7C;
    /* 0xA7E */ s16 _A7E;
    /* 0xA80 */ s16 _A80;
    /* 0xA82 */ s16 _A82;
    /* 0xA84 */ s16 _A84[4];
    /* 0xA8C */ s16 _A8C[4];
    /* 0xA94 */ s16 _A94;
    /* 0xA96 */ s16 _A96;
    /* 0xA98 */ s16 _A98;
    /* 0xA9A */ s16 _A9A;
    /* 0xA9C */ s16 _A9C;
    /* 0xA9E */ s16 _A9E;
    /* 0xAA0 */ s16 _AA0;
    /* 0xAA2 */ s16 _AA2;
    /* 0xAA4 */ s16 _AA4;
    /* 0xAA6 */ s16 _AA6;
    /* 0xAA8 */ u16 _AA8; // fade-out active (fn_3_21C90)
    /* 0xAAA */ u16 _AAA; // fade-in active (fn_3_21DE4)
    /* 0xAAC */ u16 _AAC; // fade-out length in frames
    /* 0xAAE */ u16 _AAE; // fade-in length in frames
    /* 0xAB0 */ void* _AB0; // 0x8000-byte heap buffer (fn_3_106DFC)
    /* 0xAB4 */ u8 _AB4;
    /* 0xAB5 */ u8 _AB5;
    /* 0xAB6 */ u8 _AB6;
    /* 0xAB7 */ u8 _AB7;
    /* 0xAB8 */ u8 _AB8;
    /* 0xAB9 */ u8 _AB9;
    /* 0xABA */ u8 _ABA;
    /* 0xABB */ u8 _ABB[4];
    /* 0xABF */ u8 _ABF;
    /* 0xAC0 */ u8 _AC0[4];
    /* 0xAC4 */ u8 _AC4;
    /* 0xAC5 */ u8 _AC5;
    /* 0xAC6 */ u8 _AC6;
    artificial_padding(0xac6, 0xac8, u8);
    /* 0xAC8 */ u8 _AC8;
    /* 0xAC9 */ u8 _AC9;
    /* 0xACA */ u8 _ACA;
    artificial_padding(0xaca, 0xad8, u8);
    /* 0xAD8 */ u8 _AD8;
    artificial_padding(0xad8, 0x146c, u8);
    /* 0x146C */ void* _146C; // 0x8000-byte heap buffer (fn_3_106DFC)
    artificial_padding(0x146c, 0x2810, void*);
    };
#endif
    struct {
        u8 _11C_[4];
        /* 0x120 */ lbl_3_common_bss_DE94_s2 views[4]; // replay camera views (game/replay_camera.h)
    };
    };
    /* 0x2810 */ s16 _2810;
    /* 0x2812 */ s16 _2812;
    /* 0x2814 */ s16 _2814;
    /* 0x2816 */ s16 _2816;
    /* 0x2818 */ u8 _2818;
    /* 0x2819 */ u8 _2819;
    /* 0x281A */ u8 _281A;
    /* 0x281C */ VecXYZ _281C;
    /* 0x2828 */ VecXYZ _2828;
    /* 0x2834 */ f32 _2834;
    /* 0x2838 */ s16 _2838;
    /* 0x283A */ s16 _283A;
    /* 0x283C */ s16 _283C;
    /* 0x283E */ u8 _283E;
    /* 0x283F */ u8 _283F;
    /* 0x2840 */ VecXYZ _2840;
    /* 0x284C */ VecXYZ _284C;
    /* 0x2858 */ VecXYZ _2858;
    artificial_padding(0x2860, 0x2870, f32);
    /* 0x2870 */ f32 _2870;
    /* 0x2874 */ f32 _2874;
    /* 0x2878 */ f32 _2878;
    /* 0x287C */ f32 _287C;
    /* 0x2880 */ f32 _2880;
    /* 0x2884 */ VecXYZ _2884;
    /* 0x2890 */ VecXYZ _2890;
    /* 0x289C */ s16 _289C;
    /* 0x289E */ s16 _289E;
    /* 0x28A0 */ s16 _28A0;
    artificial_padding(0x28A0, 0x28a6, s16);
    /* 0x28A6 */ u8 _28A6;
    /* 0x28A7 */ u8 _28A7;
    /* 0x28A8 */ u8 _28A8;
    /* 0x28A9 */ u8 _28A9; // 1: restart the view loop (fn_3_1CE90)
    /* 0x28AA */ u8 _28AA[0x28B0 - 0x28AA];
} inMemCamera; // size: 0x28B0 (g_Camera)

extern inMemCamera *g_pCamera;
extern inMemCamera g_Camera;

typedef struct {
    /* 0x00 */ int strikes;
    /* 0x04 */ int balls;
    /* 0x08 */ int outs;
    /* 0x0C */ int storedOuts;
    /* 0x10 */ int forcedOutToEndInningInd; // unsure
    /* 0x14 */ int allForcedRunnersReachedTheirBaseInd;
    /* 0x18 */ s16 runnerIndexForEachOutThisPitch[3];
    /* 0x1E */ s16 _1E;
    /* 0x20 */ u8 GameControls_StrikeBallBitVector;
    /* 0x21 */ u8 stateRelated;
} inMemStrikes; // size: 0x24

extern inMemStrikes g_Strikes;

// One controller's input as recorded for the replay (copied from InputStruct).
typedef struct ReplayInput {
    /*0x0*/ s16 controlStickAngle;
    /*0x2*/ u16 buttonInput;    // without the 0x1000 (START) bit
    /*0x4*/ u16 newButtonInput; // without the 0x1000 (START) bit
    /*0x6*/ s8 right_left;
    /*0x7*/ s8 up_down;
} ReplayInput; // size: 0x8

// One recorded frame: both controllers (g_Stats.controller[0/1]).
typedef struct ReplayFrame {
    /*0x0*/ ReplayInput input[2];
} ReplayFrame; // size: 0x10

#define REPLAY_MAX_FRAMES 1200

extern ReplayFrame g_ReplayLogic[REPLAY_MAX_FRAMES];

// Replay state, plus a snapshot of the game state taken when recording starts.
typedef struct {
    /* 0x0000 */ VecXZ landingSpotLocation;
    /* 0x0008 */ VecXZ ballPickedUpCaught;
    /* 0x0010 */ VecXYZ deadballLastLoc;
    /* 0x001C */ s16 hitVerticalAngle;
    /* 0x001E */ s16 hitHorizontalAngle;
    /* 0x0020 */ s16 hitHorizontalPower;
    /* 0x0022 */ s16 _22;
    /* 0x0024 */ s32 playFrameCounter;
    /* 0x0028 */ s16 endFrame; // last recorded frame
    /* 0x002A */ s16 _2A;      // fielding team's score
    /* 0x002C */ s16 _2C;
    /* 0x002E */ s16 _2E;
    /* 0x0030 */ s16 _30; // batting team's score
    /* 0x0032 */ s16 _32;
    /* 0x0034 */ s16 _34;
    /* 0x0036 */ u8 replayInd; // playing back
    /* 0x0037 */ u8 recording;
    /* 0x0038 */ u8 _38;
    /* 0x0039 */ u8 _39;
    /* 0x003A */ u8 _3A;
    /* 0x003B */ u8 _3B;
    /* 0x003C */ u8 _3C;
    /* 0x003D */ u8 _3D;
    /* 0x003E */ u8 _3E;
    /* 0x003F */ u8 controller[2];
    /* 0x0041 */ u8 _41[3];
    // Snapshot of the game state (fn_3_7CF88).
    /* 0x0044 */ u8 gameLogic[0x158];
    /* 0x019C */ u8 strikes[0x24];
    /* 0x01C0 */ u8 scores[0xC8];
    /* 0x0288 */ u8 ball[0x1BF8];
    /* 0x1E80 */ u8 pitcher[0x178];
    /* 0x1FF8 */ u8 batter[0xB0];
    /* 0x20A8 */ u8 aiLogic[0xBC];
    /* 0x2164 */ u8 fieldingLogic[0x150];
    /* 0x22B4 */ u8 runningLogic[0x20];
    /* 0x22D4 */ u8 fielders[0x15A8];
    /* 0x387C */ u8 runners[0x550];
    /* 0x3DCC */ u8 bss_32234[6];
    /* 0x3DD2 */ u8 bss_32230[4];
    /* 0x3DD6 */ u8 bss_32220[0xE];
    /* 0x3DE4 */ u8 throwing[0x14];
    /* 0x3DF8 */ u8 animation[0x2F4];
    /* 0x40EC */ u8 bss_321A0[0x80];
    /* 0x416C */ u8 lbl_803537E4[0x2AC];
    /* 0x4418 */ u8 lbl_803535C8[0x21C];
} g_Stats_s; // size: 0x4634

// 0x8088a7e4
extern g_Stats_s g_Stats;

#include "game/fielding_types.h" // FieldingBoost, FieldingPadRec

typedef struct {
    /* 0x000 */ FieldingBoost boost[4];
    /* 0x070 */ FieldingBoost* curBoost; // one of boost[]
    union {
        struct {
            /* 0x074 */ FieldingPadRec padRec[4];
            /* 0x08C */ FieldingPadRec* curPadRec; // one of padRec[]
        };
        struct {
            u8 _074[3];
            /* 0x077 */ struct {
                u8 _0;  // padRec[i]._3
                u8 _1;  // padRec[i]._4; set when RandomInt_Game(100) rolls under the fielder's chance (fn_3_1DEB8)
                u8 _2[4];
            } _077[4]; // per minigame fielder (older byte view of padRec)
        };
    };
    /* 0x090 */ VecXYZ _090; // target position
    u8 _09C[0xAE - 0x9C];
    /* 0x0AE */ s16 _0AE;
    /* 0x0B0 */ s16 _0B0; // fielder index (g_Fielders), < 0 if none
    /* 0x0B2 */ s16 _0B2;
    /* 0x0B4 */ s16 _0B4;
    /* 0x0B6 */ s16 _0B6;
    /* 0x0B8 */ s16 _0B8;
    /* 0x0BA */ s16 _0BA;
    /* 0x0BC */ s16 _0BC;
    /* 0x0BE */ s16 _0BE; // fielder index
    /* 0x0C0 */ s16 _0C0;
    /* 0x0C2 */ s16 _0C2;
    /* 0x0C4 */ s16 _0C4; // base to throw to
    /* 0x0C6 */ s16 _0C6;
    /* 0x0C8 */ s16 _0C8;
    /* 0x0CA */ s16 _0CA;
    /* 0x0CC */ s16 _0CC; // base
    /* 0x0CE */ s16 _0CE;
    /* 0x0D0 */ s16 _0D0[4]; // per base: fielder covering it
    /* 0x0D8 */ s16 _0D8;
    /* 0x0DA */ s16 _0DA;
    /* 0x0DC */ s16 _0DC;
    /* 0x0DE */ s16 _0DE; // runner index
    /* 0x0E0 */ s16 _0E0; // runner index
    /* 0x0E2 */ s16 _0E2;
    /* 0x0E4 */ s16 _0E4;
    /* 0x0E6 */ s16 _0E6;
    /* 0x0E8 */ s16 _0E8; // runner index
    /* 0x0EA */ s16 _0EA; // fielder index (g_Fielders)
    /* 0x0EC */ s16 _0EC;
    /* 0x0EE */ s16 _0EE;
    /* 0x0F0 */ s16 _0F0;
    /* 0x0F2 */ s16 _0F2;
    /* 0x0F4 */ s16 _0F4;
    /* 0x0F6 */ s16 _0F6;
    /* 0x0F8 */ u8 _0F8[9]; // per fielder
    /* 0x101 */ u8 _101[4]; // per base
    /* 0x105 */ u8 playerAtMoundCutoffLocation;
    /* 0x106 */ u8 throwSpeedType;
    /* 0x107 */ u8 _107;
    /* 0x108 */ u8 _108;
    /* 0x109 */ u8 _109;
    /* 0x10A */ u8 _10A;
    /* 0x10B */ u8 _10B;
    /* 0x10C */ u8 _10C;
    /* 0x10D */ u8 _10D;
    /* 0x10E */ u8 _10E;
    /* 0x10F */ u8 _10F;
    /* 0x110 */ u8 _110;
    /* 0x111 */ u8 _111;
    /* 0x112 */ u8 _112;
    /* 0x113 */ u8 _113;
    /* 0x114 */ u8 _114;
    /* 0x115 */ u8 _115;
    /* 0x116 */ u8 _116;
    /* 0x117 */ u8 _117;
    /* 0x118 */ u8 _118;
    /* 0x119 */ u8 _119;
    /* 0x11A */ u8 _11A;
    /* 0x11B */ u8 _11B;
    /* 0x11C */ u8 _11C;
    /* 0x11D */ u8 _11D;
    /* 0x11E */ u8 _11E;
    /* 0x11F */ u8 _11F;
    /* 0x120 */ u8 _120;
    /* 0x121 */ s8 _121;
    /* 0x122 */ u8 _122;
    /* 0x123 */ u8 _123;
    /* 0x124 */ u8 _124;
    /* 0x125 */ s8 _125; // base
    /* 0x126 */ s8 _126; // -1: none
    /* 0x127 */ s8 _127;
    /* 0x128 */ u8 _128;
    /* 0x129 */ u8 _129;
    /* 0x12A */ u8 _12A;
    /* 0x12B */ u8 _12B;
    /* 0x12C */ u8 _12C;
    /* 0x12D */ u8 _12D;
    /* 0x12E */ u8 _12E;
    /* 0x12F */ u8 _12F;
    /* 0x130 */ u8 _130;
    /* 0x131 */ u8 _131;
    /* 0x132 */ u8 _132;
    /* 0x133 */ u8 _133;
    /* 0x134 */ u8 _134;
    /* 0x135 */ u8 _135;
    /* 0x136 */ u8 _136;
    /* 0x137 */ u8 _137;
    /* 0x138 */ u8 _138;
    /* 0x139 */ u8 _139;
    /* 0x13A */ u8 _13A;
    /* 0x13B */ u8 _13B;
    /* 0x13C */ u8 _13C;
    /* 0x13D */ u8 _13D;
    /* 0x13E */ u8 _13E;
    /* 0x13F */ u8 _13F;
    /* 0x140 */ u8 _140;
    /* 0x141 */ u8 _141;
    /* 0x142 */ u8 _142;
    /* 0x143 */ u8 _143;
    /* 0x144 */ u8 _144;
    /* 0x145 */ u8 _145;
    /* 0x146 */ u8 _146;
    /* 0x147 */ u8 _147;
    union {
        struct {
            /* 0x148 */ u8 _148;
            /* 0x149 */ u8 _149;
            /* 0x14A */ u8 _14A;
            /* 0x14B */ u8 _14B;
            /* 0x14C */ u8 _14C;
            /* 0x14D */ u8 _14D;
        };
        /* 0x148 */ u16 padButtons[3]; // controller held/pressed/repeat copied in fn_3_4B7E8
    };
    /* 0x14E */ u8 _14E;
    /* 0x14F */ u8 _14F;
} g_FieldingLogic_s; // size 0x150

extern g_FieldingLogic_s g_FieldingLogic;

typedef struct {
    /* 0x0 */ s16 rosterIdx;
    /* 0x2 */ s16 score;
} MvpCandidate;

typedef struct {
    /* 0x00 */ s16 _0;
    /* 0x02 */ s16 _2;
    /* 0x04 */ s16 _4;
    /* 0x06 */ s16 _6[5]; // history of _0 (fn_3_9DB5C)
    /* 0x10 */ struct {
        s8 fielder; // fielder holding the ball (-1: none)
        s8 outs;    // outs recorded on the play so far
        s8 base;    // base the fielder was covering
    } plays[5];
    /* 0x1F */ s8 lastFielder;
    /* 0x20 */ s16 _20;
    /* 0x22 */ s8 _22; // -1: undecided (fn_3_7976C)
    /* 0x23 */ s8 _23;
    /* 0x24 */ u8 _24;
    /* 0x25 */ s8 _25; // double-play tracking (fn_3_79A00)
    /* 0x26 */ s8 _26; // runs scored on the last dead ball
    /* 0x27 */ u8 baseOccupied[4]; // [0] batter, [1..3] runner on that base
    /* 0x2B */ u8 pitchCountLog[7]; // balls + strikes * 16 per pitch of the at-bat
    /* 0x32 */ s16 _32;
    /* 0x34 */ s16 _34; // pitches by the current pitcher
    /* 0x36 */ u8 _36[5];
    /* 0x3B */ u8 _3B;
    /* 0x3C */ u8 _3C;
    /* 0x3D */ u8 _3D;
    /* 0x3E */ u8 _3E[5];
    /* 0x43 */ u8 _43;
    /* 0x44 */ s16 _44[2]; // per team: times through the batting order
    /* 0x48 */ s16 _48[2]; // per team
    /* 0x4C */ s16 _4C[2]; // per team
    /* 0x50 */ struct {
        s16 pitcher;
        s16 _2;
    } _50[2]; // per team
    /* 0x58 */ MvpCandidate mvp[2]; // per team (fn_3_759BC)
    /* 0x60 */ u8 _60;
    /* 0x61 */ u8 _61;
    /* 0x62 */ u8 _62;
    /* 0x63 */ u8 _63[2]; // per team
    /* 0x65 */ u8 _65[2]; // per team
    /* 0x67 */ u8 _67[2]; // per team
    /* 0x69 */ u8 _69;
    /* 0x6A */ u8 _6A[0x13]; // per team: [team * 10 + i], i < 9
    /* 0x7D */ u8 _7D;
    /* 0x7E */ u8 _7E;
    /* 0x7F */ u8 _7F;
    /* 0x80 */ u8 _80;
    /* 0x81 */ u8 _81;
    /* 0x82 */ u8 _82;
    /* 0x83 */ u8 _83;
    /* 0x84 */ u8 _84;
    /* 0x85 */ u8 _85;
    /* 0x86 */ u8 _86;
    /* 0x87 */ u8 _87;
    /* 0x88 */ u8 _88;
    /* 0x89 */ u8 _89;
    /* 0x8A */ u8 _8A;
    /* 0x8B */ u8 _8B;
} lbl_3_common_bss_32A94_s; // size: 0x8C

extern lbl_3_common_bss_32A94_s lbl_3_common_bss_32A94;

// g_Scores layout (0xC8 bytes); declare `extern GameScores g_Scores;` in the unit header.
typedef struct GameScoresTeam {
    /* 0x00 */ s16 runs[19]; // [0] total, [1..] per inning
} GameScoresTeam; // size: 0x26

typedef struct GameScores {
    /* 0x00 */ s32 inning;
    /* 0x04 */ GameScoresTeam team[2];
    /* 0x50 */ GameScoresTeam hits[2]; // same layout as team[]: [0] total, [1..] per inning
    /* 0x9C */ s16 _9C;
    /* 0x9E */ s16 _9E;
    /* 0xA0 */ s16 _A0;
    /* 0xA2 */ s16 _A2;
    /* 0xA4 */ s16 _A4; // 0: away won, 1: home won, else tie
    /* 0xA6 */ s16 _A6;
    /* 0xA8 */ u8 _A8[0xAA - 0xA8];
    /* 0xAA */ u8 maxInnings;
    /* 0xAB */ u8 _AB;
    /* 0xAC */ u8 _AC;
    /* 0xAD */ u8 _AD;
    /* 0xAE */ u8 _AE[0xC2 - 0xAE];
    /* 0xC2 */ u8 _C2;
    /*0xC3*/ u8 _C3[0xC5 - 0xC3];
    /*0xC5*/ u8 _C5;
    /* 0xC6 */ u8 _C6;
    /* 0xC7 */ u8 _C7;
} GameScores; // size: 0xC8

// lbl_3_common_bss_DE94_s2 (replay camera view): game/replay_camera.h

typedef struct {
    lbl_3_common_bss_DE94_s2* _0000;
    u8 _0004[0x2AF4 - 0x4];
} lbl_3_common_bss_DE94_s; // size: 0x2AF4

extern lbl_3_common_bss_DE94_s lbl_3_common_bss_DE94;

extern trajOptions_s hitTrajOptions[]; 
extern s16 toyFieldHitVertTraj[2][5][5][2];
extern s16 bODHitVertTraj[5][5][2];
extern s16 HitVertTrajRanges[2][5][5][2];

extern void fn_3_6C854(int, int);
extern u32 playSoundEffect(s32);
extern void fn_3_5ED98(void);
extern int RandomIndexFromWeights(u8* weights, int count);
extern void fn_3_FBDAC(int);
extern void fn_3_FBE24(void);
extern BOOL checkFieldingStat(int, int, E(int, FIELDING_ABILITY));

#include "game/BurstParams.h"

#endif // !__UNKNOWN_HOMES_H_
