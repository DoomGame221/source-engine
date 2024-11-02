// ----------------------------------------------------------------------------------
// Code written by Gareth Pugh, adds a sustained-fire laser weapon dubbed the Iontau.
// ----------------------------------------------------------------------------------
// This is the Server-side version of the code, modified slightly from the tutorial.
// ----------------------------------------------------------------------------------

#include "cbase.h"				// Mandatory include.
#include "basehlcombatweapon.h"	// Needed for BaseClass.
#include "ammodef.h"			// Needed for weapon damage.
#include "in_buttons.h"			// What buttons are being pressed?
#include "tier0/memdbgon.h"		// Last file to be included.

#define IONTAU_AMMO_RATE 0.2						// Ammo consumption rate.
#define IONTAU_BEAM_SPRITE "sprites/bluelaser1.vmt"	// Material to be used for beam drawing.
#define IONTAU_ATTACK_RATE 0.0625f					// Delay between damage calls.
static int g_iontauBeam;							// Index of the beam material.

// ---------------------------------------------------
// Defines the Server-side code for the Iontau weapon.
// Changed the BaseClass to a CBaseHLCombatWeapon.
// ---------------------------------------------------
class CWeaponIontau : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CWeaponIontau, CBaseHLCombatWeapon);
	CWeaponIontau();			// Constructor.
	void Spawn(void);			// What happens when the weapon is created?
	void Precache(void);		// Initialize any materials that will be used.
	void PrimaryAttack(void);	// What happens when LMB is pressed?
	void WeaponIdle(void);		// Called when nothing is happening.
	void ItemPostFrame(void);	// Gets called every frame.

	// Called when the player switches weapons.
	virtual bool Holster(CBaseCombatWeapon* pSwitchingTo)
	{
		m_active = false;
		return BaseClass::Holster(pSwitchingTo);
	}

	void EffectUpdate(void); // Update important variables.
	void AddViewKick(void);	 // Add some recoil when the weapon is fired.
	DECLARE_SERVERCLASS();

protected:
	CNetworkVector(m_targetPosition);	// Midway point.
	CNetworkVector(m_worldPosition);	// End point.
	CNetworkVar(int, m_active);			// Is the weapon firing?
	CNetworkVar(int, m_viewModelIndex);	// entindex of the weapon.
	float m_flNextAttackTime;			// When is the next attack?
};

// --------------------------------
// Declare a Serverclass like this.
// --------------------------------
IMPLEMENT_SERVERCLASS_ST(CWeaponIontau, DT_WeaponIontau)
// You can use SENDINFO_NAME like this.
SendPropVector(SENDINFO_NAME(m_targetPosition, m_targetPosition), -1, SPROP_COORD),
SendPropVector(SENDINFO_NAME(m_worldPosition, m_worldPosition), -1, SPROP_COORD),

// Or simply SENDINFO like this.
SendPropInt(SENDINFO(m_active), 1, SPROP_UNSIGNED),
SendPropModelIndex(SENDINFO(m_viewModelIndex)),
END_SEND_TABLE()


LINK_ENTITY_TO_CLASS(weapon_iontau, CWeaponIontau);
PRECACHE_WEAPON_REGISTER(weapon_iontau);

// -----------------------------
// Declare a Datadesc like this.
// -----------------------------
BEGIN_DATADESC(CWeaponIontau)
DEFINE_FIELD(m_active, FIELD_INTEGER),
DEFINE_FIELD(m_viewModelIndex, FIELD_INTEGER),
DEFINE_FIELD(m_targetPosition, FIELD_POSITION_VECTOR),
DEFINE_FIELD(m_worldPosition, FIELD_POSITION_VECTOR),
DEFINE_FIELD(m_flNextAttackTime, FIELD_TIME),
END_DATADESC()

// -----------------------------------------------------------------
// Constructor, can pass through some stock values to our variables.
// -----------------------------------------------------------------
CWeaponIontau::CWeaponIontau(void)
{
	m_active = false;
	m_targetPosition = vec3_origin;
	m_worldPosition = vec3_origin;
	m_flNextAttackTime = 0;
}

// ----------------------
// Entity spawning stuff.
// ----------------------
void CWeaponIontau::Spawn(void)
{
	BaseClass::Spawn();
	FallInit(); // Fall to the ground.
}

// --------------------------
// Initialize materials here.
// --------------------------
void CWeaponIontau::Precache(void)
{
	BaseClass::Precache();
	g_iontauBeam = PrecacheModel(IONTAU_BEAM_SPRITE); // The material choice is arbitrary.
}

// -------------------------------------------------------------
// Update our variables here, then pass them over to the Client.
// -------------------------------------------------------------
void CWeaponIontau::EffectUpdate(void)
{
	m_active = true;
	Vector start, forward, right, up; // Create some useful Vectors.
	trace_t tr;						  // Needed for tracing stuff.

	// ----------------------------------------------------------
	// Try and find the player, bail out if they cannot be found!
	// ----------------------------------------------------------
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	// ------------------------------------------
	// If we have a viewmodel, acquire its index.
	// ------------------------------------------
	m_viewModelIndex = pOwner->entindex();
	CBaseViewModel* vm = pOwner->GetViewModel();
	if (vm)
		m_viewModelIndex = vm->entindex();

	// ---------------------------------------------------
	// Update the Vectors based off the player's position.
	// ---------------------------------------------------
	pOwner->EyeVectors(&forward, &right, &up);
	start = pOwner->Weapon_ShootPosition();
	Vector aimDir = pOwner->GetAutoaimVector(AUTOAIM_5DEGREES); // 5 degrees is arbitrary.
	Vector end = start + forward * 4096; // 4096 world units is arbitrary.
	VectorVectors(aimDir, right, up);

	// -----------------------------------------
	// Perform a trace and update our variables.
	// -----------------------------------------
	UTIL_TraceLine(start, end, MASK_SHOT, pOwner, COLLISION_GROUP_NONE, &tr);
	end = m_worldPosition = tr.endpos;		 // Set the end point Vectors to be the same thing.
	m_targetPosition = start + forward * 25; // A scale factor of 25 is arbitrary.

	// --------------------------
	// Damage will be dealt here!
	// --------------------------
	ClearMultiDamage();
	CBaseEntity* pHit = tr.m_pEnt;

	if (m_flNextAttackTime < gpGlobals->curtime)
	{
		// If we hit something, inflict damage upon it.
		if (pHit != NULL)
		{
			CTakeDamageInfo dmgInfo(this, pOwner, 3, DMG_SHOCK); // 3 shock damage is arbitrary.
			CalculateBulletDamageForce(&dmgInfo, m_iPrimaryAmmoType, aimDir, tr.endpos);
			pHit->DispatchTraceAttack(dmgInfo, aimDir, &tr);
		}

		// If we hit something that wasn't the skybox, create an impact effect.
		if (tr.DidHitWorld() && !(tr.surface.flags & SURF_SKY))
		{
			UTIL_ImpactTrace(&tr, GetAmmoDef()->DamageType(m_iPrimaryAmmoType), "ImpactGauss");
			CPVSFilter filter(tr.endpos);
			te->GaussExplosion(filter, 0.0f, tr.endpos, tr.plane.normal, 0);
		}

		ApplyMultiDamage();

		// ----------------------------------------
		// Apply recoil and pushback to the player.
		// ----------------------------------------
		Vector recoilForce = pOwner->BodyDirection2D() * -(2 * 10.0f);
		recoilForce[2] += 5.0f;

		pOwner->ApplyAbsVelocityImpulse(recoilForce);
		AddViewKick();
		m_flNextAttackTime = gpGlobals->curtime + IONTAU_ATTACK_RATE;
	}
}

// -------------------------
// Affect the player's view.
// -------------------------
void CWeaponIontau::AddViewKick(void)
{
	// You will see something like this quite often in the code for weapons!
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	// ---------------------------------------------------------
	// Randomize a view punch value then apply it to the player.
	// ---------------------------------------------------------
	QAngle viewPunch;
	viewPunch.x = random->RandomFloat(-0.4f, 0.4f); // -0.4 to 0.4 is arbitrary.
	viewPunch.y = random->RandomFloat(-0.4f, 0.4f);
	viewPunch.z = 0; // Don't apply any z-axis view punch.

	pPlayer->ViewPunch(viewPunch);
}

// ----------------------------------------------------------------
// Executes when the Left Mouse Button (or +attack key) is pressed.
// ----------------------------------------------------------------
void CWeaponIontau::PrimaryAttack(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	if (pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 0)
	{
		m_active = true; // ให้ยังคงยิงได้แม้กระสุนหมด
	}
	else
	{
		if (!m_active)
		{
			SendWeaponAnim(ACT_VM_PULLBACK);
			pOwner->SetAnimation(PLAYER_ATTACK1);
			m_active = true;
		}
		else
			EffectUpdate();
	}

	if (m_flNextPrimaryAttack < gpGlobals->curtime)
	{
		// pOwner->RemoveAmmo(1, m_iPrimaryAmmoType); // ไม่ลดจำนวนกระสุน
		WeaponSound(SINGLE);
		AddViewKick();
		m_flNextPrimaryAttack = gpGlobals->curtime + IONTAU_AMMO_RATE;
	}
}


// -------------------------------------------
// Play an idle animation and become inactive.
// -------------------------------------------
void CWeaponIontau::WeaponIdle(void)
{
	SendWeaponAnim(ACT_VM_IDLE);
	if (m_active)
		m_active = false;
}

// ----------------------------------------------------
// Check to see if we should be allowed to fire or not.
// ----------------------------------------------------
void CWeaponIontau::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	if (pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 0 || (pOwner->m_afButtonReleased & IN_ATTACK))
	{
		m_active = false;
		WeaponIdle();
		return;
	}

	if (pOwner->m_nButtons & IN_ATTACK)
		PrimaryAttack();
	else
	{
		WeaponIdle();
		return;
	}
}