#pragma once
#include "Condition.h"
#include "Action.h"
class State;
class Transition
{
	Condition* m_condition;
	State* m_targetState;
	Action* m_triggerAction;
public:
	bool canTrigger() const;
	State* trigger();

};

