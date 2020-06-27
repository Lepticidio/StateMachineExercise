#pragma once
#include <vector>
#include "Transition.h"
class State
{
	Action* m_enterAction;
	Action* m_exitAction;
	Action* m_stateAction;
	std::vector<Transition> m_transitions;
public:
	void onEnter();
	void update();
	void onExit();
	const std::vector<Transition>& getTransitions();

};

