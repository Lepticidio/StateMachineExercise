#include "Transition.h"
#include "State.h"
#include <stdafx.h>
bool Transition::canTrigger() 
{
	return m_condition->check();
}
State* Transition::trigger()
{
	m_triggerAction->start();
	return m_targetState;
}