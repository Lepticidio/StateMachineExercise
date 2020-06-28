#include "stdafx.h"
#include "State.h"
void State::onEnter()
{
	if (m_enterAction != nullptr)
	{
		m_enterAction->start();
	}
	if (m_stateAction != nullptr)
	{
		m_stateAction->start();
	}
}
void State::update()
{
	if (m_stateAction != nullptr)
	{
		m_stateAction->update();
	}
}
void State::onExit()
{
	if (m_stateAction != nullptr)
	{
		m_stateAction->end();
	}
	if (m_exitAction != nullptr)
	{
		m_exitAction->start();
	}
}
const std::vector<Transition*>& State::getTransitions()
{
	return m_transitions;
}