#include "ActionIdle.h"
#include "character.h"
#include <stdafx.h>
ActionIdle::ActionIdle(Character* _pOwner) : m_pOwner(_pOwner)
{
}
void ActionIdle::start()
{
	m_pOwner->SetImage(0);
}