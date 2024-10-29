//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//

#ifndef WEAPON_COMBAT_H
#define WEAPON_COMBAT_H

#include "basebludgeonweapon.h"

#if defined( _WIN32 )
#pragma once
#endif

#ifdef HL2MP
#error weapon_COMBAT.h must not be included in hl2mp. The windows compiler will use the wrong class elsewhere if it is.
#endif

#define	COMBAT_RANGE	75.0f
#define	COMBAT_REFIRE	0.4f

//-----------------------------------------------------------------------------
// CWeaponCOMBAT
//-----------------------------------------------------------------------------

class CWeaponCOMBAT : public CBaseHLBludgeonWeapon
{
public:
	DECLARE_CLASS(CWeaponCOMBAT, CBaseHLBludgeonWeapon);

	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();

	CWeaponCOMBAT();

	float		GetRange(void)		{ return	COMBAT_RANGE; }
	float		GetFireRate(void)		{ return	COMBAT_REFIRE; }

	void		AddViewKick(void);
	float		GetDamageForActivity(Activity hitActivity);

	virtual int WeaponMeleeAttack1Condition(float flDot, float flDist);
	void		SecondaryAttack(void)	{ return; }

	// Animation event
	virtual void Operator_HandleAnimEvent(animevent_t *pEvent, CBaseCombatCharacter *pOperator);

private:
	// Animation event handlers
	void HandleAnimEventMeleeHit(animevent_t *pEvent, CBaseCombatCharacter *pOperator);
};

#endif // WEAPON_COMBAT_H
