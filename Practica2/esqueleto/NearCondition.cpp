#include "stdafx.h"
#include "NearCondition.h"
#include "character.h"

NearCondition::NearCondition(Character* _pOwner, Character* _pOther) : m_pOwner(_pOwner), m_pOther(_pOther)
{
	m_fMinDistance = 75;
}
bool  NearCondition::check()  const
{
	float fDistance = (m_pOwner->GetLoc() - m_pOther->GetLoc()).Length();
	return  fDistance < m_fMinDistance;
}