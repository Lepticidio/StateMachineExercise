#pragma once
#include "Condition.h"
class Character;
class CooldownTimeCondition : public Condition
{
	float m_fMaxTime;
	Character* m_pOwner;
public:
	CooldownTimeCondition(Character* _pOwner, float _fMaxTime);
	bool  check()  const;
};

