#include "stdafx.h"
#include "State.h"
void State::onEnter()
{
	m_enterAction->start();
	m_stateAction->start();
}
void State::update()
{
	m_stateAction->update();
}
void State::onExit()
{
	m_stateAction->end();
	m_exitAction->start();
}
const std::vector<Transition*>& State::getTransitions()
{
	return m_transitions;
}