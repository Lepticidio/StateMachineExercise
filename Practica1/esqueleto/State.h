#pragma once
#include <vector>
#include "Transition.h"
class State
{
	Action* m_enterAction;
	Action* m_exitAction;
	Action* m_stateAction;
	std::vector<Transition*> m_transitions;
public:
	void onEnter();
	void update();
	void onExit();
	const std::vector<Transition*>& getTransitions();
	void SetEnterAction(Action* _pAction) { m_enterAction = _pAction; };
	void SetExitAction(Action* _pAction) { m_exitAction = _pAction; };
	void SetStateAction(Action* _pAction) { m_stateAction = _pAction; };
	void AddTransition(Transition* _pTransition) { m_transitions.push_back(_pTransition);  };


};

