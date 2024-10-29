//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:     SuperShotgun - hand gun
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

#define SuperShotgun_FASTEST_REFIRE_TIME 0.1f
#define SuperShotgun_FASTEST_DRY_REFIRE_TIME 0.2f

#define SuperShotgun_ACCURACY_SHOT_PENALTY_TIME 0.2f // Applied amount of time each shot adds to the time we must recover from
#define SuperShotgun_ACCURACY_MAXIMUM_PENALTY_TIME 1.5f // Maximum penalty to deal out

ConVar SuperShotgun_use_new_accuracy("SuperShotgun_use_new_accuracy", "1");

//-----------------------------------------------------------------------------
// CWeaponSuperShotgun
//-----------------------------------------------------------------------------

class CWeaponSuperShotgun : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponSuperShotgun, CBaseHLCombatWeapon);

	CWeaponSuperShotgun(void);

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
		cone = VECTOR_CONE_10DEGREES; // ปรับการกระจายของกระสุนเป็น 10 องศา
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
	void PerformReload(void);
	float m_flSoonestPrimaryAttack;
	float m_flLastAttackTime;
	float m_flAccuracyPenalty;
	int m_nNumShotsFired;
	float m_flLastModeSwitchTime;
	bool m_bIsBurstMode; // สถานะการยิง burst fire
	int m_nBurstShotsRemaining; // จำนวนกระสุนที่เหลือใน burst fire

	// ตัวแปร Burst Fire
	bool m_bIsBurstFiring;
};


IMPLEMENT_SERVERCLASS_ST(CWeaponSuperShotgun, DT_WeaponSuperShotgun)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_SuperShotgun, CWeaponSuperShotgun);
PRECACHE_WEAPON_REGISTER(weapon_SuperShotgun);

BEGIN_DATADESC(CWeaponSuperShotgun)

DEFINE_FIELD(m_flSoonestPrimaryAttack, FIELD_TIME),
DEFINE_FIELD(m_flLastAttackTime, FIELD_TIME),
DEFINE_FIELD(m_flAccuracyPenalty, FIELD_FLOAT), // NOTENOTE: This is NOT tracking game time
DEFINE_FIELD(m_nNumShotsFired, FIELD_INTEGER),

END_DATADESC()

acttable_t CWeaponSuperShotgun::m_acttable[] =
{
	{ ACT_IDLE, ACT_IDLE_SUPERSHOTGUN, true },
	{ ACT_IDLE_ANGRY, ACT_IDLE_ANGRY_SUPERSHOTGUN, true },
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_SUPERSHOTGUN, true },
	{ ACT_RELOAD, ACT_RELOAD_SUPERSHOTGUN, true },
	{ ACT_WALK_AIM, ACT_WALK_AIM_SUPERSHOTGUN, true },
	{ ACT_RUN_AIM, ACT_RUN_AIM_SUPERSHOTGUN, true },
	{ ACT_GESTURE_RANGE_ATTACK1, ACT_GESTURE_RANGE_ATTACK_SUPERSHOTGUN, true },
	{ ACT_RELOAD_LOW, ACT_RELOAD_SUPERSHOTGUN_LOW, false },
	{ ACT_RANGE_ATTACK1_LOW, ACT_RANGE_ATTACK_SUPERSHOTGUN_LOW, false },
	{ ACT_COVER_LOW, ACT_COVER_SUPERSHOTGUN_LOW, false },
	{ ACT_RANGE_AIM_LOW, ACT_RANGE_AIM_SUPERSHOTGUN_LOW, false },
	{ ACT_GESTURE_RELOAD, ACT_GESTURE_RELOAD_SUPERSHOTGUN, false },
	{ ACT_WALK, ACT_WALK_SUPERSHOTGUN, false },
	{ ACT_RUN, ACT_RUN_SUPERSHOTGUN, false },
};

IMPLEMENT_ACTTABLE(CWeaponSuperShotgun);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------

CWeaponSuperShotgun::CWeaponSuperShotgun(void)
{
	m_flSoonestPrimaryAttack = gpGlobals->curtime;
	m_flAccuracyPenalty = 0.0f;
	m_flLastModeSwitchTime = 0.0f;
	m_bIsBurstMode = false;

	m_fMinRange1 = 24;
	m_fMaxRange1 = 1500;
	m_fMinRange2 = 24;
	m_fMaxRange2 = 200;

	m_bFiresUnderwater = true;
}



//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::Precache(void)
{
	BaseClass::Precache();
	UTIL_PrecacheOther("grenade_ar2");
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
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
void CWeaponSuperShotgun::DryFire(void)
{
	WeaponSound(EMPTY);
	SendWeaponAnim(ACT_VM_DRYFIRE);

	m_flSoonestPrimaryAttack = gpGlobals->curtime + 1.0f; // Adjust as necessary
	m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::PrimaryAttack(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	Vector vecSrc = pOwner->Weapon_ShootPosition();
	Vector vecAiming = pOwner->GetAutoaimVector(AUTOAIM_5DEGREES);

	FireBulletsInfo_t info;
	info.m_vecSrc = vecSrc;
	info.m_vecDirShooting = vecAiming;
	info.m_iShots = 12; // ยิงกระสุน 12 นัดในแต่ละครั้ง
	info.m_vecSpread = GetBulletSpread();
	info.m_flDistance = MAX_TRACE_LENGTH;
	info.m_iAmmoType = m_iPrimaryAmmoType;
	info.m_flDamage = 15.0f; // ปรับความเสียหายต่อกระสุนแต่ละนัด

	pOwner->FireBullets(info);

	WeaponSound(SINGLE);
	pOwner->ViewPunch(QAngle(-8, 0, 0)); // เพิ่มแรง recoil
	m_iClip1 -= 2; // ลดจำนวนกระสุน 2 นัด (สามารถปรับให้ลดมากกว่านี้ได้หากต้องการ)

	m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate() + 0.5f; // หน่วงเวลาหลังจากยิง

	SendWeaponAnim(ACT_VM_PRIMARYATTACK);
	pOwner->SetAnimation(PLAYER_ATTACK1);
}






//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::UpdatePenaltyTime(void)
{
	// Do nothing for grenade
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::ItemPreFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemPreFrame();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::ItemBusyFrame(void)
{
	UpdatePenaltyTime();

	BaseClass::ItemBusyFrame();
}

//-----------------------------------------------------------------------------
// Purpose: Allows firing as fast as button is pressed
//-----------------------------------------------------------------------------
#include "util.h"

void CWeaponSuperShotgun::ItemPostFrame(void)
{
	BaseClass::ItemPostFrame();

	if (m_bInReload)
		return;

	CBasePlayer* pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	// ตรวจสอบการกดคลิกขวาเพื่อสลับโหมด
	if (pOwner->m_nButtons & IN_ATTACK2)
	{
		if (gpGlobals->curtime - m_flLastModeSwitchTime > 0.3f) // ป้องกันการสลับโหมดบ่อยเกินไป
		{
			m_bIsBurstMode = !m_bIsBurstMode; // สลับโหมดการยิง

			// แสดงข้อความที่กลางหน้าจอ
			if (m_bIsBurstMode)
			{
				ClientPrint(pOwner, HUD_PRINTTALK, "Burst Fire Mode Activated");
			}
			else
			{
				ClientPrint(pOwner, HUD_PRINTTALK, "Single Fire Mode Activated");
			}

			m_flLastModeSwitchTime = gpGlobals->curtime; // อัพเดตเวลาเมื่อสลับโหมด
		}
	}

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
Activity CWeaponSuperShotgun::GetPrimaryAttackActivity(void)
{
	return ACT_VM_PRIMARYATTACK;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponSuperShotgun::Reload(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return false;

	// ตรวจสอบว่าต้องรีโหลดจริงหรือไม่
	if (m_iClip1 < GetMaxClip1() && pOwner->GetAmmoCount(m_iPrimaryAmmoType) > 0)
	{
		// เพิ่ม delay ก่อนการ reload
		float flReloadDelay = 0.5f; // ระยะเวลา delay ก่อนการ reload
		m_flNextPrimaryAttack = gpGlobals->curtime + flReloadDelay;
		m_flNextSecondaryAttack = gpGlobals->curtime + flReloadDelay;

		// ตั้งเวลาสำหรับการเริ่ม animation reload
		SetWeaponIdleTime(gpGlobals->curtime + flReloadDelay);

		// เสียงการ reload
		WeaponSound(RELOAD);

		// เรียกใช้ DefaultReload หลังจาก delay
		return DefaultReload(GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD);
	}

	return false;
}






//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSuperShotgun::AddViewKick(void)
{
	// Do nothing for grenade
}