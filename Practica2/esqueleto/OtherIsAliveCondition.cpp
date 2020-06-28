#include "stdafx.h"
#include "OtherIsAliveCondition.h"
#include "character.h"

OtherIsAliveCondition::OtherIsAliveCondition(Character* _pOther) : m_pOther(_pOther)
{
}
bool  OtherIsAliveCondition::check()  const
{
	return m_pOther->GetHealth() > 0;
}