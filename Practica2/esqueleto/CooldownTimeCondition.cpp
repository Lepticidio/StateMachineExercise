#include "stdafx.h"
#include "CooldownTimeCondition.h"
#include "character.h"

CooldownTimeCondition::CooldownTimeCondition(Character* _pOwner, float _fMaxTime) : m_pOwner(_pOwner), m_fMaxTime(_fMaxTime)
{
}
bool  CooldownTimeCondition::check()  const
{
	return m_pOwner->GetCooldownTime() >= m_fMaxTime;
}