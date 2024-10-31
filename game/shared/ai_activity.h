//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef AI_ACTIVITY_H
#define AI_ACTIVITY_H
#ifdef _WIN32
#pragma once
#endif

#define ACTIVITY_NOT_AVAILABLE                -1

typedef enum
{
        ACT_INVALID = -1,                        // So we have something more succint to check for than '-1'
        ACT_RESET = 0,                                // Set m_Activity to this invalid value to force a reset to m_IdealActivity
        ACT_IDLE,
        ACT_TRANSITION,
        ACT_COVER,                                        // FIXME: obsolete? redundant with ACT_COVER_LOW?
        ACT_COVER_MED,                                // FIXME: unsupported?
        ACT_COVER_LOW,                                // FIXME: rename ACT_IDLE_CROUCH?
        ACT_WALK,
        ACT_WALK_AIM,
        ACT_WALK_CROUCH,
        ACT_WALK_CROUCH_AIM,
        ACT_RUN,
        ACT_RUN_AIM,
        ACT_RUN_CROUCH,
        ACT_RUN_CROUCH_AIM,
        ACT_RUN_PROTECTED,
        ACT_SCRIPT_CUSTOM_MOVE,
        ACT_RANGE_ATTACK1,
        ACT_RANGE_ATTACK2,
        ACT_RANGE_ATTACK1_LOW,                // FIXME: not used yet, crouched versions of the range attack
        ACT_RANGE_ATTACK2_LOW,                // FIXME: not used yet, crouched versions of the range attack
        ACT_DIESIMPLE,
        ACT_DIEBACKWARD,
        ACT_DIEFORWARD,
        ACT_DIEVIOLENT,
        ACT_DIERAGDOLL,
        ACT_FLY,                                // Fly (and flap if appropriate)
        ACT_HOVER,
        ACT_GLIDE,
        ACT_SWIM,
        ACT_JUMP,
        ACT_HOP,                                // vertical jump
        ACT_LEAP,                                // long forward jump
        ACT_LAND,
        ACT_CLIMB_UP,
        ACT_CLIMB_DOWN,
        ACT_CLIMB_DISMOUNT,
        ACT_SHIPLADDER_UP,
        ACT_SHIPLADDER_DOWN,
        ACT_STRAFE_LEFT,
        ACT_STRAFE_RIGHT,
        ACT_ROLL_LEFT,                        // tuck and roll, left
        ACT_ROLL_RIGHT,                        // tuck and roll, right
        ACT_TURN_LEFT,                        // turn quickly left (stationary)
        ACT_TURN_RIGHT,                        // turn quickly right (stationary)
        ACT_CROUCH,                                // FIXME: obsolete? only used be soldier (the act of crouching down from a standing position)
        ACT_CROUCHIDLE,                        // FIXME: obsolete? only used be soldier (holding body in crouched position (loops))
        ACT_STAND,                                // FIXME: obsolete? should be transition (the act of standing from a crouched position)
        ACT_USE,
        ACT_SIGNAL1,
        ACT_SIGNAL2,
        ACT_SIGNAL3,

        ACT_SIGNAL_ADVANCE,                // Squad handsignals, specific.
        ACT_SIGNAL_FORWARD,
        ACT_SIGNAL_GROUP,
        ACT_SIGNAL_HALT,
        ACT_SIGNAL_LEFT,
        ACT_SIGNAL_RIGHT,
        ACT_SIGNAL_TAKECOVER,

        ACT_LOOKBACK_RIGHT,                // look back over shoulder without turning around.
        ACT_LOOKBACK_LEFT,
        ACT_COWER,                                // FIXME: unused, should be more extreme version of crouching
        ACT_SMALL_FLINCH,                // FIXME: needed? shouldn't flinching be down with overlays?
        ACT_BIG_FLINCH,                
        ACT_MELEE_ATTACK1,
        ACT_MELEE_ATTACK2,
        ACT_RELOAD,
        ACT_RELOAD_START,
        ACT_RELOAD_FINISH,
        ACT_RELOAD_LOW,
        ACT_ARM,                                // pull out gun, for instance
        ACT_DISARM,                                // reholster gun
        ACT_DROP_WEAPON,
        ACT_DROP_WEAPON_SHOTGUN,
        ACT_PICKUP_GROUND,                // pick up something in front of you on the ground
        ACT_PICKUP_RACK,                // pick up something from a rack or shelf in front of you.
        ACT_IDLE_ANGRY,                        // FIXME: being used as an combat ready idle?  alternate idle animation in which the monster is clearly agitated. (loop)

        ACT_IDLE_RELAXED,
        ACT_IDLE_STIMULATED,
        ACT_IDLE_AGITATED,
        ACT_IDLE_STEALTH,
        ACT_IDLE_HURT,

        ACT_WALK_RELAXED,
        ACT_WALK_STIMULATED,
        ACT_WALK_AGITATED,
        ACT_WALK_STEALTH,

        ACT_RUN_RELAXED,
        ACT_RUN_STIMULATED,
        ACT_RUN_AGITATED,
        ACT_RUN_STEALTH,

        ACT_IDLE_AIM_RELAXED,
        ACT_IDLE_AIM_STIMULATED,
        ACT_IDLE_AIM_AGITATED,
        ACT_IDLE_AIM_STEALTH,

        ACT_WALK_AIM_RELAXED,
        ACT_WALK_AIM_STIMULATED,
        ACT_WALK_AIM_AGITATED,
        ACT_WALK_AIM_STEALTH,

        ACT_RUN_AIM_RELAXED,
        ACT_RUN_AIM_STIMULATED,
        ACT_RUN_AIM_AGITATED,
        ACT_RUN_AIM_STEALTH,

        ACT_CROUCHIDLE_STIMULATED,
        ACT_CROUCHIDLE_AIM_STIMULATED,
        ACT_CROUCHIDLE_AGITATED,

        ACT_WALK_HURT,                        // limp  (loop)
        ACT_RUN_HURT,                        // limp  (loop)
        ACT_SPECIAL_ATTACK1,        // very monster specific special attacks.
        ACT_SPECIAL_ATTACK2,        
        ACT_COMBAT_IDLE,                // FIXME: unused?  agitated idle.
        ACT_WALK_SCARED,
        ACT_RUN_SCARED,
        ACT_VICTORY_DANCE,                // killed a player, do a victory dance.
        ACT_DIE_HEADSHOT,                // die, hit in head. 
        ACT_DIE_CHESTSHOT,                // die, hit in chest
        ACT_DIE_GUTSHOT,                // die, hit in gut
        ACT_DIE_BACKSHOT,                // die, hit in back
        ACT_FLINCH_HEAD,
        ACT_FLINCH_CHEST,
        ACT_FLINCH_STOMACH,
        ACT_FLINCH_LEFTARM,
        ACT_FLINCH_RIGHTARM,
        ACT_FLINCH_LEFTLEG,
        ACT_FLINCH_RIGHTLEG,
        ACT_FLINCH_PHYSICS,

        ACT_IDLE_ON_FIRE,                // ON FIRE animations
        ACT_WALK_ON_FIRE,
        ACT_RUN_ON_FIRE,                

        ACT_RAPPEL_LOOP,                // Rappel down a rope!

        ACT_180_LEFT,                        // 180 degree left turn
        ACT_180_RIGHT,

        ACT_90_LEFT,                        // 90 degree turns
        ACT_90_RIGHT,

        ACT_STEP_LEFT,                        // Single steps
        ACT_STEP_RIGHT,
        ACT_STEP_BACK,
        ACT_STEP_FORE,

        ACT_GESTURE_RANGE_ATTACK1,
        ACT_GESTURE_RANGE_ATTACK2,
        ACT_GESTURE_MELEE_ATTACK1,
        ACT_GESTURE_MELEE_ATTACK2,
        ACT_GESTURE_RANGE_ATTACK1_LOW,        // FIXME: not used yet, crouched versions of the range attack
        ACT_GESTURE_RANGE_ATTACK2_LOW,        // FIXME: not used yet, crouched versions of the range attack

        ACT_MELEE_ATTACK_SWING_GESTURE,

        ACT_GESTURE_SMALL_FLINCH,
        ACT_GESTURE_BIG_FLINCH,
        ACT_GESTURE_FLINCH_BLAST,                        // Startled by an explosion
        ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
        ACT_GESTURE_FLINCH_BLAST_DAMAGED,        // Damaged by an explosion
        ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
        ACT_GESTURE_FLINCH_HEAD,
        ACT_GESTURE_FLINCH_CHEST,
        ACT_GESTURE_FLINCH_STOMACH,
        ACT_GESTURE_FLINCH_LEFTARM,
        ACT_GESTURE_FLINCH_RIGHTARM,
        ACT_GESTURE_FLINCH_LEFTLEG,
        ACT_GESTURE_FLINCH_RIGHTLEG,

        ACT_GESTURE_TURN_LEFT,
        ACT_GESTURE_TURN_RIGHT,
        ACT_GESTURE_TURN_LEFT45,
        ACT_GESTURE_TURN_RIGHT45,
        ACT_GESTURE_TURN_LEFT90,
        ACT_GESTURE_TURN_RIGHT90,
        ACT_GESTURE_TURN_LEFT45_FLAT,
        ACT_GESTURE_TURN_RIGHT45_FLAT,
        ACT_GESTURE_TURN_LEFT90_FLAT,
        ACT_GESTURE_TURN_RIGHT90_FLAT,

        // HALF-LIFE 1 compatability stuff goes here. Temporary!
        ACT_BARNACLE_HIT,                // barnacle tongue hits a monster
        ACT_BARNACLE_PULL,                // barnacle is lifting the monster ( loop )
        ACT_BARNACLE_CHOMP,                // barnacle latches on to the monster
        ACT_BARNACLE_CHEW,                // barnacle is holding the monster in its mouth ( loop )

        // Sometimes, you just want to set an NPC's sequence to a sequence that doesn't actually
        // have an activity. The AI will reset the NPC's sequence to whatever its IDEAL activity
        // is, though. So if you set ideal activity to DO_NOT_DISTURB, the AI will not interfere
        // with the NPC's current sequence. (SJB)
        ACT_DO_NOT_DISTURB,

        // viewmodel (weapon) activities
        // FIXME: move these to the specific viewmodels, no need to make global
        ACT_VM_DRAW,
        ACT_VM_HOLSTER,
        ACT_VM_IDLE,
        ACT_VM_FIDGET,
        ACT_VM_PULLBACK,
        ACT_VM_PULLBACK_HIGH,
        ACT_VM_PULLBACK_LOW,
        ACT_VM_THROW,
        ACT_VM_PULLPIN,
        ACT_VM_PRIMARYATTACK,                // fire
        ACT_VM_SECONDARYATTACK,                // alt. fire
        ACT_VM_RELOAD,                        
        ACT_VM_RELOAD_START,                        
        ACT_VM_RELOAD_FINISH,                        
        ACT_VM_DRYFIRE,                                // fire with no ammo loaded.
        ACT_VM_HITLEFT,                                // bludgeon, swing to left - hit (primary attk)
        ACT_VM_HITLEFT2,                        // bludgeon, swing to left - hit (secondary attk)
        ACT_VM_HITRIGHT,                        // bludgeon, swing to right - hit (primary attk)
        ACT_VM_HITRIGHT2,                        // bludgeon, swing to right - hit (secondary attk)
        ACT_VM_HITCENTER,                        // bludgeon, swing center - hit (primary attk)
        ACT_VM_HITCENTER2,                        // bludgeon, swing center - hit (secondary attk)
        ACT_VM_MISSLEFT,                        // bludgeon, swing to left - miss (primary attk)
        ACT_VM_MISSLEFT2,                        // bludgeon, swing to left - miss (secondary attk)
        ACT_VM_MISSRIGHT,                        // bludgeon, swing to right - miss (primary attk)
        ACT_VM_MISSRIGHT2,                        // bludgeon, swing to right - miss (secondary attk)
        ACT_VM_MISSCENTER,                        // bludgeon, swing center - miss (primary attk)
        ACT_VM_MISSCENTER2,                        // bludgeon, swing center - miss (secondary attk)
        ACT_VM_HAULBACK,                        // bludgeon, haul the weapon back for a hard strike (secondary attk)
        ACT_VM_SWINGHARD,                        // bludgeon, release the hard strike (secondary attk)
        ACT_VM_SWINGMISS,
        ACT_VM_SWINGHIT,
        ACT_VM_IDLE_TO_LOWERED,
        ACT_VM_IDLE_LOWERED,
        ACT_VM_LOWERED_TO_IDLE,
        ACT_VM_RECOIL1,
        ACT_VM_RECOIL2,
        ACT_VM_RECOIL3,
        ACT_VM_PICKUP,
        ACT_VM_RELEASE,

        ACT_VM_ATTACH_SILENCER,
        ACT_VM_DETACH_SILENCER,

        // TF2 Scout Pack
        ACT_VM_DRAW_SPECIAL,
        ACT_VM_HOLSTER_SPECIAL,
        ACT_VM_IDLE_SPECIAL,
        ACT_VM_PULLBACK_SPECIAL,
        ACT_VM_PRIMARYATTACK_SPECIAL,
        ACT_VM_SECONDARYATTACK_SPECIAL,
        ACT_VM_HITCENTER_SPECIAL,
        ACT_VM_SWINGHARD_SPECIAL,
        ACT_VM_IDLE_TO_LOWERED_SPECIAL,
        ACT_VM_IDLE_LOWERED_SPECIAL,
        ACT_VM_LOWERED_TO_IDLE_SPECIAL,

        ACT_FISTS_VM_HITLEFT,
        ACT_FISTS_VM_HITRIGHT,
        ACT_FISTS_VM_SWINGHARD,
        ACT_FISTS_VM_IDLE,
        ACT_FISTS_VM_DRAW,

//===========================
// HL2 Specific Activities
//===========================
        // SLAM        Specialty Activities
        ACT_SLAM_STICKWALL_IDLE,
        ACT_SLAM_STICKWALL_ND_IDLE,
        ACT_SLAM_STICKWALL_ATTACH,
        ACT_SLAM_STICKWALL_ATTACH2,
        ACT_SLAM_STICKWALL_ND_ATTACH,
        ACT_SLAM_STICKWALL_ND_ATTACH2,
        ACT_SLAM_STICKWALL_DETONATE,
        ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
        ACT_SLAM_STICKWALL_DRAW, 
        ACT_SLAM_STICKWALL_ND_DRAW, 
        ACT_SLAM_STICKWALL_TO_THROW, 
        ACT_SLAM_STICKWALL_TO_THROW_ND, 
        ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
        ACT_SLAM_THROW_IDLE,
        ACT_SLAM_THROW_ND_IDLE,
        ACT_SLAM_THROW_THROW,
        ACT_SLAM_THROW_THROW2,
        ACT_SLAM_THROW_THROW_ND,
        ACT_SLAM_THROW_THROW_ND2,
        ACT_SLAM_THROW_DRAW, 
        ACT_SLAM_THROW_ND_DRAW,
        ACT_SLAM_THROW_TO_STICKWALL, 
        ACT_SLAM_THROW_TO_STICKWALL_ND, 
          ACT_SLAM_THROW_DETONATE,
          ACT_SLAM_THROW_DETONATOR_HOLSTER,
        ACT_SLAM_THROW_TO_TRIPMINE_ND,
        ACT_SLAM_TRIPMINE_IDLE,
        ACT_SLAM_TRIPMINE_DRAW, 
        ACT_SLAM_TRIPMINE_ATTACH, 
        ACT_SLAM_TRIPMINE_ATTACH2, 
        ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
        ACT_SLAM_TRIPMINE_TO_THROW_ND,
        ACT_SLAM_DETONATOR_IDLE, 
        ACT_SLAM_DETONATOR_DRAW, 
        ACT_SLAM_DETONATOR_DETONATE,
        ACT_SLAM_DETONATOR_HOLSTER,
        ACT_SLAM_DETONATOR_STICKWALL_DRAW,
        ACT_SLAM_DETONATOR_THROW_DRAW,

        // Shotgun Specialty Activities
        ACT_SHOTGUN_RELOAD_START,
        ACT_SHOTGUN_RELOAD_FINISH,
        ACT_SHOTGUN_PUMP,

        // SMG2 special activities
        ACT_SMG2_IDLE2,
        ACT_SMG2_FIRE2,
        ACT_SMG2_DRAW2,
        ACT_SMG2_RELOAD2,
        ACT_SMG2_DRYFIRE2,
        ACT_SMG2_TOAUTO,
        ACT_SMG2_TOBURST,

        // Physcannon special activities
        ACT_PHYSCANNON_UPGRADE,

        // weapon override activities
        ACT_RANGE_ATTACK_AR1,
        ACT_RANGE_ATTACK_AR2,
        ACT_RANGE_ATTACK_AR2_LOW,
        ACT_RANGE_ATTACK_AR2_GRENADE,
        ACT_RANGE_ATTACK_HMG1,
        ACT_RANGE_ATTACK_ML,
        ACT_RANGE_ATTACK_SMG1,
        ACT_RANGE_ATTACK_SMG1_LOW,
        ACT_RANGE_ATTACK_SMG2,
        ACT_RANGE_ATTACK_SHOTGUN,
        ACT_RANGE_ATTACK_SHOTGUN_LOW,
        ACT_RANGE_ATTACK_PISTOL,
        ACT_RANGE_ATTACK_PISTOL_LOW,
        ACT_RANGE_ATTACK_SLAM,
        ACT_RANGE_ATTACK_TRIPWIRE,
        ACT_RANGE_ATTACK_THROW,
        ACT_RANGE_ATTACK_SNIPER_RIFLE,
        ACT_RANGE_ATTACK_RPG,
        ACT_MELEE_ATTACK_SWING,

        ACT_RANGE_AIM_LOW,
        ACT_RANGE_AIM_SMG1_LOW,
        ACT_RANGE_AIM_PISTOL_LOW,
        ACT_RANGE_AIM_AR2_LOW,

        ACT_COVER_PISTOL_LOW,
        ACT_COVER_SMG1_LOW,

        // weapon override activities
        ACT_GESTURE_RANGE_ATTACK_AR1,
        ACT_GESTURE_RANGE_ATTACK_AR2,
        ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
        ACT_GESTURE_RANGE_ATTACK_HMG1,
        ACT_GESTURE_RANGE_ATTACK_ML,
        ACT_GESTURE_RANGE_ATTACK_SMG1,
        ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
        ACT_GESTURE_RANGE_ATTACK_SMG2,
        ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
        ACT_GESTURE_RANGE_ATTACK_PISTOL,
        ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
        ACT_GESTURE_RANGE_ATTACK_SLAM,
        ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
        ACT_GESTURE_RANGE_ATTACK_THROW,
        ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
        ACT_GESTURE_MELEE_ATTACK_SWING,

        ACT_IDLE_RIFLE,
        ACT_IDLE_SMG1,
        ACT_IDLE_ANGRY_SMG1,
        ACT_IDLE_PISTOL,
        ACT_IDLE_ANGRY_PISTOL,
        ACT_IDLE_ANGRY_SHOTGUN,
        ACT_IDLE_STEALTH_PISTOL,

        ACT_IDLE_PACKAGE,
        ACT_WALK_PACKAGE,
        ACT_IDLE_SUITCASE,
        ACT_WALK_SUITCASE,

        ACT_IDLE_SMG1_RELAXED,
        ACT_IDLE_SMG1_STIMULATED,
        ACT_WALK_RIFLE_RELAXED,
        ACT_RUN_RIFLE_RELAXED,
        ACT_WALK_RIFLE_STIMULATED,
        ACT_RUN_RIFLE_STIMULATED,

        ACT_IDLE_AIM_RIFLE_STIMULATED,
        ACT_WALK_AIM_RIFLE_STIMULATED,
        ACT_RUN_AIM_RIFLE_STIMULATED,

        ACT_IDLE_SHOTGUN_RELAXED,
        ACT_IDLE_SHOTGUN_STIMULATED,
        ACT_IDLE_SHOTGUN_AGITATED,

        // Policing activities
        ACT_WALK_ANGRY,
        ACT_POLICE_HARASS1,
        ACT_POLICE_HARASS2,

        // Manned guns
        ACT_IDLE_MANNEDGUN,

        // Melee weapon
        ACT_IDLE_MELEE,
        ACT_IDLE_ANGRY_MELEE,

        // RPG activities
        ACT_IDLE_RPG_RELAXED,
        ACT_IDLE_RPG, 
        ACT_IDLE_ANGRY_RPG,
        ACT_COVER_LOW_RPG, 
        ACT_WALK_RPG,
        ACT_RUN_RPG, 
        ACT_WALK_CROUCH_RPG, 
        ACT_RUN_CROUCH_RPG, 
        ACT_WALK_RPG_RELAXED, 
        ACT_RUN_RPG_RELAXED, 

        ACT_WALK_RIFLE,
        ACT_WALK_AIM_RIFLE,
        ACT_WALK_CROUCH_RIFLE,
        ACT_WALK_CROUCH_AIM_RIFLE,
        ACT_RUN_RIFLE,
        ACT_RUN_AIM_RIFLE,
        ACT_RUN_CROUCH_RIFLE,
        ACT_RUN_CROUCH_AIM_RIFLE,
        ACT_RUN_STEALTH_PISTOL,

        ACT_WALK_AIM_SHOTGUN,
        ACT_RUN_AIM_SHOTGUN,

        ACT_WALK_PISTOL,
        ACT_RUN_PISTOL,
        ACT_WALK_AIM_PISTOL,
        ACT_RUN_AIM_PISTOL,
        ACT_WALK_STEALTH_PISTOL,
        ACT_WALK_AIM_STEALTH_PISTOL,
        ACT_RUN_AIM_STEALTH_PISTOL,

        // Reloads
        ACT_RELOAD_PISTOL,
        ACT_RELOAD_PISTOL_LOW,
        ACT_RELOAD_SMG1,
        ACT_RELOAD_SMG1_LOW,
        ACT_RELOAD_SHOTGUN,
        ACT_RELOAD_SHOTGUN_LOW,

        ACT_GESTURE_RELOAD,
        ACT_GESTURE_RELOAD_PISTOL,
        ACT_GESTURE_RELOAD_SMG1,
        ACT_GESTURE_RELOAD_SHOTGUN,

        // Busy animations
        ACT_BUSY_LEAN_LEFT,
        ACT_BUSY_LEAN_LEFT_ENTRY,
        ACT_BUSY_LEAN_LEFT_EXIT,
        ACT_BUSY_LEAN_BACK,
        ACT_BUSY_LEAN_BACK_ENTRY,
        ACT_BUSY_LEAN_BACK_EXIT,
        ACT_BUSY_SIT_GROUND,
        ACT_BUSY_SIT_GROUND_ENTRY,
        ACT_BUSY_SIT_GROUND_EXIT,
        ACT_BUSY_SIT_CHAIR,
        ACT_BUSY_SIT_CHAIR_ENTRY,
        ACT_BUSY_SIT_CHAIR_EXIT,
        ACT_BUSY_STAND,
        ACT_BUSY_QUEUE,

        // Dodge animations
        ACT_DUCK_DODGE,

        // For NPCs being lifted/eaten by barnacles:
        // being swallowed by a barnacle
        ACT_DIE_BARNACLE_SWALLOW,  
         // being lifted by a barnacle
        ACT_GESTURE_BARNACLE_STRANGLE, 

        ACT_PHYSCANNON_DETACH,        // An activity to be played if we're picking this up with the physcannon
        ACT_PHYSCANNON_ANIMATE, // An activity to be played by an object being picked up with the physcannon, but has different behavior to DETACH
        ACT_PHYSCANNON_ANIMATE_PRE,        // An activity to be played by an object being picked up with the physcannon, before playing the ACT_PHYSCANNON_ANIMATE
        ACT_PHYSCANNON_ANIMATE_POST,// An activity to be played by an object being picked up with the physcannon, after playing the ACT_PHYSCANNON_ANIMATE

        ACT_DIE_FRONTSIDE,
        ACT_DIE_RIGHTSIDE,
        ACT_DIE_BACKSIDE,
        ACT_DIE_LEFTSIDE,

        ACT_OPEN_DOOR,

        // Dynamic interactions
        ACT_DI_ALYX_ZOMBIE_MELEE,
        ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
        ACT_DI_ALYX_HEADCRAB_MELEE,
        ACT_DI_ALYX_ANTLION,

        ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
        ACT_DI_ALYX_ZOMBIE_SHOTGUN26,

        ACT_READINESS_RELAXED_TO_STIMULATED,
        ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
        ACT_READINESS_AGITATED_TO_STIMULATED,
        ACT_READINESS_STIMULATED_TO_RELAXED,

        ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
        ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
        ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
        ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,

        ACT_IDLE_CARRY,
        ACT_WALK_CARRY,

//===========================
// TF2 Specific Activities
//===========================
        ACT_STARTDYING,
        ACT_DYINGLOOP,
        ACT_DYINGTODEAD,

        ACT_RIDE_MANNED_GUN,

        // All viewmodels
        ACT_VM_SPRINT_ENTER,
        ACT_VM_SPRINT_IDLE,
        ACT_VM_SPRINT_LEAVE,

        // Looping weapon firing
        ACT_FIRE_START,
        ACT_FIRE_LOOP,
        ACT_FIRE_END,

        ACT_CROUCHING_GRENADEIDLE,
        ACT_CROUCHING_GRENADEREADY,
        ACT_CROUCHING_PRIMARYATTACK,
        ACT_OVERLAY_GRENADEIDLE,
        ACT_OVERLAY_GRENADEREADY,
        ACT_OVERLAY_PRIMARYATTACK,
        ACT_OVERLAY_SHIELD_UP,
        ACT_OVERLAY_SHIELD_DOWN,
        ACT_OVERLAY_SHIELD_UP_IDLE,
        ACT_OVERLAY_SHIELD_ATTACK,
        ACT_OVERLAY_SHIELD_KNOCKBACK,
        ACT_SHIELD_UP,
        ACT_SHIELD_DOWN,
        ACT_SHIELD_UP_IDLE,
        ACT_SHIELD_ATTACK,
        ACT_SHIELD_KNOCKBACK,
        ACT_CROUCHING_SHIELD_UP,
        ACT_CROUCHING_SHIELD_DOWN,
        ACT_CROUCHING_SHIELD_UP_IDLE,
        ACT_CROUCHING_SHIELD_ATTACK,
        ACT_CROUCHING_SHIELD_KNOCKBACK,

        // turning in place
        ACT_TURNRIGHT45,
        ACT_TURNLEFT45,

        ACT_TURN,

        ACT_OBJ_ASSEMBLING,
        ACT_OBJ_DISMANTLING,
        ACT_OBJ_STARTUP,
        ACT_OBJ_RUNNING,
        ACT_OBJ_IDLE,
        ACT_OBJ_PLACING,
        ACT_OBJ_DETERIORATING,
        ACT_OBJ_UPGRADING,

        // Deploy
        ACT_DEPLOY,
        ACT_DEPLOY_IDLE,
        ACT_UNDEPLOY,

//===========================
// HL1 Specific Activities
//===========================
        // Grenades
        ACT_GRENADE_ROLL,
        ACT_GRENADE_TOSS,

        // Hand grenade
        ACT_HANDGRENADE_THROW1,
        ACT_HANDGRENADE_THROW2,
        ACT_HANDGRENADE_THROW3,

        // Shotgun
        ACT_SHOTGUN_IDLE_DEEP,
        ACT_SHOTGUN_IDLE4,

        // Glock
        ACT_GLOCK_SHOOTEMPTY,
        ACT_GLOCK_SHOOT_RELOAD,

        // RPG
        ACT_RPG_DRAW_UNLOADED,
        ACT_RPG_HOLSTER_UNLOADED,
        ACT_RPG_IDLE_UNLOADED,
        ACT_RPG_FIDGET_UNLOADED,

        // Crossbow
        ACT_CROSSBOW_DRAW_UNLOADED,
        ACT_CROSSBOW_IDLE_UNLOADED,
        ACT_CROSSBOW_FIDGET_UNLOADED,

        // Gauss
        ACT_GAUSS_SPINUP,
        ACT_GAUSS_SPINCYCLE,

        // Tripmine
        ACT_TRIPMINE_GROUND,
        ACT_TRIPMINE_WORLD,

//===========================
// CSPort Specific Activities
//===========================

        ACT_VM_PRIMARYATTACK_SILENCED,                // fire
        ACT_VM_RELOAD_SILENCED,
        ACT_VM_DRYFIRE_SILENCED,                                // fire with no ammo loaded.
        ACT_VM_IDLE_SILENCED,
        ACT_VM_DRAW_SILENCED,
        ACT_VM_IDLE_EMPTY_LEFT,
        ACT_VM_DRYFIRE_LEFT,

        ACT_PLAYER_IDLE_FIRE,
        ACT_PLAYER_CROUCH_FIRE,
        ACT_PLAYER_CROUCH_WALK_FIRE,
        ACT_PLAYER_WALK_FIRE,
        ACT_PLAYER_RUN_FIRE,

        ACT_IDLETORUN,
        ACT_RUNTOIDLE,


//===========================
// DoD Specific Activities
//===========================
        ACT_SPRINT,

        ACT_GET_DOWN_STAND,
        ACT_GET_UP_STAND,
        ACT_GET_DOWN_CROUCH,
        ACT_GET_UP_CROUCH,
        ACT_PRONE_FORWARD,
        ACT_PRONE_IDLE,

        ACT_DEEPIDLE1,
        ACT_DEEPIDLE2,
        ACT_DEEPIDLE3,
        ACT_DEEPIDLE4,

        ACT_VM_RELOAD_DEPLOYED, 
        ACT_VM_RELOAD_IDLE,

        ACT_VM_DRAW_DEPLOYED,

        //Weapon is empty activities
        ACT_VM_DRAW_EMPTY,
        ACT_VM_PRIMARYATTACK_EMPTY,
        ACT_VM_RELOAD_EMPTY,
        ACT_VM_IDLE_EMPTY,
        ACT_VM_IDLE_DEPLOYED_EMPTY,

        ACT_VM_IDLE_8,
        ACT_VM_IDLE_7,
        ACT_VM_IDLE_6,
        ACT_VM_IDLE_5,
        ACT_VM_IDLE_4,
        ACT_VM_IDLE_3,
        ACT_VM_IDLE_2,
        ACT_VM_IDLE_1,

        ACT_VM_IDLE_DEPLOYED,
        ACT_VM_IDLE_DEPLOYED_8,
        ACT_VM_IDLE_DEPLOYED_7,
        ACT_VM_IDLE_DEPLOYED_6,
        ACT_VM_IDLE_DEPLOYED_5,
        ACT_VM_IDLE_DEPLOYED_4,
        ACT_VM_IDLE_DEPLOYED_3,
        ACT_VM_IDLE_DEPLOYED_2,
        ACT_VM_IDLE_DEPLOYED_1,

        // Animation from prone idle to standing/crouch idle. Number designates bullets left
        ACT_VM_UNDEPLOY,
        ACT_VM_UNDEPLOY_8,
        ACT_VM_UNDEPLOY_7,
        ACT_VM_UNDEPLOY_6,
        ACT_VM_UNDEPLOY_5,
        ACT_VM_UNDEPLOY_4,
        ACT_VM_UNDEPLOY_3,
        ACT_VM_UNDEPLOY_2,
        ACT_VM_UNDEPLOY_1,
        ACT_VM_UNDEPLOY_EMPTY,

        // Animation from standing/crouch idle to prone idle. Number designates bullets left
        ACT_VM_DEPLOY,
        ACT_VM_DEPLOY_8,
        ACT_VM_DEPLOY_7,
        ACT_VM_DEPLOY_6,
        ACT_VM_DEPLOY_5,
        ACT_VM_DEPLOY_4,
        ACT_VM_DEPLOY_3,
        ACT_VM_DEPLOY_2,
        ACT_VM_DEPLOY_1,
        ACT_VM_DEPLOY_EMPTY,

        // Shooting animations for standing/crouch position.  Number designates bullets left at START of animation
        ACT_VM_PRIMARYATTACK_8,
        ACT_VM_PRIMARYATTACK_7,
        ACT_VM_PRIMARYATTACK_6,
        ACT_VM_PRIMARYATTACK_5,
        ACT_VM_PRIMARYATTACK_4,
        ACT_VM_PRIMARYATTACK_3,
        ACT_VM_PRIMARYATTACK_2,
        ACT_VM_PRIMARYATTACK_1,

        // Shooting animations for prone position. Number designates bullets left at START of animation
        ACT_VM_PRIMARYATTACK_DEPLOYED,
        ACT_VM_PRIMARYATTACK_DEPLOYED_8,
        ACT_VM_PRIMARYATTACK_DEPLOYED_7,
        ACT_VM_PRIMARYATTACK_DEPLOYED_6, 
        ACT_VM_PRIMARYATTACK_DEPLOYED_5,
        ACT_VM_PRIMARYATTACK_DEPLOYED_4,
        ACT_VM_PRIMARYATTACK_DEPLOYED_3,
        ACT_VM_PRIMARYATTACK_DEPLOYED_2,
        ACT_VM_PRIMARYATTACK_DEPLOYED_1,
        ACT_VM_PRIMARYATTACK_DEPLOYED_EMPTY,

        // Player anim ACTs
        ACT_DOD_DEPLOYED,
        ACT_DOD_PRONE_DEPLOYED,
        ACT_DOD_IDLE_ZOOMED,
        ACT_DOD_WALK_ZOOMED,
        ACT_DOD_CROUCH_ZOOMED,
        ACT_DOD_CROUCHWALK_ZOOMED,
        ACT_DOD_PRONE_ZOOMED,
        ACT_DOD_PRONE_FORWARD_ZOOMED,
        ACT_DOD_PRIMARYATTACK_DEPLOYED,
        ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED,
        ACT_DOD_RELOAD_DEPLOYED,
        ACT_DOD_RELOAD_PRONE_DEPLOYED,        
        ACT_DOD_PRIMARYATTACK_PRONE,
        ACT_DOD_SECONDARYATTACK_PRONE,
        ACT_DOD_RELOAD_CROUCH,
        ACT_DOD_RELOAD_PRONE,
        ACT_DOD_STAND_IDLE,
        ACT_DOD_STAND_AIM,
        ACT_DOD_CROUCH_IDLE,
        ACT_DOD_CROUCH_AIM,
        ACT_DOD_CROUCHWALK_IDLE,
        ACT_DOD_CROUCHWALK_AIM,
        ACT_DOD_WALK_IDLE,
        ACT_DOD_WALK_AIM,
        ACT_DOD_RUN_IDLE,
        ACT_DOD_RUN_AIM,

        // Positions
        ACT_DOD_STAND_AIM_PISTOL,
        ACT_DOD_CROUCH_AIM_PISTOL,
        ACT_DOD_CROUCHWALK_AIM_PISTOL,
        ACT_DOD_WALK_AIM_PISTOL,
        ACT_DOD_RUN_AIM_PISTOL,
        ACT_DOD_PRONE_AIM_PISTOL,
        ACT_DOD_STAND_IDLE_PISTOL,
        ACT_DOD_CROUCH_IDLE_PISTOL,
        ACT_DOD_CROUCHWALK_IDLE_PISTOL,
        ACT_DOD_WALK_IDLE_PISTOL,
        ACT_DOD_RUN_IDLE_PISTOL,
        ACT_DOD_SPRINT_IDLE_PISTOL,
        ACT_DOD_PRONEWALK_IDLE_PISTOL,

        ACT_DOD_STAND_AIM_C96,
        ACT_DOD_CROUCH_AIM_C96,
        ACT_DOD_CROUCHWALK_AIM_C96,
        ACT_DOD_WALK_AIM_C96,
        ACT_DOD_RUN_AIM_C96,
        ACT_DOD_PRONE_AIM_C96,
        ACT_DOD_STAND_IDLE_C96,
        ACT_DOD_CROUCH_IDLE_C96,
        ACT_DOD_CROUCHWALK_IDLE_C96,
        ACT_DOD_WALK_IDLE_C96,
        ACT_DOD_RUN_IDLE_C96,
        ACT_DOD_SPRINT_IDLE_C96,
        ACT_DOD_PRONEWALK_IDLE_C96,

        ACT_DOD_STAND_AIM_RIFLE,
        ACT_DOD_CROUCH_AIM_RIFLE,
        ACT_DOD_CROUCHWALK_AIM_RIFLE,
        ACT_DOD_WALK_AIM_RIFLE,
        ACT_DOD_RUN_AIM_RIFLE,
        ACT_DOD_PRONE_AIM_RIFLE,
        ACT_DOD_STAND_IDLE_RIFLE,
        ACT_DOD_CROUCH_IDLE_RIFLE,
        ACT_DOD_CROUCHWALK_IDLE_RIFLE,
        ACT_DOD_WALK_IDLE_RIFLE,
        ACT_DOD_RUN_IDLE_RIFLE,
        ACT_DOD_SPRINT_IDLE_RIFLE,
        ACT_DOD_PRONEWALK_IDLE_RIFLE,

        ACT_DOD_STAND_AIM_BOLT,
        ACT_DOD_CROUCH_AIM_BOLT,
        ACT_DOD_CROUCHWALK_AIM_BOLT,
        ACT_DOD_WALK_AIM_BOLT,
        ACT_DOD_RUN_AIM_BOLT,
        ACT_DOD_PRONE_AIM_BOLT,
        ACT_DOD_STAND_IDLE_BOLT,
        ACT_DOD_CROUCH_IDLE_BOLT,
        ACT_DOD_CROUCHWALK_IDLE_BOLT,
        ACT_DOD_WALK_IDLE_BOLT,
        ACT_DOD_RUN_IDLE_BOLT,
        ACT_DOD_SPRINT_IDLE_BOLT,
        ACT_DOD_PRONEWALK_IDLE_BOLT,

        ACT_DOD_STAND_AIM_TOMMY,
        ACT_DOD_CROUCH_AIM_TOMMY,
        ACT_DOD_CROUCHWALK_AIM_TOMMY,
        ACT_DOD_WALK_AIM_TOMMY,
        ACT_DOD_RUN_AIM_TOMMY,
        ACT_DOD_PRONE_AIM_TOMMY,
        ACT_DOD_STAND_IDLE_TOMMY,
        ACT_DOD_CROUCH_IDLE_TOMMY,
        ACT_DOD_CROUCHWALK_IDLE_TOMMY,
        ACT_DOD_WALK_IDLE_TOMMY,
        ACT_DOD_RUN_IDLE_TOMMY,
        ACT_DOD_SPRINT_IDLE_TOMMY,
        ACT_DOD_PRONEWALK_IDLE_TOMMY,

        ACT_DOD_STAND_AIM_MP40,
        ACT_DOD_CROUCH_AIM_MP40,
        ACT_DOD_CROUCHWALK_AIM_MP40,
        ACT_DOD_WALK_AIM_MP40,
        ACT_DOD_RUN_AIM_MP40,
        ACT_DOD_PRONE_AIM_MP40,
        ACT_DOD_STAND_IDLE_MP40,
        ACT_DOD_CROUCH_IDLE_MP40,
        ACT_DOD_CROUCHWALK_IDLE_MP40,
        ACT_DOD_WALK_IDLE_MP40,
        ACT_DOD_RUN_IDLE_MP40,
        ACT_DOD_SPRINT_IDLE_MP40,
        ACT_DOD_PRONEWALK_IDLE_MP40,

        ACT_DOD_STAND_AIM_MP44,
        ACT_DOD_CROUCH_AIM_MP44,
        ACT_DOD_CROUCHWALK_AIM_MP44,
        ACT_DOD_WALK_AIM_MP44,
        ACT_DOD_RUN_AIM_MP44,
        ACT_DOD_PRONE_AIM_MP44,
        ACT_DOD_STAND_IDLE_MP44,
        ACT_DOD_CROUCH_IDLE_MP44,
        ACT_DOD_CROUCHWALK_IDLE_MP44,
        ACT_DOD_WALK_IDLE_MP44,
        ACT_DOD_RUN_IDLE_MP44,
        ACT_DOD_SPRINT_IDLE_MP44,
        ACT_DOD_PRONEWALK_IDLE_MP44,

        ACT_DOD_STAND_AIM_GREASE,
        ACT_DOD_CROUCH_AIM_GREASE,
        ACT_DOD_CROUCHWALK_AIM_GREASE,
        ACT_DOD_WALK_AIM_GREASE,
        ACT_DOD_RUN_AIM_GREASE,
        ACT_DOD_PRONE_AIM_GREASE,
        ACT_DOD_STAND_IDLE_GREASE,
        ACT_DOD_CROUCH_IDLE_GREASE,
        ACT_DOD_CROUCHWALK_IDLE_GREASE,
        ACT_DOD_WALK_IDLE_GREASE,
        ACT_DOD_RUN_IDLE_GREASE,
        ACT_DOD_SPRINT_IDLE_GREASE,
        ACT_DOD_PRONEWALK_IDLE_GREASE,

        ACT_DOD_STAND_AIM_MG,
        ACT_DOD_CROUCH_AIM_MG,
        ACT_DOD_CROUCHWALK_AIM_MG,
        ACT_DOD_WALK_AIM_MG,
        ACT_DOD_RUN_AIM_MG,
        ACT_DOD_PRONE_AIM_MG,
        ACT_DOD_STAND_IDLE_MG,
        ACT_DOD_CROUCH_IDLE_MG,
        ACT_DOD_CROUCHWALK_IDLE_MG,
        ACT_DOD_WALK_IDLE_MG,
        ACT_DOD_RUN_IDLE_MG,
        ACT_DOD_SPRINT_IDLE_MG,
        ACT_DOD_PRONEWALK_IDLE_MG,

        ACT_DOD_STAND_AIM_30CAL,
        ACT_DOD_CROUCH_AIM_30CAL,
        ACT_DOD_CROUCHWALK_AIM_30CAL,
        ACT_DOD_WALK_AIM_30CAL,
        ACT_DOD_RUN_AIM_30CAL,
        ACT_DOD_PRONE_AIM_30CAL,
        ACT_DOD_STAND_IDLE_30CAL,
        ACT_DOD_CROUCH_IDLE_30CAL,
        ACT_DOD_CROUCHWALK_IDLE_30CAL,
        ACT_DOD_WALK_IDLE_30CAL,
        ACT_DOD_RUN_IDLE_30CAL,
        ACT_DOD_SPRINT_IDLE_30CAL,
        ACT_DOD_PRONEWALK_IDLE_30CAL,

        ACT_DOD_STAND_AIM_GREN_FRAG,
        ACT_DOD_CROUCH_AIM_GREN_FRAG,
        ACT_DOD_CROUCHWALK_AIM_GREN_FRAG,
        ACT_DOD_WALK_AIM_GREN_FRAG,
        ACT_DOD_RUN_AIM_GREN_FRAG,
        ACT_DOD_PRONE_AIM_GREN_FRAG,
        ACT_DOD_SPRINT_AIM_GREN_FRAG,
        ACT_DOD_PRONEWALK_AIM_GREN_FRAG,
        ACT_DOD_STAND_AIM_GREN_STICK,
        ACT_DOD_CROUCH_AIM_GREN_STICK,
        ACT_DOD_CROUCHWALK_AIM_GREN_STICK,
        ACT_DOD_WALK_AIM_GREN_STICK,
        ACT_DOD_RUN_AIM_GREN_STICK,
        ACT_DOD_PRONE_AIM_GREN_STICK,
        ACT_DOD_SPRINT_AIM_GREN_STICK,
        ACT_DOD_PRONEWALK_AIM_GREN_STICK,

        ACT_DOD_STAND_AIM_KNIFE,
        ACT_DOD_CROUCH_AIM_KNIFE,
        ACT_DOD_CROUCHWALK_AIM_KNIFE,
        ACT_DOD_WALK_AIM_KNIFE,
        ACT_DOD_RUN_AIM_KNIFE,
        ACT_DOD_PRONE_AIM_KNIFE,
        ACT_DOD_SPRINT_AIM_KNIFE,
        ACT_DOD_PRONEWALK_AIM_KNIFE,

        ACT_DOD_STAND_AIM_SPADE,
        ACT_DOD_CROUCH_AIM_SPADE,
        ACT_DOD_CROUCHWALK_AIM_SPADE,
        ACT_DOD_WALK_AIM_SPADE,
        ACT_DOD_RUN_AIM_SPADE,
        ACT_DOD_PRONE_AIM_SPADE,
        ACT_DOD_SPRINT_AIM_SPADE,
        ACT_DOD_PRONEWALK_AIM_SPADE,

        ACT_DOD_STAND_AIM_BAZOOKA,
        ACT_DOD_CROUCH_AIM_BAZOOKA,
        ACT_DOD_CROUCHWALK_AIM_BAZOOKA,
        ACT_DOD_WALK_AIM_BAZOOKA,
        ACT_DOD_RUN_AIM_BAZOOKA,
        ACT_DOD_PRONE_AIM_BAZOOKA,
        ACT_DOD_STAND_IDLE_BAZOOKA,
        ACT_DOD_CROUCH_IDLE_BAZOOKA,
        ACT_DOD_CROUCHWALK_IDLE_BAZOOKA,
        ACT_DOD_WALK_IDLE_BAZOOKA,
        ACT_DOD_RUN_IDLE_BAZOOKA,
        ACT_DOD_SPRINT_IDLE_BAZOOKA,
        ACT_DOD_PRONEWALK_IDLE_BAZOOKA,

        ACT_DOD_STAND_AIM_PSCHRECK,
        ACT_DOD_CROUCH_AIM_PSCHRECK,
        ACT_DOD_CROUCHWALK_AIM_PSCHRECK,
        ACT_DOD_WALK_AIM_PSCHRECK,
        ACT_DOD_RUN_AIM_PSCHRECK,
        ACT_DOD_PRONE_AIM_PSCHRECK,
        ACT_DOD_STAND_IDLE_PSCHRECK,
        ACT_DOD_CROUCH_IDLE_PSCHRECK,
        ACT_DOD_CROUCHWALK_IDLE_PSCHRECK,
        ACT_DOD_WALK_IDLE_PSCHRECK,
        ACT_DOD_RUN_IDLE_PSCHRECK,
        ACT_DOD_SPRINT_IDLE_PSCHRECK,
        ACT_DOD_PRONEWALK_IDLE_PSCHRECK,

        ACT_DOD_STAND_AIM_BAR,
        ACT_DOD_CROUCH_AIM_BAR,
        ACT_DOD_CROUCHWALK_AIM_BAR,
        ACT_DOD_WALK_AIM_BAR,
        ACT_DOD_RUN_AIM_BAR,
        ACT_DOD_PRONE_AIM_BAR,
        ACT_DOD_STAND_IDLE_BAR,
        ACT_DOD_CROUCH_IDLE_BAR,
        ACT_DOD_CROUCHWALK_IDLE_BAR,
        ACT_DOD_WALK_IDLE_BAR,
        ACT_DOD_RUN_IDLE_BAR,
        ACT_DOD_SPRINT_IDLE_BAR,
        ACT_DOD_PRONEWALK_IDLE_BAR,

        // Zoomed aims
        ACT_DOD_STAND_ZOOM_RIFLE,
        ACT_DOD_CROUCH_ZOOM_RIFLE,
        ACT_DOD_CROUCHWALK_ZOOM_RIFLE,
        ACT_DOD_WALK_ZOOM_RIFLE,
        ACT_DOD_RUN_ZOOM_RIFLE,
        ACT_DOD_PRONE_ZOOM_RIFLE,

        ACT_DOD_STAND_ZOOM_BOLT,
        ACT_DOD_CROUCH_ZOOM_BOLT,
        ACT_DOD_CROUCHWALK_ZOOM_BOLT,
        ACT_DOD_WALK_ZOOM_BOLT,
        ACT_DOD_RUN_ZOOM_BOLT,
        ACT_DOD_PRONE_ZOOM_BOLT,

        ACT_DOD_STAND_ZOOM_BAZOOKA,
        ACT_DOD_CROUCH_ZOOM_BAZOOKA,
        ACT_DOD_CROUCHWALK_ZOOM_BAZOOKA,
        ACT_DOD_WALK_ZOOM_BAZOOKA,
        ACT_DOD_RUN_ZOOM_BAZOOKA,
        ACT_DOD_PRONE_ZOOM_BAZOOKA,

        ACT_DOD_STAND_ZOOM_PSCHRECK,
        ACT_DOD_CROUCH_ZOOM_PSCHRECK,
        ACT_DOD_CROUCHWALK_ZOOM_PSCHRECK,
        ACT_DOD_WALK_ZOOM_PSCHRECK,
        ACT_DOD_RUN_ZOOM_PSCHRECK,
        ACT_DOD_PRONE_ZOOM_PSCHRECK,

        // Deployed Aim
        ACT_DOD_DEPLOY_RIFLE,
        ACT_DOD_DEPLOY_TOMMY,
        ACT_DOD_DEPLOY_MG,
        ACT_DOD_DEPLOY_30CAL,

        // Prone Deployed Aim
        ACT_DOD_PRONE_DEPLOY_RIFLE ,
        ACT_DOD_PRONE_DEPLOY_TOMMY,
        ACT_DOD_PRONE_DEPLOY_MG,
        ACT_DOD_PRONE_DEPLOY_30CAL,

        // Attacks

        // Rifle
        ACT_DOD_PRIMARYATTACK_RIFLE,
        ACT_DOD_SECONDARYATTACK_RIFLE,
        ACT_DOD_PRIMARYATTACK_PRONE_RIFLE,
        ACT_DOD_SECONDARYATTACK_PRONE_RIFLE,
        ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_RIFLE,
        ACT_DOD_PRIMARYATTACK_DEPLOYED_RIFLE,

        // Bolt
        ACT_DOD_PRIMARYATTACK_BOLT,
        ACT_DOD_SECONDARYATTACK_BOLT,
        ACT_DOD_PRIMARYATTACK_PRONE_BOLT ,
        ACT_DOD_SECONDARYATTACK_PRONE_BOLT ,

        // Tommy
        ACT_DOD_PRIMARYATTACK_TOMMY,
        ACT_DOD_PRIMARYATTACK_PRONE_TOMMY,
        ACT_DOD_SECONDARYATTACK_TOMMY,
        ACT_DOD_SECONDARYATTACK_PRONE_TOMMY,

        // MP40
        ACT_DOD_PRIMARYATTACK_MP40,
        ACT_DOD_PRIMARYATTACK_PRONE_MP40 ,
        ACT_DOD_SECONDARYATTACK_MP40,
        ACT_DOD_SECONDARYATTACK_PRONE_MP40 ,

        // MP44
        ACT_DOD_PRIMARYATTACK_MP44,
        ACT_DOD_PRIMARYATTACK_PRONE_MP44 ,

        // Greasegun
        ACT_DOD_PRIMARYATTACK_GREASE,
        ACT_DOD_PRIMARYATTACK_PRONE_GREASE ,

        // Pistols (Colt, Luger)
        ACT_DOD_PRIMARYATTACK_PISTOL,
        ACT_DOD_PRIMARYATTACK_PRONE_PISTOL ,
        ACT_DOD_PRIMARYATTACK_C96,
        ACT_DOD_PRIMARYATTACK_PRONE_C96,

        // Mgs (mg42, mg34)
        ACT_DOD_PRIMARYATTACK_MG,
        ACT_DOD_PRIMARYATTACK_PRONE_MG ,
        ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_MG ,
        ACT_DOD_PRIMARYATTACK_DEPLOYED_MG ,

        // 30cal
        ACT_DOD_PRIMARYATTACK_30CAL,
        ACT_DOD_PRIMARYATTACK_PRONE_30CAL,
        ACT_DOD_PRIMARYATTACK_DEPLOYED_30CAL,
        ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_30CAL ,

        // Grenades
        ACT_DOD_PRIMARYATTACK_GREN_FRAG,
        ACT_DOD_PRIMARYATTACK_PRONE_GREN_FRAG,
        ACT_DOD_PRIMARYATTACK_GREN_STICK,
        ACT_DOD_PRIMARYATTACK_PRONE_GREN_STICK,

        // Knife
        ACT_DOD_PRIMARYATTACK_KNIFE,
        ACT_DOD_PRIMARYATTACK_PRONE_KNIFE,

        // Spade
        ACT_DOD_PRIMARYATTACK_SPADE,
        ACT_DOD_PRIMARYATTACK_PRONE_SPADE,

        // Bazooka
        ACT_DOD_PRIMARYATTACK_BAZOOKA,
        ACT_DOD_PRIMARYATTACK_PRONE_BAZOOKA,

        // Pschreck
        ACT_DOD_PRIMARYATTACK_PSCHRECK,
        ACT_DOD_PRIMARYATTACK_PRONE_PSCHRECK ,

        // Bar
        ACT_DOD_PRIMARYATTACK_BAR,
        ACT_DOD_PRIMARYATTACK_PRONE_BAR,

        // Reloads
        ACT_DOD_RELOAD_GARAND,
        ACT_DOD_RELOAD_K43,
        ACT_DOD_RELOAD_BAR,
        ACT_DOD_RELOAD_MP40,
        ACT_DOD_RELOAD_MP44,
        ACT_DOD_RELOAD_BOLT,
        ACT_DOD_RELOAD_M1CARBINE,
        ACT_DOD_RELOAD_TOMMY,
        ACT_DOD_RELOAD_GREASEGUN,
        ACT_DOD_RELOAD_PISTOL,
        ACT_DOD_RELOAD_FG42,
        ACT_DOD_RELOAD_RIFLE,
        ACT_DOD_RELOAD_RIFLEGRENADE,
        ACT_DOD_RELOAD_C96,

        // Crouch
        ACT_DOD_RELOAD_CROUCH_BAR,
        ACT_DOD_RELOAD_CROUCH_RIFLE,
        ACT_DOD_RELOAD_CROUCH_RIFLEGRENADE,
        ACT_DOD_RELOAD_CROUCH_BOLT,
        ACT_DOD_RELOAD_CROUCH_MP44,
        ACT_DOD_RELOAD_CROUCH_MP40,
        ACT_DOD_RELOAD_CROUCH_TOMMY,
        ACT_DOD_RELOAD_CROUCH_BAZOOKA,
        ACT_DOD_RELOAD_CROUCH_PSCHRECK,
        ACT_DOD_RELOAD_CROUCH_PISTOL,
        ACT_DOD_RELOAD_CROUCH_M1CARBINE,
        ACT_DOD_RELOAD_CROUCH_C96,

        // Bazookas
        ACT_DOD_RELOAD_BAZOOKA,
        ACT_DOD_ZOOMLOAD_BAZOOKA,
        ACT_DOD_RELOAD_PSCHRECK,
        ACT_DOD_ZOOMLOAD_PSCHRECK,

        // Deployed
        ACT_DOD_RELOAD_DEPLOYED_FG42,
        ACT_DOD_RELOAD_DEPLOYED_30CAL,
        ACT_DOD_RELOAD_DEPLOYED_MG,
        ACT_DOD_RELOAD_DEPLOYED_MG34,
        ACT_DOD_RELOAD_DEPLOYED_BAR,

        // Prone
        ACT_DOD_RELOAD_PRONE_PISTOL,
        ACT_DOD_RELOAD_PRONE_GARAND,
        ACT_DOD_RELOAD_PRONE_M1CARBINE,
        ACT_DOD_RELOAD_PRONE_BOLT,
        ACT_DOD_RELOAD_PRONE_K43,
        ACT_DOD_RELOAD_PRONE_MP40,
        ACT_DOD_RELOAD_PRONE_MP44,
        ACT_DOD_RELOAD_PRONE_BAR,
        ACT_DOD_RELOAD_PRONE_GREASEGUN,
        ACT_DOD_RELOAD_PRONE_TOMMY,
        ACT_DOD_RELOAD_PRONE_FG42,
        ACT_DOD_RELOAD_PRONE_RIFLE,
        ACT_DOD_RELOAD_PRONE_RIFLEGRENADE,
        ACT_DOD_RELOAD_PRONE_C96,

        // Prone bazooka
        ACT_DOD_RELOAD_PRONE_BAZOOKA,
        ACT_DOD_ZOOMLOAD_PRONE_BAZOOKA,
        ACT_DOD_RELOAD_PRONE_PSCHRECK,
        ACT_DOD_ZOOMLOAD_PRONE_PSCHRECK,

        // Prone deployed
        ACT_DOD_RELOAD_PRONE_DEPLOYED_BAR,
        ACT_DOD_RELOAD_PRONE_DEPLOYED_FG42,
        ACT_DOD_RELOAD_PRONE_DEPLOYED_30CAL,
        ACT_DOD_RELOAD_PRONE_DEPLOYED_MG,
        ACT_DOD_RELOAD_PRONE_DEPLOYED_MG34,

        // Prone zoomed aim
        ACT_DOD_PRONE_ZOOM_FORWARD_RIFLE,
        ACT_DOD_PRONE_ZOOM_FORWARD_BOLT,
        ACT_DOD_PRONE_ZOOM_FORWARD_BAZOOKA,
        ACT_DOD_PRONE_ZOOM_FORWARD_PSCHRECK,

        // Crouch attack
        ACT_DOD_PRIMARYATTACK_CROUCH,
        ACT_DOD_PRIMARYATTACK_CROUCH_SPADE,
        ACT_DOD_PRIMARYATTACK_CROUCH_KNIFE,
        ACT_DOD_PRIMARYATTACK_CROUCH_GREN_FRAG,
        ACT_DOD_PRIMARYATTACK_CROUCH_GREN_STICK,
        ACT_DOD_SECONDARYATTACK_CROUCH,
        ACT_DOD_SECONDARYATTACK_CROUCH_TOMMY,
        ACT_DOD_SECONDARYATTACK_CROUCH_MP40,

        // Hand Signals
        ACT_DOD_HS_IDLE,
        ACT_DOD_HS_CROUCH,
        ACT_DOD_HS_IDLE_30CAL,
        ACT_DOD_HS_IDLE_BAZOOKA,
        ACT_DOD_HS_IDLE_PSCHRECK,
        ACT_DOD_HS_IDLE_KNIFE,
        ACT_DOD_HS_IDLE_MG42,
        ACT_DOD_HS_IDLE_PISTOL,
        ACT_DOD_HS_IDLE_STICKGRENADE,
        ACT_DOD_HS_IDLE_TOMMY,
        ACT_DOD_HS_IDLE_MP44,
        ACT_DOD_HS_IDLE_K98,
        ACT_DOD_HS_CROUCH_30CAL,
        ACT_DOD_HS_CROUCH_BAZOOKA,
        ACT_DOD_HS_CROUCH_PSCHRECK,
        ACT_DOD_HS_CROUCH_KNIFE,
        ACT_DOD_HS_CROUCH_MG42,
        ACT_DOD_HS_CROUCH_PISTOL,
        ACT_DOD_HS_CROUCH_STICKGRENADE,
        ACT_DOD_HS_CROUCH_TOMMY,
        ACT_DOD_HS_CROUCH_MP44,
        ACT_DOD_HS_CROUCH_K98,

        ACT_DOD_STAND_IDLE_TNT,
        ACT_DOD_CROUCH_IDLE_TNT,
        ACT_DOD_CROUCHWALK_IDLE_TNT,
        ACT_DOD_WALK_IDLE_TNT,
        ACT_DOD_RUN_IDLE_TNT,
        ACT_DOD_SPRINT_IDLE_TNT,
        ACT_DOD_PRONEWALK_IDLE_TNT,

        ACT_DOD_PLANT_TNT,
        ACT_DOD_DEFUSE_TNT,

// HL2MP
        ACT_HL2MP_IDLE,
        ACT_HL2MP_RUN,
        ACT_HL2MP_IDLE_CROUCH,
        ACT_HL2MP_WALK_CROUCH,
        ACT_HL2MP_GESTURE_RANGE_ATTACK,
        ACT_HL2MP_GESTURE_RELOAD,
        ACT_HL2MP_JUMP,

        ACT_HL2MP_IDLE_PISTOL,
        ACT_HL2MP_RUN_PISTOL,
        ACT_HL2MP_IDLE_CROUCH_PISTOL,
        ACT_HL2MP_WALK_CROUCH_PISTOL,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_PISTOL,
        ACT_HL2MP_GESTURE_RELOAD_PISTOL,
        ACT_HL2MP_JUMP_PISTOL,

        ACT_HL2MP_IDLE_SMG1,
        ACT_HL2MP_RUN_SMG1,
        ACT_HL2MP_IDLE_CROUCH_SMG1,
        ACT_HL2MP_WALK_CROUCH_SMG1,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_SMG1,
        ACT_HL2MP_GESTURE_RELOAD_SMG1,
        ACT_HL2MP_JUMP_SMG1,

          ACT_HL2MP_IDLE_AR2,
        ACT_HL2MP_RUN_AR2,
        ACT_HL2MP_IDLE_CROUCH_AR2,
        ACT_HL2MP_WALK_CROUCH_AR2,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2,
        ACT_HL2MP_GESTURE_RELOAD_AR2,
        ACT_HL2MP_JUMP_AR2,

          ACT_HL2MP_IDLE_SHOTGUN,
        ACT_HL2MP_RUN_SHOTGUN,
        ACT_HL2MP_IDLE_CROUCH_SHOTGUN,
        ACT_HL2MP_WALK_CROUCH_SHOTGUN,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_SHOTGUN,
        ACT_HL2MP_GESTURE_RELOAD_SHOTGUN,
        ACT_HL2MP_JUMP_SHOTGUN,

          ACT_HL2MP_IDLE_RPG,
        ACT_HL2MP_RUN_RPG,
        ACT_HL2MP_IDLE_CROUCH_RPG,
        ACT_HL2MP_WALK_CROUCH_RPG,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_RPG,
        ACT_HL2MP_GESTURE_RELOAD_RPG,
        ACT_HL2MP_JUMP_RPG,

          ACT_HL2MP_IDLE_GRENADE,
        ACT_HL2MP_RUN_GRENADE,
        ACT_HL2MP_IDLE_CROUCH_GRENADE,
        ACT_HL2MP_WALK_CROUCH_GRENADE,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_GRENADE,
        ACT_HL2MP_GESTURE_RELOAD_GRENADE,
        ACT_HL2MP_JUMP_GRENADE,

          ACT_HL2MP_IDLE_PHYSGUN,
        ACT_HL2MP_RUN_PHYSGUN,
        ACT_HL2MP_IDLE_CROUCH_PHYSGUN,
        ACT_HL2MP_WALK_CROUCH_PHYSGUN,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_PHYSGUN,
        ACT_HL2MP_GESTURE_RELOAD_PHYSGUN,
        ACT_HL2MP_JUMP_PHYSGUN,

          ACT_HL2MP_IDLE_CROSSBOW,
        ACT_HL2MP_RUN_CROSSBOW,
        ACT_HL2MP_IDLE_CROUCH_CROSSBOW,
        ACT_HL2MP_WALK_CROUCH_CROSSBOW,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_CROSSBOW,
        ACT_HL2MP_GESTURE_RELOAD_CROSSBOW,
        ACT_HL2MP_JUMP_CROSSBOW,

          ACT_HL2MP_IDLE_MELEE,
        ACT_HL2MP_RUN_MELEE,
        ACT_HL2MP_IDLE_CROUCH_MELEE,
        ACT_HL2MP_WALK_CROUCH_MELEE,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
        ACT_HL2MP_GESTURE_RELOAD_MELEE,
        ACT_HL2MP_JUMP_MELEE,

        ACT_HL2MP_IDLE_SLAM,
        ACT_HL2MP_RUN_SLAM,
        ACT_HL2MP_IDLE_CROUCH_SLAM,
        ACT_HL2MP_WALK_CROUCH_SLAM,
        ACT_HL2MP_GESTURE_RANGE_ATTACK_SLAM,
        ACT_HL2MP_GESTURE_RELOAD_SLAM,
        ACT_HL2MP_JUMP_SLAM,

// Portal!
        ACT_VM_FIZZLE,

        // Multiplayer
        ACT_MP_STAND_IDLE,
        ACT_MP_CROUCH_IDLE,
        ACT_MP_CROUCH_DEPLOYED_IDLE,
        ACT_MP_CROUCH_DEPLOYED,
        ACT_MP_CROUCHWALK_DEPLOYED,
        ACT_MP_DEPLOYED_IDLE,
        ACT_MP_RUN,
        ACT_MP_WALK,
        ACT_MP_AIRWALK,
        ACT_MP_CROUCHWALK,
        ACT_MP_SPRINT,
        ACT_MP_JUMP,
        ACT_MP_JUMP_START,
        ACT_MP_JUMP_FLOAT,
        ACT_MP_JUMP_LAND,
        ACT_MP_DOUBLEJUMP,
        ACT_MP_SWIM,
        ACT_MP_DEPLOYED,
        ACT_MP_SWIM_DEPLOYED,
        ACT_MP_VCD,

        ACT_MP_ATTACK_STAND_PRIMARYFIRE,
        ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
        ACT_MP_ATTACK_STAND_SECONDARYFIRE,
        ACT_MP_ATTACK_STAND_GRENADE,
        ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
        ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
        ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
        ACT_MP_ATTACK_CROUCH_GRENADE,
        ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
        ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
        ACT_MP_ATTACK_SWIM_GRENADE,
        ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
        ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
        ACT_MP_ATTACK_AIRWALK_GRENADE,
        ACT_MP_RELOAD_STAND,
        ACT_MP_RELOAD_STAND_LOOP,
        ACT_MP_RELOAD_STAND_END,
        ACT_MP_RELOAD_CROUCH,
        ACT_MP_RELOAD_CROUCH_LOOP,
        ACT_MP_RELOAD_CROUCH_END,
        ACT_MP_RELOAD_SWIM,
        ACT_MP_RELOAD_SWIM_LOOP,
        ACT_MP_RELOAD_SWIM_END,
        ACT_MP_RELOAD_AIRWALK,
        ACT_MP_RELOAD_AIRWALK_LOOP,
        ACT_MP_RELOAD_AIRWALK_END,
        ACT_MP_ATTACK_STAND_PREFIRE,
        ACT_MP_ATTACK_STAND_POSTFIRE,
        ACT_MP_ATTACK_STAND_STARTFIRE,
        ACT_MP_ATTACK_CROUCH_PREFIRE,
        ACT_MP_ATTACK_CROUCH_POSTFIRE,
        ACT_MP_ATTACK_SWIM_PREFIRE,
        ACT_MP_ATTACK_SWIM_POSTFIRE,

        // Multiplayer - Primary
        ACT_MP_STAND_PRIMARY,
        ACT_MP_CROUCH_PRIMARY,
        ACT_MP_RUN_PRIMARY,
        ACT_MP_WALK_PRIMARY,
        ACT_MP_AIRWALK_PRIMARY,
        ACT_MP_CROUCHWALK_PRIMARY,
        ACT_MP_JUMP_PRIMARY,
        ACT_MP_JUMP_START_PRIMARY,
        ACT_MP_JUMP_FLOAT_PRIMARY,
        ACT_MP_JUMP_LAND_PRIMARY,
        ACT_MP_SWIM_PRIMARY,
        ACT_MP_DEPLOYED_PRIMARY,
        ACT_MP_SWIM_DEPLOYED_PRIMARY,
        ACT_MP_CROUCHWALK_DEPLOYED_PRIMARY,
        ACT_MP_CROUCH_DEPLOYED_IDLE_PRIMARY,

        ACT_MP_ATTACK_STAND_PRIMARY,                // RUN, WALK
        ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
        ACT_MP_ATTACK_CROUCH_PRIMARY,                // CROUCHWALK
        ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
        ACT_MP_ATTACK_SWIM_PRIMARY,
        ACT_MP_ATTACK_AIRWALK_PRIMARY,

        ACT_MP_RELOAD_STAND_PRIMARY,                // RUN, WALK
        ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
        ACT_MP_RELOAD_STAND_PRIMARY_END,
        ACT_MP_RELOAD_CROUCH_PRIMARY,                // CROUCHWALK
        ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
        ACT_MP_RELOAD_CROUCH_PRIMARY_END,
        ACT_MP_RELOAD_SWIM_PRIMARY,
        ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
        ACT_MP_RELOAD_SWIM_PRIMARY_END,
        ACT_MP_RELOAD_AIRWALK_PRIMARY,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_END,

        ACT_MP_RELOAD_STAND_PRIMARY_2,
        ACT_MP_RELOAD_STAND_PRIMARY_LOOP_2,
        ACT_MP_RELOAD_STAND_PRIMARY_END_2,        
        ACT_MP_RELOAD_CROUCH_PRIMARY_2,        
        ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP_2,
        ACT_MP_RELOAD_CROUCH_PRIMARY_END_2,
        ACT_MP_RELOAD_SWIM_PRIMARY_2,
        ACT_MP_RELOAD_SWIM_PRIMARY_LOOP_2,
        ACT_MP_RELOAD_SWIM_PRIMARY_END_2,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_2,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP_2,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_END_2,

        // PRIMARY ALT
        ACT_MP_ATTACK_STAND_PRIMARY_ALT,
        ACT_MP_ATTACK_CROUCH_PRIMARY_ALT,
        ACT_MP_ATTACK_SWIM_PRIMARY_ALT,
        ACT_MP_RELOAD_STAND_PRIMARY_ALT,
        ACT_MP_RELOAD_CROUCH_PRIMARY_ALT,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_ALT,
        ACT_MP_RELOAD_STAND_PRIMARY_LOOP_ALT,
        ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP_ALT,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP_ALT,
        ACT_MP_RELOAD_STAND_PRIMARY_END_ALT,
        ACT_MP_RELOAD_CROUCH_PRIMARY_END_ALT,
        ACT_MP_RELOAD_AIRWALK_PRIMARY_END_ALT,
        ACT_MP_RELOAD_SWIM_PRIMARY_ALT,
        ACT_MP_ATTACK_STAND_PRIMARY_SUPER,
        ACT_MP_ATTACK_CROUCH_PRIMARY_SUPER,
        ACT_MP_ATTACK_SWIM_PRIMARY_SUPER,

        ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
        ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,

        // Secondary
        ACT_MP_STAND_SECONDARY,
        ACT_MP_CROUCH_SECONDARY,
        ACT_MP_RUN_SECONDARY,
        ACT_MP_WALK_SECONDARY,
        ACT_MP_AIRWALK_SECONDARY,
        ACT_MP_CROUCHWALK_SECONDARY,
        ACT_MP_JUMP_SECONDARY,
        ACT_MP_JUMP_START_SECONDARY,
        ACT_MP_JUMP_FLOAT_SECONDARY,
        ACT_MP_JUMP_LAND_SECONDARY,
        ACT_MP_SWIM_SECONDARY,

        ACT_MP_ATTACK_STAND_SECONDARY,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_SECONDARY,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_SECONDARY,
        ACT_MP_ATTACK_AIRWALK_SECONDARY,

        ACT_MP_RELOAD_STAND_SECONDARY,                // RUN, WALK
        ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
        ACT_MP_RELOAD_STAND_SECONDARY_END,
        ACT_MP_RELOAD_CROUCH_SECONDARY,                // CROUCHWALK
        ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
        ACT_MP_RELOAD_CROUCH_SECONDARY_END,
        ACT_MP_RELOAD_SWIM_SECONDARY,
        ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
        ACT_MP_RELOAD_SWIM_SECONDARY_END,
        ACT_MP_RELOAD_AIRWALK_SECONDARY,
        ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
        ACT_MP_RELOAD_AIRWALK_SECONDARY_END,

        ACT_MP_RELOAD_STAND_SECONDARY_2,
        ACT_MP_RELOAD_CROUCH_SECONDARY_2,
        ACT_MP_RELOAD_SWIM_SECONDARY_2,
        ACT_MP_RELOAD_AIRWALK_SECONDARY_2,

        ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
        ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,

        // Secondary2
        ACT_MP_STAND_SECONDARY2,
        ACT_MP_CROUCH_SECONDARY2,
        ACT_MP_RUN_SECONDARY2,
        ACT_MP_WALK_SECONDARY2,
        ACT_MP_AIRWALK_SECONDARY2,
        ACT_MP_CROUCHWALK_SECONDARY2,
        ACT_MP_JUMP_SECONDARY2,
        ACT_MP_JUMP_START_SECONDARY2,
        ACT_MP_JUMP_FLOAT_SECONDARY2,
        ACT_MP_JUMP_LAND_SECONDARY2,
        ACT_MP_SWIM_SECONDARY2,

        ACT_MP_ATTACK_STAND_SECONDARY2,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_SECONDARY2,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_SECONDARY2,
        ACT_MP_ATTACK_AIRWALK_SECONDARY2,

        ACT_MP_RELOAD_STAND_SECONDARY2,                // RUN, WALK
        ACT_MP_RELOAD_STAND_SECONDARY2_LOOP,
        ACT_MP_RELOAD_STAND_SECONDARY2_END,
        ACT_MP_RELOAD_CROUCH_SECONDARY2,                // CROUCHWALK
        ACT_MP_RELOAD_CROUCH_SECONDARY2_LOOP,
        ACT_MP_RELOAD_CROUCH_SECONDARY2_END,
        ACT_MP_RELOAD_SWIM_SECONDARY2,
        ACT_MP_RELOAD_SWIM_SECONDARY2_LOOP,
        ACT_MP_RELOAD_SWIM_SECONDARY2_END,
        ACT_MP_RELOAD_AIRWALK_SECONDARY2,
        ACT_MP_RELOAD_AIRWALK_SECONDARY2_LOOP,
        ACT_MP_RELOAD_AIRWALK_SECONDARY2_END,

        // Melee
        ACT_MP_STAND_MELEE,
        ACT_MP_CROUCH_MELEE,
        ACT_MP_RUN_MELEE,
        ACT_MP_WALK_MELEE,
        ACT_MP_AIRWALK_MELEE,
        ACT_MP_CROUCHWALK_MELEE,
        ACT_MP_JUMP_MELEE,
        ACT_MP_JUMP_START_MELEE,
        ACT_MP_JUMP_FLOAT_MELEE,
        ACT_MP_JUMP_LAND_MELEE,
        ACT_MP_SWIM_MELEE,

        ACT_MP_ATTACK_STAND_MELEE,                // RUN, WALK
        ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
        ACT_MP_ATTACK_CROUCH_MELEE,                // CROUCHWALK
        ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
        ACT_MP_ATTACK_SWIM_MELEE,
        ACT_MP_ATTACK_AIRWALK_MELEE,

        ACT_MP_ATTACK_STAND_GRENADE_MELEE,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
        ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,

        // Item1
        ACT_MP_STAND_ITEM1,
        ACT_MP_CROUCH_ITEM1,
        ACT_MP_RUN_ITEM1,
        ACT_MP_WALK_ITEM1,
        ACT_MP_AIRWALK_ITEM1,
        ACT_MP_CROUCHWALK_ITEM1,
        ACT_MP_JUMP_ITEM1,
        ACT_MP_JUMP_START_ITEM1,
        ACT_MP_JUMP_FLOAT_ITEM1,
        ACT_MP_JUMP_LAND_ITEM1,
        ACT_MP_SWIM_ITEM1,

        ACT_MP_ATTACK_STAND_ITEM1,                // RUN, WALK
        ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
        ACT_MP_ATTACK_CROUCH_ITEM1,                // CROUCHWALK
        ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
        ACT_MP_ATTACK_SWIM_ITEM1,
        ACT_MP_ATTACK_AIRWALK_ITEM1,

        ACT_MP_DEPLOYED_ITEM1,
        ACT_MP_DEPLOYED_IDLE_ITEM1,
        ACT_MP_CROUCHWALK_DEPLOYED_ITEM1,
        ACT_MP_CROUCH_DEPLOYED_IDLE_ITEM1,
        ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED_ITEM1,
        ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED_ITEM1,

        // Item2
        ACT_MP_STAND_ITEM2,
        ACT_MP_CROUCH_ITEM2,
        ACT_MP_RUN_ITEM2,
        ACT_MP_WALK_ITEM2,
        ACT_MP_AIRWALK_ITEM2,
        ACT_MP_CROUCHWALK_ITEM2,
        ACT_MP_JUMP_ITEM2,
        ACT_MP_JUMP_START_ITEM2,
        ACT_MP_JUMP_FLOAT_ITEM2,
        ACT_MP_JUMP_LAND_ITEM2,
        ACT_MP_SWIM_ITEM2,

        ACT_MP_ATTACK_STAND_ITEM2,                // RUN, WALK
        ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
        ACT_MP_ATTACK_CROUCH_ITEM2,                // CROUCHWALK
        ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
        ACT_MP_ATTACK_SWIM_ITEM2,
        ACT_MP_ATTACK_AIRWALK_ITEM2,

        ACT_MP_ATTACK_STAND_HARD_ITEM2,        
        ACT_MP_ATTACK_CROUCH_HARD_ITEM2,
        ACT_MP_ATTACK_SWIM_HARD_ITEM2,

        ACT_MP_DEPLOYED_ITEM2,
        ACT_MP_DEPLOYED_IDLE_ITEM2,
        ACT_MP_CROUCHWALK_DEPLOYED_ITEM2,
        ACT_MP_CROUCH_DEPLOYED_IDLE_ITEM2,
        ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED_ITEM2,
        ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED_ITEM2,

        ACT_MP_RELOAD_STAND_ITEM2,                // RUN, WALK
        ACT_MP_RELOAD_STAND_ITEM2_LOOP,
        ACT_MP_RELOAD_STAND_ITEM2_END,
        ACT_MP_RELOAD_CROUCH_ITEM2,                // CROUCHWALK
        ACT_MP_RELOAD_CROUCH_ITEM2_LOOP,
        ACT_MP_RELOAD_CROUCH_ITEM2_END,
        ACT_MP_RELOAD_SWIM_ITEM2,
        ACT_MP_RELOAD_SWIM_ITEM2_LOOP,
        ACT_MP_RELOAD_SWIM_ITEM2_END,
        ACT_MP_RELOAD_AIRWALK_ITEM2,
        ACT_MP_RELOAD_AIRWALK_ITEM2_LOOP,
        ACT_MP_RELOAD_AIRWALK_ITEM2_END,
        ACT_MP_RELOAD_NO_AMMO_ITEM2,

        ACT_MP_ATTACK_STAND_GRENADE_ITEM2,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_ITEM2,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_ITEM2,
        ACT_MP_ATTACK_AIRWALK_GRENADE_ITEM2,

        // Flinches
        ACT_MP_GESTURE_FLINCH,
        ACT_MP_GESTURE_FLINCH_PRIMARY,
        ACT_MP_GESTURE_FLINCH_SECONDARY,
        ACT_MP_GESTURE_FLINCH_MELEE,
        ACT_MP_GESTURE_FLINCH_ITEM1,
        ACT_MP_GESTURE_FLINCH_ITEM2,

        ACT_MP_GESTURE_FLINCH_HEAD,
        ACT_MP_GESTURE_FLINCH_CHEST,
        ACT_MP_GESTURE_FLINCH_STOMACH,
        ACT_MP_GESTURE_FLINCH_LEFTARM,
        ACT_MP_GESTURE_FLINCH_RIGHTARM,
        ACT_MP_GESTURE_FLINCH_LEFTLEG,
        ACT_MP_GESTURE_FLINCH_RIGHTLEG,

// Team Fortress specific - medic heal, medic infect, etc.....
        ACT_MP_GRENADE1_DRAW,
        ACT_MP_GRENADE1_IDLE,
        ACT_MP_GRENADE1_ATTACK,
        ACT_MP_GRENADE2_DRAW,
        ACT_MP_GRENADE2_IDLE,
        ACT_MP_GRENADE2_ATTACK,

        ACT_MP_PRIMARY_GRENADE1_DRAW,
        ACT_MP_PRIMARY_GRENADE1_IDLE,
        ACT_MP_PRIMARY_GRENADE1_ATTACK,
        ACT_MP_PRIMARY_GRENADE2_DRAW,
        ACT_MP_PRIMARY_GRENADE2_IDLE,
        ACT_MP_PRIMARY_GRENADE2_ATTACK,

        ACT_MP_SECONDARY_GRENADE1_DRAW,
        ACT_MP_SECONDARY_GRENADE1_IDLE,
        ACT_MP_SECONDARY_GRENADE1_ATTACK,
        ACT_MP_SECONDARY_GRENADE2_DRAW,
        ACT_MP_SECONDARY_GRENADE2_IDLE,
        ACT_MP_SECONDARY_GRENADE2_ATTACK,

        ACT_MP_MELEE_GRENADE1_DRAW,
        ACT_MP_MELEE_GRENADE1_IDLE,
        ACT_MP_MELEE_GRENADE1_ATTACK,
        ACT_MP_MELEE_GRENADE2_DRAW,
        ACT_MP_MELEE_GRENADE2_IDLE,
        ACT_MP_MELEE_GRENADE2_ATTACK,

        ACT_MP_ITEM1_GRENADE1_DRAW,
        ACT_MP_ITEM1_GRENADE1_IDLE,
        ACT_MP_ITEM1_GRENADE1_ATTACK,
        ACT_MP_ITEM1_GRENADE2_DRAW,
        ACT_MP_ITEM1_GRENADE2_IDLE,
        ACT_MP_ITEM1_GRENADE2_ATTACK,

        ACT_MP_ITEM2_GRENADE1_DRAW,
        ACT_MP_ITEM2_GRENADE1_IDLE,
        ACT_MP_ITEM2_GRENADE1_ATTACK,
        ACT_MP_ITEM2_GRENADE2_DRAW,
        ACT_MP_ITEM2_GRENADE2_IDLE,
        ACT_MP_ITEM2_GRENADE2_ATTACK,

        // Building
        ACT_MP_STAND_BUILDING,
        ACT_MP_CROUCH_BUILDING,
        ACT_MP_RUN_BUILDING,
        ACT_MP_WALK_BUILDING,
        ACT_MP_AIRWALK_BUILDING,
        ACT_MP_CROUCHWALK_BUILDING,
        ACT_MP_JUMP_BUILDING,
        ACT_MP_JUMP_START_BUILDING,
        ACT_MP_JUMP_FLOAT_BUILDING,
        ACT_MP_JUMP_LAND_BUILDING,
        ACT_MP_SWIM_BUILDING,

        ACT_MP_ATTACK_STAND_BUILDING,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_BUILDING,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_BUILDING,
        ACT_MP_ATTACK_AIRWALK_BUILDING,

        ACT_MP_ATTACK_STAND_GRENADE_BUILDING,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
        ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,

        // Building
        ACT_MP_STAND_BUILDING_DEPLOYED,
        ACT_MP_CROUCH_BUILDING_DEPLOYED,
        ACT_MP_RUN_BUILDING_DEPLOYED,
        ACT_MP_WALK_BUILDING_DEPLOYED,
        ACT_MP_AIRWALK_BUILDING_DEPLOYED,
        ACT_MP_CROUCHWALK_BUILDING_DEPLOYED,
        ACT_MP_JUMP_BUILDING_DEPLOYED,
        ACT_MP_JUMP_START_BUILDING_DEPLOYED,
        ACT_MP_JUMP_FLOAT_BUILDING_DEPLOYED,
        ACT_MP_JUMP_LAND_BUILDING_DEPLOYED,
        ACT_MP_SWIM_BUILDING_DEPLOYED,

        ACT_MP_ATTACK_STAND_BUILDING_DEPLOYED,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_BUILDING_DEPLOYED,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_BUILDING_DEPLOYED,
        ACT_MP_ATTACK_AIRWALK_BUILDING_DEPLOYED,

        ACT_MP_ATTACK_STAND_GRENADE_BUILDING_DEPLOYED,                // RUN, WALK
        ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING_DEPLOYED,                // CROUCHWALK
        ACT_MP_ATTACK_SWIM_GRENADE_BUILDING_DEPLOYED,
        ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING_DEPLOYED,

        ACT_MP_STAND_PDA,
        ACT_MP_CROUCH_PDA,
        ACT_MP_RUN_PDA,
        ACT_MP_WALK_PDA,
        ACT_MP_AIRWALK_PDA,
        ACT_MP_CROUCHWALK_PDA,
        ACT_MP_JUMP_PDA,
        ACT_MP_JUMP_START_PDA,
        ACT_MP_JUMP_FLOAT_PDA,
        ACT_MP_JUMP_LAND_PDA,
        ACT_MP_SWIM_PDA,

        ACT_MP_ATTACK_STAND_PDA,
        ACT_MP_ATTACK_SWIM_PDA,

        ACT_MP_STAND_LOSERSTATE,
        ACT_MP_CROUCH_LOSERSTATE,
        ACT_MP_RUN_LOSERSTATE,
        ACT_MP_WALK_LOSERSTATE,
        ACT_MP_AIRWALK_LOSERSTATE,
        ACT_MP_CROUCHWALK_LOSERSTATE,
        ACT_MP_JUMP_LOSERSTATE,
        ACT_MP_JUMP_START_LOSERSTATE,
        ACT_MP_JUMP_FLOAT_LOSERSTATE,
        ACT_MP_JUMP_LAND_LOSERSTATE,
        ACT_MP_SWIM_LOSERSTATE,
        ACT_MP_DOUBLEJUMP_LOSERSTATE,

        ACT_MP_DOUBLEJUMP_CROUCH,
        ACT_MP_DOUBLEJUMP_CROUCH_PRIMARY,
        ACT_MP_DOUBLEJUMP_CROUCH_SECONDARY,
        ACT_MP_DOUBLEJUMP_CROUCH_MELEE,
        ACT_MP_DOUBLEJUMP_CROUCH_ITEM1,
        ACT_MP_DOUBLEJUMP_CROUCH_ITEM2,
        ACT_MP_DOUBLEJUMP_CROUCH_LOSERSTATE,

        ACT_MP_GESTURE_VC_HANDMOUTH,
        ACT_MP_GESTURE_VC_FINGERPOINT,
        ACT_MP_GESTURE_VC_FISTPUMP,
        ACT_MP_GESTURE_VC_THUMBSUP,
        ACT_MP_GESTURE_VC_NODYES,
        ACT_MP_GESTURE_VC_NODNO,

        ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
        ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
        ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
        ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
        ACT_MP_GESTURE_VC_NODYES_PRIMARY,
        ACT_MP_GESTURE_VC_NODNO_PRIMARY,

        ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
        ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
        ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
        ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
        ACT_MP_GESTURE_VC_NODYES_SECONDARY,
        ACT_MP_GESTURE_VC_NODNO_SECONDARY,

        ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
        ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
        ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
        ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
        ACT_MP_GESTURE_VC_NODYES_MELEE,
        ACT_MP_GESTURE_VC_NODNO_MELEE,

        ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
        ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
        ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
        ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
        ACT_MP_GESTURE_VC_NODYES_ITEM1,
        ACT_MP_GESTURE_VC_NODNO_ITEM1,

        ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
        ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
        ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
        ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
        ACT_MP_GESTURE_VC_NODYES_ITEM2,
        ACT_MP_GESTURE_VC_NODNO_ITEM2,

        ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
        ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
        ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
        ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
        ACT_MP_GESTURE_VC_NODYES_BUILDING,
        ACT_MP_GESTURE_VC_NODNO_BUILDING,

        ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
        ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
        ACT_MP_GESTURE_VC_FISTPUMP_PDA,
        ACT_MP_GESTURE_VC_THUMBSUP_PDA,
        ACT_MP_GESTURE_VC_NODYES_PDA,
        ACT_MP_GESTURE_VC_NODNO_PDA,

        ACT_MP_STUN_BEGIN,
        ACT_MP_STUN_MIDDLE,
        ACT_MP_STUN_END,

        ACT_VM_UNUSABLE,
        ACT_VM_UNUSABLE_TO_USABLE,
        ACT_VM_USABLE_TO_UNUSABLE,

        // Specific viewmodel activities for weapon roles
        ACT_PRIMARY_VM_DRAW,
        ACT_PRIMARY_VM_HOLSTER,
        ACT_PRIMARY_VM_IDLE,
        ACT_PRIMARY_VM_PULLBACK,
        ACT_PRIMARY_VM_PRIMARYATTACK,
        ACT_PRIMARY_VM_SECONDARYATTACK,
        ACT_PRIMARY_VM_RELOAD,                        
        ACT_PRIMARY_RELOAD_START,                        
        ACT_PRIMARY_RELOAD_FINISH,                        
        ACT_PRIMARY_VM_DRYFIRE,                
        ACT_PRIMARY_VM_IDLE_TO_LOWERED,
        ACT_PRIMARY_VM_IDLE_LOWERED,
        ACT_PRIMARY_VM_LOWERED_TO_IDLE,
        ACT_PRIMARY_VM_RELOAD_2,
        ACT_PRIMARY_RELOAD_START_2,                
        ACT_PRIMARY_RELOAD_FINISH_2,
        ACT_PRIMARY_VM_RELOAD_3,
        ACT_PRIMARY_RELOAD_START_3,                
        ACT_PRIMARY_RELOAD_FINISH_3,
        ACT_PRIMARY_VM_PRIMARYATTACK_3,

        ACT_SECONDARY_VM_DRAW,
        ACT_SECONDARY_VM_HOLSTER,
        ACT_SECONDARY_VM_IDLE,
        ACT_SECONDARY_VM_PULLBACK,
        ACT_SECONDARY_VM_PRIMARYATTACK,
        ACT_SECONDARY_VM_SECONDARYATTACK,
        ACT_SECONDARY_VM_RELOAD,                        
        ACT_SECONDARY_RELOAD_START,
        ACT_SECONDARY_RELOAD_FINISH,
        ACT_SECONDARY_VM_RELOAD2,                        
        ACT_SECONDARY_VM_DRYFIRE,                
        ACT_SECONDARY_VM_IDLE_TO_LOWERED,
        ACT_SECONDARY_VM_IDLE_LOWERED,
        ACT_SECONDARY_VM_LOWERED_TO_IDLE,

        ACT_SECONDARY_VM_DRAW_2,
        ACT_SECONDARY_VM_IDLE_2,
        ACT_SECONDARY_VM_PRIMARYATTACK_2,
        ACT_SECONDARY_VM_RELOAD_2,

        ACT_MELEE_VM_DRAW,
        ACT_MELEE_VM_HOLSTER,
        ACT_MELEE_VM_IDLE,
        ACT_MELEE_VM_PULLBACK,
        ACT_MELEE_VM_PRIMARYATTACK,
        ACT_MELEE_VM_SECONDARYATTACK,
        ACT_MELEE_VM_RELOAD,                        
        ACT_MELEE_VM_DRYFIRE,                
        ACT_MELEE_VM_IDLE_TO_LOWERED,
        ACT_MELEE_VM_IDLE_LOWERED,
        ACT_MELEE_VM_LOWERED_TO_IDLE,
        ACT_MELEE_VM_STUN,
        ACT_MELEE_VM_HITCENTER,                
        ACT_MELEE_VM_SWINGHARD,

        ACT_PDA_VM_DRAW,
        ACT_PDA_VM_HOLSTER,
        ACT_PDA_VM_IDLE,
        ACT_PDA_VM_PULLBACK,
        ACT_PDA_VM_PRIMARYATTACK,
        ACT_PDA_VM_SECONDARYATTACK,
        ACT_PDA_VM_RELOAD,                        
        ACT_PDA_VM_DRYFIRE,                
        ACT_PDA_VM_IDLE_TO_LOWERED,
        ACT_PDA_VM_IDLE_LOWERED,
        ACT_PDA_VM_LOWERED_TO_IDLE,

        ACT_ENGINEER_PDA1_VM_DRAW,
        ACT_ENGINEER_PDA2_VM_DRAW,
        ACT_ENGINEER_BLD_VM_DRAW,
        ACT_ENGINEER_PDA1_VM_IDLE,
        ACT_ENGINEER_PDA2_VM_IDLE,
        ACT_ENGINEER_BLD_VM_IDLE,

        ACT_ITEM1_VM_DRAW,
        ACT_ITEM1_VM_HOLSTER,
        ACT_ITEM1_VM_IDLE,
        ACT_ITEM1_VM_IDLE_2,
        ACT_ITEM1_VM_PULLBACK,
        ACT_ITEM1_VM_PRIMARYATTACK,
        ACT_ITEM1_VM_SECONDARYATTACK,
        ACT_ITEM1_VM_RELOAD,                        
        ACT_ITEM1_VM_DRYFIRE,                
        ACT_ITEM1_VM_IDLE_TO_LOWERED,
        ACT_ITEM1_VM_IDLE_LOWERED,
        ACT_ITEM1_VM_LOWERED_TO_IDLE,
        ACT_ITEM1_RELOAD_START,                        
        ACT_ITEM1_RELOAD_FINISH,                        
        ACT_ITEM1_VM_HITCENTER,
        ACT_ITEM1_VM_SWINGHARD,
        ACT_ITEM1_BACKSTAB_VM_UP,
        ACT_ITEM1_BACKSTAB_VM_DOWN,
        ACT_ITEM1_BACKSTAB_VM_IDLE,
        ACT_MELEE_VM_ITEM1_STUN,

        ACT_ITEM2_VM_DRAW,
        ACT_ITEM2_VM_HOLSTER,
        ACT_ITEM2_VM_IDLE,
        ACT_ITEM2_VM_PULLBACK,
        ACT_ITEM2_VM_PRIMARYATTACK,
        ACT_ITEM2_VM_SECONDARYATTACK,
        ACT_ITEM2_VM_RELOAD,                        
        ACT_ITEM2_VM_DRYFIRE,                
        ACT_ITEM2_VM_IDLE_TO_LOWERED,
        ACT_ITEM2_VM_IDLE_LOWERED,
        ACT_ITEM2_VM_LOWERED_TO_IDLE,
        ACT_ITEM2_VM_CHARGE,
        ACT_ITEM2_VM_IDLE_2,
        ACT_ITEM2_VM_IDLE_3,
        ACT_ITEM2_VM_CHARGE_IDLE_3,
        ACT_ITEM2_VM_HITCENTER,
        ACT_ITEM2_VM_SWINGHARD,
        ACT_ITEM2_BACKSTAB_VM_UP,
        ACT_ITEM2_BACKSTAB_VM_DOWN,
        ACT_ITEM2_BACKSTAB_VM_IDLE,
        ACT_MELEE_VM_ITEM2_STUN,

        ACT_ITEM3_VM_DRAW,
        ACT_ITEM3_VM_HOLSTER,
        ACT_ITEM3_VM_IDLE,
        ACT_ITEM3_VM_PULLBACK,
        ACT_ITEM3_VM_PRIMARYATTACK,
        ACT_ITEM3_VM_SECONDARYATTACK,
        ACT_ITEM3_VM_RELOAD,                        
        ACT_ITEM3_VM_DRYFIRE,                
        ACT_ITEM3_VM_IDLE_TO_LOWERED,
        ACT_ITEM3_VM_IDLE_LOWERED,
        ACT_ITEM3_VM_LOWERED_TO_IDLE,
        ACT_ITEM3_VM_CHARGE,
        ACT_ITEM3_VM_IDLE_2,
        ACT_ITEM3_VM_IDLE_3,
        ACT_ITEM3_VM_CHARGE_IDLE_3,
        ACT_ITEM3_VM_HITCENTER,
        ACT_ITEM3_VM_SWINGHARD,

        ACT_SECONDARY2_VM_DRAW,
        ACT_SECONDARY2_VM_HOLSTER,
        ACT_SECONDARY2_VM_IDLE,
        ACT_SECONDARY2_VM_PULLBACK,
        ACT_SECONDARY2_VM_PRIMARYATTACK,
        ACT_SECONDARY2_VM_SECONDARY2ATTACK,
        ACT_SECONDARY2_VM_RELOAD,                        
        ACT_SECONDARY2_RELOAD_START,
        ACT_SECONDARY2_RELOAD_FINISH,
        ACT_SECONDARY2_VM_RELOAD2,                        
        ACT_SECONDARY2_VM_DRYFIRE,                
        ACT_SECONDARY2_VM_IDLE_TO_LOWERED,
        ACT_SECONDARY2_VM_IDLE_LOWERED,
        ACT_SECONDARY2_VM_LOWERED_TO_IDLE,

        ACT_BACKSTAB_VM_UP,
        ACT_BACKSTAB_VM_DOWN,
        ACT_BACKSTAB_VM_IDLE,

        ACT_PRIMARY_ATTACK_STAND_PREFIRE,
        ACT_PRIMARY_ATTACK_STAND_POSTFIRE,
        ACT_PRIMARY_ATTACK_STAND_STARTFIRE,
        ACT_PRIMARY_ATTACK_CROUCH_PREFIRE,
        ACT_PRIMARY_ATTACK_CROUCH_POSTFIRE,
        ACT_PRIMARY_ATTACK_SWIM_PREFIRE,
        ACT_PRIMARY_ATTACK_SWIM_POSTFIRE,

        ACT_SECONDARY_ATTACK_STAND_PREFIRE,
        ACT_SECONDARY_ATTACK_STAND_POSTFIRE,
        ACT_SECONDARY_ATTACK_STAND_STARTFIRE,
        ACT_SECONDARY_ATTACK_CROUCH_PREFIRE,
        ACT_SECONDARY_ATTACK_CROUCH_POSTFIRE,
        ACT_SECONDARY_ATTACK_SWIM_PREFIRE,
        ACT_SECONDARY_ATTACK_SWIM_POSTFIRE,

        ACT_MELEE_ATTACK_STAND_PREFIRE,
        ACT_MELEE_ATTACK_STAND_POSTFIRE,
        ACT_MELEE_ATTACK_STAND_STARTFIRE,
        ACT_MELEE_ATTACK_CROUCH_PREFIRE,
        ACT_MELEE_ATTACK_CROUCH_POSTFIRE,
        ACT_MELEE_ATTACK_SWIM_PREFIRE,
        ACT_MELEE_ATTACK_SWIM_POSTFIRE,

        ACT_ITEM1_ATTACK_STAND_PREFIRE,
        ACT_ITEM1_ATTACK_STAND_POSTFIRE,
        ACT_ITEM1_ATTACK_STAND_STARTFIRE,
        ACT_ITEM1_ATTACK_CROUCH_PREFIRE,
        ACT_ITEM1_ATTACK_CROUCH_POSTFIRE,
        ACT_ITEM1_ATTACK_SWIM_PREFIRE,
        ACT_ITEM1_ATTACK_SWIM_POSTFIRE,

        ACT_ITEM2_ATTACK_STAND_PREFIRE,
        ACT_ITEM2_ATTACK_STAND_POSTFIRE,
        ACT_ITEM2_ATTACK_STAND_STARTFIRE,
        ACT_ITEM2_ATTACK_CROUCH_PREFIRE,
        ACT_ITEM2_ATTACK_CROUCH_POSTFIRE,
        ACT_ITEM2_ATTACK_SWIM_PREFIRE,
        ACT_ITEM2_ATTACK_SWIM_POSTFIRE,

        ACT_MP_STAND_MELEE_ALLCLASS,
        ACT_MP_CROUCH_MELEE_ALLCLASS,
        ACT_MP_RUN_MELEE_ALLCLASS,
        ACT_MP_WALK_MELEE_ALLCLASS,
        ACT_MP_AIRWALK_MELEE_ALLCLASS,
        ACT_MP_CROUCHWALK_MELEE_ALLCLASS,
        ACT_MP_JUMP_MELEE_ALLCLASS,
        ACT_MP_JUMP_START_MELEE_ALLCLASS,
        ACT_MP_JUMP_FLOAT_MELEE_ALLCLASS,
        ACT_MP_JUMP_LAND_MELEE_ALLCLASS,
        ACT_MP_SWIM_MELEE_ALLCLASS,

        ACT_MP_ATTACK_STAND_MELEE_ALLCLASS,                // RUN, WALK
        ACT_MP_ATTACK_STAND_MELEE_SECONDARY_ALLCLASS,
        ACT_MP_ATTACK_CROUCH_MELEE_ALLCLASS,                // CROUCHWALK
        ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY_ALLCLASS,
        ACT_MP_ATTACK_SWIM_MELEE_ALLCLASS,
        ACT_MP_ATTACK_AIRWALK_MELEE_ALLCLASS,

        ACT_MELEE_ALLCLASS_VM_DRAW,
        ACT_MELEE_ALLCLASS_VM_HOLSTER,
        ACT_MELEE_ALLCLASS_VM_IDLE,
        ACT_MELEE_ALLCLASS_VM_PULLBACK,
        ACT_MELEE_ALLCLASS_VM_PRIMARYATTACK,
        ACT_MELEE_ALLCLASS_VM_SECONDARYATTACK,
        ACT_MELEE_ALLCLASS_VM_RELOAD,                        
        ACT_MELEE_ALLCLASS_VM_DRYFIRE,                
        ACT_MELEE_ALLCLASS_VM_IDLE_TO_LOWERED,
        ACT_MELEE_ALLCLASS_VM_IDLE_LOWERED,
        ACT_MELEE_ALLCLASS_VM_LOWERED_TO_IDLE,
        ACT_MELEE_ALLCLASS_VM_STUN,
        ACT_MELEE_ALLCLASS_VM_HITCENTER,                
        ACT_MELEE_ALLCLASS_VM_SWINGHARD,

        // BOMB activities for TD mode.
        ACT_MP_STAND_BOMB,
        ACT_MP_JUMP_START_BOMB,
        ACT_MP_JUMP_FLOAT_BOMB,
        ACT_MP_JUMP_LAND_BOMB,
        ACT_MP_RUN_BOMB,
        ACT_MP_SWIM_BOMB,

        // More Primary VM activities for Soldier Quake RL
        ACT_VM_DRAW_QRL,
        ACT_VM_IDLE_QRL,
        ACT_VM_PULLBACK_QRL,
        ACT_VM_PRIMARYATTACK_QRL,
        ACT_VM_RELOAD_QRL,
        ACT_VM_RELOAD_START_QRL,                        
        ACT_VM_RELOAD_FINISH_QRL,        

        // Third person anims for the Soldier Quake RL
        ACT_MP_RELOAD_STAND_PRIMARY3,
        ACT_MP_RELOAD_CROUCH_PRIMARY3,
        ACT_MP_RELOAD_AIRWALK_PRIMARY3,
        ACT_MP_RELOAD_STAND_PRIMARY3_LOOP,
        ACT_MP_RELOAD_CROUCH_PRIMARY3_LOOP,
        ACT_MP_RELOAD_AIRWALK_PRIMARY3_LOOP,
        ACT_MP_RELOAD_STAND_PRIMARY3_END,
        ACT_MP_RELOAD_CROUCH_PRIMARY3_END,
        ACT_MP_RELOAD_AIRWALK_PRIMARY3_END,
        ACT_MP_RELOAD_SWIM_PRIMARY3,

        // Throwable Animations
        ACT_MP_THROW,
        ACT_THROWABLE_VM_DRAW,
        ACT_THROWABLE_VM_IDLE,
        ACT_THROWABLE_VM_FIRE,

        // Spell Animations
        ACT_SPELL_VM_DRAW,
        ACT_SPELL_VM_IDLE, 
        ACT_SPELL_VM_ARM, 
        ACT_SPELL_VM_FIRE,

        // this is the end of the global activities, private per-monster activities start here.
        LAST_SHARED_ACTIVITY,
} Activity;


#endif // AI_ACTIVITY_H