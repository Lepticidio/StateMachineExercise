#include "stdafx.h"
#include "ActionWindup.h"
#include "character.h"
#include "PursueSteering.h"


ActionWindup::ActionWindup(Character* _pOwner, Character* _pTarget) : m_pOwner(_pOwner)
{
	m_pPursueSteering = new PursueSteering(m_pOwner->GetArrive(), m_pOwner);
	m_pPursueSteering->SetTarget(_pTarget);
}
void ActionWindup::start() const
{
	m_pOwner->SetImage(2);
	m_pOwner->SetCooldownTime(0);
}
void ActionWindup::update()const
{
	m_pOwner->IncreaseTime();
	USVec2D vAcceleration = m_pPursueSteering->GetSteering();
	USVec2D vCurrentVelocity = m_pOwner->GetLinearVelocity() + vAcceleration * m_pOwner->GetLastStep();
	m_pOwner->SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	m_pOwner->SetLoc(m_pOwner->GetLoc() + m_pOwner->GetLinearVelocity() * m_pOwner->GetLastStep());
}
void ActionWindup::end()const
{
}