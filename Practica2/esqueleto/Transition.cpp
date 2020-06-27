#include "Transition.h"
bool Transition::canTrigger() const
{
	return m_condition->check();
}
State* Transition::trigger()
{
	m_triggerAction->start();
	return m_targetState;
}