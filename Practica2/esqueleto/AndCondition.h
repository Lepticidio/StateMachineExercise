#pragma once
#include "Condition.h"
class AndCondition : Condition
{
public:
	AndCondition(Condition* c1, Condition* c2);
	bool check()  const override { return m_c1->check() && m_c2->check(); }
private:
	Condition* m_c1;
	Condition* m_c2;
};

