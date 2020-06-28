#pragma once
#include "Action.h"
#include <stdafx.h>
class Character;
class ActionIdle : public Action
{
	Character* m_pOwner;
public:
	ActionIdle(Character* _pOwner);
	void start();

};

