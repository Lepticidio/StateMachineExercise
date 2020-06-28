#pragma once
#include "Action.h"
class Character;
class AttackAction : public Action
{
	float m_fAttackTime = 1;
	float m_fDamage = 40;
	Character* m_pOwner;
	Character* m_pTarget;
public:
	AttackAction(Character* _pOwner, Character* _pTarget);
	void start() const;
	void update() const;
	void end() const;
};

