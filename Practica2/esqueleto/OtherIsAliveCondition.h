#pragma once
#include "Condition.h"
class Character;
class OtherIsAliveCondition : public Condition
{
	Character* m_pOther;
public:
	OtherIsAliveCondition(Character* _pOther);
	bool  check()  const;
};
