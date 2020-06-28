#pragma once
#include "Action.h"
class Character;
class ActionWindup : public Action
{
	float m_fWindupTime = 0.5f;
	Character* m_pOwner;
public:
	ActionWindup(Character* _pOwner);
	void start() const;
	void update() const;
	void end() const;
};

