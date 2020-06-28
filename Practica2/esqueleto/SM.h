#pragma once
#include <vector>
#include "State.h"
class SM
{
	std::vector<State*> m_States;
	State* m_currentState;
public:
	void load();
	void start(State* _pInitialState);
	void update();
};

