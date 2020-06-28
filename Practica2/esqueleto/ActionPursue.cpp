#include "stdafx.h"
#include "ActionPursue.h"
#include "character.h"
#include "PursueSteering.h"

ActionPursue::ActionPursue(Character* _pOwner, Character* _pTarget) : m_pOwner(_pOwner)
{
	m_pPursueSteering = new PursueSteering(m_pOwner->GetArrive(), m_pOwner);
	m_pPursueSteering->SetTarget(_pTarget);
}
void ActionPursue::start()
{
	m_pOwner->SetImage(1);
}
void ActionPursue::update()
{
	USVec2D vAcceleration = m_pPursueSteering->GetSteering();

	//USVec2D vAcceleration = m_pPathSteering->GetSteering();
	//USVec2D vAcceleration (0,0);
	USVec2D vCurrentVelocity = m_pOwner->GetLinearVelocity() + vAcceleration * m_pOwner->GetLastStep();
	m_pOwner->SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	m_pOwner->SetLoc(m_pOwner->GetLoc() + m_pOwner->GetLinearVelocity() * m_pOwner->GetLastStep());
}
