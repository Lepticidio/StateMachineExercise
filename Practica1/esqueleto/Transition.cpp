#include "stdafx.h"
#include "Transition.h"
#include "State.h"
bool Transition::canTrigger() 
{
	return m_condition->check();
}
State* Transition::trigger()
{
	if (m_triggerAction != nullptr)
	{
		m_triggerAction->start();
	}
	return m_targetState;
}