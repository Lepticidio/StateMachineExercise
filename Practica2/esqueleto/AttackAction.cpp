#include "stdafx.h"
#include "AttackAction.h"
#include "character.h"

AttackAction::AttackAction(Character* _pOwner, Character* _pTarget) : m_pOwner(_pOwner), m_pTarget(_pTarget)
{
}
void AttackAction::start() const
{
	m_pOwner->SetImage(3);
}
void AttackAction::update()const
{
	m_pOwner->IncreaseTime();
	if (m_pOwner->GetCooldownTime() > m_fAttackTime)
	{
		m_pTarget->TakeDamage(m_fDamage);
	}

}
void AttackAction::end()const
{
}
