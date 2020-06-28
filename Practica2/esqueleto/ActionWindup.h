#pragma once
#include "Action.h"
class Character;
class PursueSteering;
class ActionWindup : public Action
{
	float m_fWindupTime = 0.5f;
	Character* m_pOwner;
	PursueSteering* m_pPursueSteering;
public:
	ActionWindup(Character* _pOwner, Character* _pTarget);
	void start() const;
	void update() const;
	void end() const;
};

