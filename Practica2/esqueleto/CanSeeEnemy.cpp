
#include "stdafx.h"
#include "CanSeeEnemy.h"
#include "character.h"

CanSeeEnemy::CanSeeEnemy(Character* _pOwner, Character* _pEnemy) : m_pOwner(_pOwner), m_pEnemy(_pEnemy)
{
	m_fMaxAngle = 90;
}
bool  CanSeeEnemy::check()  const
{
	USVec2D vDirEnemy = m_pEnemy->GetLoc() - m_pOwner->GetLoc();
	USVec2D vForward = Character::RotateVector(USVec2D(1, 0), m_pOwner->GetRot());
	float fAngle = Character::AngleBetweenVectors(vDirEnemy, vForward);
	printf("Angle: %f \n",fAngle);
	if (fAngle < m_fMaxAngle || fAngle > 360 - m_fMaxAngle)
	{
		return true;
	}
	else
	{
		return false;
	}
	return true;
}