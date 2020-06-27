#include "SM.h"
void SM::start()
{
	m_currentState = m_initialState;
	m_currentState->onEnter();

}
void SM::update()
{
	m_currentState->update();
	const std::vector<Transition>& trans = m_currentState->getTransitions();
	for each (Transition tran in trans)
	{
		if (tran.canTrigger())
		{
			m_currentState->onExit();
			State* nextState = tran.trigger();
			nextState->onEnter();
			m_currentState = nextState;
			return;
		}
	}
}