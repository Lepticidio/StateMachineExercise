#pragma once
#include <vector>
#include "State.h"
class SM
{
	std::vector<State*> m_States;
	State* m_currentState,* m_initialState;
public:
	void load();
	void start();
	void update();
};

