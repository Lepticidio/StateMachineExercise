#pragma once
#include "Condition.h"

class Character;
class CanSeeEnemy : public Condition
{
	float m_fMaxAngle;
	Character* m_pEnemy;
	Character* m_pOwner;
public:
	CanSeeEnemy(Character* _pOwner, Character* _pEnemy);
	bool  check()  const;
};
