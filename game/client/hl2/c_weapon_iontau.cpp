// ----------------------------------------------------------------------------------
// Code written by Gareth Pugh, adds a sustained-fire laser weapon dubbed the Iontau.
// ----------------------------------------------------------------------------------
// This is the Client-side version of the code, modified slightly from the tutorial.
// ----------------------------------------------------------------------------------

#include "cbase.h"						// Mandatory include.
#include "beamdraw.h"					// Needed for beam drawing.
#include "c_basehlcombatweapon.h"		// Needed for BaseClass.
#include "c_weapon__stubs.h"			// Allows weapon to be networked.
#include "clienteffectprecachesystem.h"	// Precache client effect.
#include "decals.h"						// These two includes are needed for decal drawing.
#include "iefx.h"
#include "tier0/memdbgon.h"				// Last file to be included.

// ----------------------------------------------------------------------
// Declare a client effect register and precache the material to be used.
// ----------------------------------------------------------------------
CLIENTEFFECT_REGISTER_BEGIN(PrecacheEffectIontau)
CLIENTEFFECT_MATERIAL("sprites/bluelaser1") // The material choice is arbitrary.
CLIENTEFFECT_REGISTER_END()

// --------------------------------------
// The beam effect for the Iontau weapon.
// --------------------------------------
class C_IontauBeam : public CDefaultClientRenderable
{
public:
	C_IontauBeam(); // Constructor.

	void Update(C_BaseEntity* pOwner); // Update the render handle.
	void AddDecal(trace_t& tr);		   // Draw a decal at the end point.

	// This is needed for the beam drawing to work properly.
	matrix3x4_t z;
	const matrix3x4_t& RenderableToWorldTransform() { return z; }

	// Pretty much the same as the Physgun.
	virtual const Vector& GetRenderOrigin(void) { return m_worldPosition; }
	virtual const QAngle& GetRenderAngles(void) { return vec3_angle; }
	virtual bool ShouldDraw(void) { return true; }
	virtual bool IsTransparent(void) { return true; }
	virtual bool ShouldReceiveProjectedTextures(int flags) { return false; }
	virtual int DrawModel(int flags);

	virtual void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		mins.Init(-32, -32, -32);
		maxs.Init(32, 32, 32);
	}

	C_BaseEntity* m_pOwner;
	Vector m_targetPosition;
	Vector m_worldPosition;
	int m_active;
	int m_viewModelIndex;
};

// ---------------------------------------------------
// Defines the Client-side code for the Iontau weapon.
// Changed the BaseClass to a C_BaseHLCombatWeapon.
// ---------------------------------------------------
class C_WeaponIontau : public C_BaseHLCombatWeapon
{
	DECLARE_CLASS(C_WeaponIontau, C_BaseHLCombatWeapon);
public:
	C_WeaponIontau() {} // Constructor.
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();

	// --------------------------------
	// Called whenever data is changed.
	// --------------------------------
	void OnDataChanged(DataUpdateType_t updateType)
	{
		BaseClass::OnDataChanged(updateType);
		m_beam.Update(this); // Update the Iontau beam.
	}

private:
	C_WeaponIontau(const C_WeaponIontau&); // Constructor again?
	C_IontauBeam m_beam; // The Iontau beam.
};

STUB_WEAPON_CLASS_IMPLEMENT(weapon_iontau, C_WeaponIontau); // Link Client/Server classes.

// ----------------------------
// Add a Clientclass like this.
// ----------------------------
IMPLEMENT_CLIENTCLASS_DT(C_WeaponIontau, DT_WeaponIontau, CWeaponIontau)
// You can easily receive information from the Server like this.
RecvPropVector(RECVINFO_NAME(m_beam.m_targetPosition, m_targetPosition)),
RecvPropVector(RECVINFO_NAME(m_beam.m_worldPosition, m_worldPosition)),
RecvPropInt(RECVINFO_NAME(m_beam.m_active, m_active)),
RecvPropInt(RECVINFO_NAME(m_beam.m_viewModelIndex, m_viewModelIndex)),
END_RECV_TABLE()


// ------------
// Constructor.
// ------------
C_IontauBeam::C_IontauBeam()
{
	m_pOwner = NULL;
	m_hRenderHandle = INVALID_CLIENT_RENDER_HANDLE;
}

// --------------------------------------------------------------
// Update the render handle based off the weapon activity status.
// --------------------------------------------------------------
void C_IontauBeam::Update(C_BaseEntity* pOwner)
{
	m_pOwner = pOwner;
	if (m_active)
	{
		if (m_hRenderHandle == INVALID_CLIENT_RENDER_HANDLE)
			ClientLeafSystem()->AddRenderable(this, RENDER_GROUP_TRANSLUCENT_ENTITY);
		else
			ClientLeafSystem()->RenderableChanged(m_hRenderHandle);
	}
	else if (!m_active && m_hRenderHandle != INVALID_CLIENT_RENDER_HANDLE)
	{
		ClientLeafSystem()->RemoveRenderable(m_hRenderHandle);
		m_hRenderHandle = INVALID_CLIENT_RENDER_HANDLE;
	}
}

// --------------------------------------------
// Draws a decal at the end point of the trace.
// --------------------------------------------
void C_IontauBeam::AddDecal(trace_t& tr)
{
	C_BaseEntity* ent = cl_entitylist->GetEnt(0); // Get entity with index 0.
	if (ent != NULL)
	{
		int index = decalsystem->GetDecalIndexForName("RedGlowFade"); // Get the index of the RedGlowFade decal.
		if (index >= 0)
		{
			// -------------------------------------------------------
			// Randomize a Vector around the end point, then apply it.
			// -------------------------------------------------------
			Vector endPos;
			endPos.Random(-4.0f, 4.0f);
			endPos += tr.endpos;

			effects->DecalShoot(index, 0, ent->GetModel(), ent->GetAbsOrigin(), ent->GetAbsAngles(), endPos, 0, 0);
		}
	}
}

// ----------------------------------------
// Draw the beam when the weapon is active.
// ----------------------------------------
int C_IontauBeam::DrawModel(int flags)
{
	Vector points[3]; // Creates start, middle and end Vectors.
	QAngle tmpAngle;  // Stock angle.

	// -----------------------------------------------
	// If the weapon is inactive, don't draw the beam.
	// -----------------------------------------------
	if (!m_active)
		return 0;

	// --------------------------------------------------------
	// If we don't have a viewmodel index, don't draw the beam.
	// --------------------------------------------------------
	C_BaseEntity* pEnt = cl_entitylist->GetEnt(m_viewModelIndex);
	if (!pEnt)
		return 0;

	// ----------------------------------------
	// Set the positions of the points Vectors.
	// ----------------------------------------
	pEnt->GetAttachment(1, points[0], tmpAngle);

	points[1] = 0.5 * (m_targetPosition + points[0]);
	// a little noise 11t & 13t should be somewhat non-periodic looking
	points[1].z += 4 * sin(gpGlobals->curtime * 11) + 5 * cos(gpGlobals->curtime * 13);

	points[2] = m_worldPosition;

	// --------------------------------------------------
	// Perform a trace and draw a decal at the end point.
	// --------------------------------------------------
	trace_t tr;
	UTIL_TraceLine(points[0], points[2], MASK_SHOT, NULL, COLLISION_GROUP_NONE, &tr);
	AddDecal(tr);

	// -------------------------------------------------------
	// Find the beam material and specify a colour to give it.
	// -------------------------------------------------------
	IMaterial* pMat = materials->FindMaterial("sprites/bluelaser1", TEXTURE_GROUP_CLIENT_EFFECTS);
	Vector color;
	color.Init(0, 0, 1); // R, G, B so 0, 0, 1 will be completely blue.

	float scrollOffset = gpGlobals->curtime - (int)gpGlobals->curtime; // Creates beam scrolling.

	// --------------------------------------------------
	// Bind the material for rendering and draw the beam.
	// --------------------------------------------------
	CMatRenderContextPtr pRenderContext(materials);
	pRenderContext->Bind(pMat);

	DrawBeamQuadratic(points[0], points[1], points[2], 13, color, scrollOffset); // Width of 13 is arbitrary.

	return 1;
}