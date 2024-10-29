//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:     StickyBomb - hand gun
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "basehlcombatweapon.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "gamerules.h"
#include "in_buttons.h"
#include "soundent.h"
#include "game.h"
#include "vstdlib/random.h"
#include "gamestats.h"
#include "grenade_ar2.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define StickyBomb_FASTEST_REFIRE_TIME 0.1f
#define StickyBomb_FASTEST_DRY_REFIRE_TIME 0.2f

#define StickyBomb_ACCURACY_SHOT_PENALTY_TIME 0.2f // Applied amount of time each shot adds to the time we must recover from
#define StickyBomb_ACCURACY_MAXIMUM_PENALTY_TIME 1.5f // Maximum penalty to deal out

ConVar StickyBomb_use_new_accuracy("StickyBomb_use_new_accuracy", "1");

//-----------------------------------------------------------------------------
// CWeaponStickyBomb
//-----------------------------------------------------------------------------

class CWeaponStickyBomb : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponStickyBomb, CBaseHLCombatWeapon);

	CWeaponStickyBomb(void);

	DECLARE_SERVERCLASS();

	void Precache(void);
	void ItemPostFrame(void);
	void ItemPreFrame(void);
	void ItemBusyFrame(void);
	void PrimaryAttack(void);
	void AddViewKick(void);
	void DryFire(void);
	void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

	void UpdatePenaltyTime(void);

	int CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }
	Activity GetPrimaryAttackActivity(void);

	virtual bool Reload(void);

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone;
		return cone;
	}

	virtual int GetMinBurst()
	{
		return 1;
	}

	virtual int GetMaxBurst()
	{
		return 1;
	}

	virtual float GetFireRate(void)
	{
		return 1.0f; // Adjust fire rate as necessary
	}

	DECLARE_ACTTABLE();

private:
	float m_flSoonestPrimaryAttack;
	float m_flLastAttackTime;
	float m_flAccuracyPenalty;
	int m_nNumShotsFired;
};

IMPLEMENT_SERVERCLASS_ST(CWeaponStickyBomb, DT_WeaponStickyBomb)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_StickyBomb, CWeaponStickyBomb);
PRECACHE_WEAPON_REGISTER(weapon_StickyBomb);

BEGIN_DATADESC(CWeaponStickyBomb)

DEFINE_FIELD(m_flSoonestPrimaryAttack, FIELD_TIME),
DEFINE_FIELD(m_flLastAttackTime, FIELD_TIME),
DEFINE_FIELD(m_flAccuracyPenalty, FIELD_FLOAT), // NOTENOTE: This is NOT tracking game time
DEFINE_FIELD(m_nNumShotsFired, FIELD_INTEGER),

END_DATADESC()

acttable_t CWeaponStickyBomb::m_acttable[] =
{
	{ ACT_IDLE, ACT_IDLE_PISTOL, true },
	{ ACT_IDLE_ANGRY, ACT_IDLE_ANGRY_PISTOL, true },
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_PISTOL, true },
	{ ACT_RELOAD, ACT_RELOAD_PISTOL, true },
	{ ACT_WALK_AIM, ACT_WALK_AIM_PISTOL, true },
	{ ACT_RUN_AIM, ACT_RUN_AIM_PISTOL, true },
	{ ACT_GESTURE_RANGE_ATTACK1, ACT_GESTURE_RANGE_ATTACK_PISTOL, true },
	{ ACT_RELOAD_LOW, ACT_RELOAD_PISTOL_LOW, false },
	{ ACT_RANGE_ATTACK1_LOW, ACT_RANGE_ATTACK_PISTOL_LOW, false },
	{ ACT_COVER_LOW, ACT_COVER_PISTOL_LOW, false },
	{ ACT_RANGE_AIM_LOW, ACT_RANGE_AIM_PISTOL_LOW, false },
	{ ACT_GESTURE_RELOAD, ACT_GESTURE_RELOAD_PISTOL, false },
	{ ACT_WALK, ACT_WALK_PISTOL, false },
	{ ACT_RUN, ACT_RUN_PISTOL, false },
};

IMPLEMENT_ACTTABLE(CWeaponStickyBomb);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponStickyBomb::CWeaponStickyBomb(void)
{
	m_flSoonestPrimaryAttack = gpGlobals->curtime;
	m_flAccuracyPenalty = 0.0f;

	m_fMinRange1 = 24;
	m_fMaxRange1 = 1500;
	m_fMinRange2 = 24;
	m_fMaxRange2 = 200;

	m_bFiresUnderwater = true;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::Precache(void)
{
	BaseClass::Precache();
	UTIL_PrecacheOther("grenade_ar2");
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
	switch (pEvent->event)
	{
	case EVENT_WEAPON_PISTOL_FIRE:
	{
		// No grenade firing for NPCs
		BaseClass::Operator_HandleAnimEvent(pEvent, pOperator);
	}
	break;
	default:
		BaseClass::Operator_HandleAnimEvent(pEvent, pOperator);
		break;
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::DryFire(void)
{
	WeaponSound(EMPTY);
	SendWeaponAnim(ACT_VM_DRYFIRE);

	m_flSoonestPrimaryAttack = gpGlobals->curtime + 1.0f; // Adjust as necessary
	m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::PrimaryAttack(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	Vector vecSrc = pOwner->Weapon_ShootPosition();
	Vector vecThrow;
	pOwner->EyeVectors(&vecThrow);

	// Create grenade
	CGrenadeAR2* pGrenade = (CGrenadeAR2*)Create("grenade_ar2", vecSrc, vec3_angle, pOwner);
	if (pGrenade)
	{
		pGrenade->SetAbsVelocity(vecThrow * 1000); // Adjust speed as necessary
		pGrenade->SetLocalAngularVelocity(RandomAngle(-400, 400)); // Add some spin for realism
		pGrenade->SetThrower(pOwner);
		pGrenade->SetOwnerEntity(pOwner);
		pGrenade->SetDamage(100.0f); // Adjust damage as necessary
	}

	WeaponSound(SINGLE);
	pOwner->ViewPunch(QAngle(-2, 0, 0));
	m_iClip1--;

	SendWeaponAnim(ACT_VM_PRIMARYATTACK);
	pOwner->SetAnimation(PLAYER_ATTACK1);

	m_flNextPrimaryAttack = gpGlobals->curtime + 1.0f; // Adjust fire rate as necessary
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::UpdatePenaltyTime(void)
{
	// Do nothing for grenade
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::ItemPreFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemPreFrame();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::ItemBusyFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemBusyFrame();
}

//-----------------------------------------------------------------------------
// Purpose: Allows firing as fast as button is pressed
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::ItemPostFrame(void)
{
	BaseClass::ItemPostFrame();

	if (m_bInReload)
		return;

	CBasePlayer* pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	// Allow a refire as fast as the player can click
	if (((pOwner->m_nButtons & IN_ATTACK) == false) && (m_flSoonestPrimaryAttack < gpGlobals->curtime))
	{
		m_flNextPrimaryAttack = gpGlobals->curtime - 0.1f;
	}
	else if ((pOwner->m_nButtons & IN_ATTACK) && (m_flNextPrimaryAttack < gpGlobals->curtime) && (m_iClip1 <= 0))
	{
		DryFire();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : int
//-----------------------------------------------------------------------------
Activity CWeaponStickyBomb::GetPrimaryAttackActivity(void)
{
	return ACT_VM_PRIMARYATTACK;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponStickyBomb::Reload(void)
{
	bool fRet = DefaultReload(GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD);
	if (fRet)
	{
		WeaponSound(RELOAD);
		m_flAccuracyPenalty = 0.0f;
	}
	return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponStickyBomb::AddViewKick(void)
{
	// Do nothing for grenade
}