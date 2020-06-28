#pragma once
#include "Condition.h"
class Character;
class NearCondition : public Condition
{
	float m_fMinDistance;
	Character* m_pOther;
	Character* m_pOwner;
public:
	NearCondition(Character* _pOwner, Character* _pOther);
	bool  check()  const;
};

