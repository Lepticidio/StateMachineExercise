#pragma once
#include "Condition.h"
class NotCondition : public Condition
{
public:
	NotCondition(Condition* c1);
	bool check()  const override { return !m_c1->check(); }
private:
	Condition* m_c1;
};

