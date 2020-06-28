#include "stdafx.h"
#include "ActionWindup.h"
#include "character.h"

ActionWindup::ActionWindup(Character* _pOwner) : m_pOwner(_pOwner)
{
}
void ActionWindup::start() const
{
	m_pOwner->SetImage(2);
	m_pOwner->SetCooldownTime(0);
}
void ActionWindup::update()const
{
	m_pOwner->IncreaseTime();
}
void ActionWindup::end()const
{
}