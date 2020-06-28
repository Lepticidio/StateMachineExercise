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
	void setCondition(Condition* _pCondition) { m_condition = _pCondition; };
	void setTargetState(State* _pState) { m_targetState = _pState; };
	void setTriggerAction(Action* _pAction) { m_triggerAction = _pAction; };

};

