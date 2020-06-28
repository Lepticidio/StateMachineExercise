#include "stdafx.h"
#include "ActionIdle.h"
#include "character.h"
ActionIdle::ActionIdle(Character* _pOwner) : m_pOwner(_pOwner)
{
}
void ActionIdle::start() const
{
	m_pOwner->SetImage(0);
}
void ActionIdle::update() const
{
}
void ActionIdle::end() const
{
}