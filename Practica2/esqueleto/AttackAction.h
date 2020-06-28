#pragma once
#include "Action.h"
class Character;
class PursueSteering;
class AttackAction : public Action
{
	float m_fAttackTime = 1;
	float m_fDamage = 40;
	Character* m_pOwner;
	Character* m_pTarget;
	PursueSteering* m_pPursueSteering;
public:
	AttackAction(Character* _pOwner, Character* _pTarget);
	void start() const;
	void update() const;
	void end() const;
};

