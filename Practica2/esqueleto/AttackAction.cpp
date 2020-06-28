#include "stdafx.h"
#include "AttackAction.h"
#include "character.h"

AttackAction::AttackAction(Character* _pOwner, Character* _pTarget) : m_pOwner(_pOwner), m_pTarget(_pTarget)
{
}
void AttackAction::start() const
{
	m_pOwner->SetImage(3);
	m_pTarget->TakeDamage(m_fDamage);
	m_pOwner->SetCooldownTime(0);
}
void AttackAction::update()const
{
	m_pOwner->IncreaseTime();

}
void AttackAction::end()const
{
}
