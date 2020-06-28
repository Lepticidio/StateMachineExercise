#pragma once
#include "Action.h"
class Character;
class PursueSteering;
class ActionPursue : public Action
{
	Character* m_pOwner;
	PursueSteering* m_pPursueSteering;
public:
	ActionPursue(Character* _pOwner, Character* _pTarget);
	void start() const;
	void update() const;
	void end() const;
};

