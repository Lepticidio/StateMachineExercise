#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include "PathFollowingSteering.h"
#include "PursueSteering.h"
#include "AlignToMovement.h"
#include "ArriveSteering.h"

#include "SM.h"
#include "ActionIdle.h"
#include "ActionPursue.h"
#include "ActionWindup.h"
#include "AndCondition.h"
#include "AttackAction.h"
#include "CanSeeEnemy.h"
#include "CooldownTimeCondition.h"
#include "NearCondition.h"
#include "NotCondition.h"
#include "OrCondition.h"
#include "OtherIsAliveCondition.h"

USVec2D Character::RotateVector(USVec2D _vInitialVector, float _fAngle)
{
	float fRadians = _fAngle / 57.2958f;
	return USVec2D(cos(fRadians) * _vInitialVector.mX - sin(fRadians) * _vInitialVector.mY, sin(fRadians) * _vInitialVector.mX + cos(fRadians) * _vInitialVector.mY);
}
float Character::AngleBetweenVectors(USVec2D _v0, USVec2D _v1)
{
	float fDot = _v0.Dot(_v1);
	fDot = (fDot < -1.0 ? -1.0 : (fDot > 1.0 ? 1.0 : fDot));
	float fAngle = acos(fDot);
	float fDegrees = fAngle* 57.2958f;
	return fDegrees;
}

Character::Character() : mLinearVelocity(00.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END
		m_pSeek = new SeekSteering(this);
		m_pArrive = new ArriveSteering(this);
		m_pAlign = new AlignSteering(this);
		m_pAlignToMovement = new AlignToMovement(this, m_pAlign);
		const char* sPathName = "path.xml";
		m_pPath = new Path(sPathName);
		m_pPathSteering = new PathFollowingSteering(m_pSeek, m_pPath, this);
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams(m_sParamsName.c_str(), mParams);
	m_pSeek->Initialize();
	m_pArrive->Initialize();
	m_pAlign->Initialize();
	m_pPathSteering->Initialize();
	m_vRandomPos = USVec2D(Rand() * 1024.0f - 512, Rand() * 768.0f - 384);
}

void Character::OnStop()
{

}


void Character::OnUpdate(float step)
{
	//USVec2D vAcceleration = m_pSeek->GetSteering(mParams.targetPosition); 
	//USVec2D vAcceleration = m_pArrive->GetSteering(mParams.targetPosition);
	
	m_fLastStep = step;
	USVec2D vAcceleration(0, 0);
	if (m_bIsEnemy)
	{
		m_fCurrentTime += step;
		if (m_fCurrentTime - m_fPreviousTime > m_fSecondsToChangeTarget)
		{
			m_vRandomPos = USVec2D(Rand() * 1024.0f - 512, Rand() * 768.0f - 384);
			m_fPreviousTime = m_fCurrentTime;
		}

		vAcceleration = m_pArrive->GetSteering(m_vRandomPos);
	}
	else
	{
		m_pSM->update();
	}
	if (m_fHealth <= 0)
	{
		m_fHealth = 0;
		SetImage(1);
		vAcceleration = USVec2D(0, 0);
		SetLinearVelocity(0, 0);
	}
	//USVec2D vAcceleration = m_pPathSteering->GetSteering();
	//USVec2D vAcceleration (0,0);
	USVec2D vCurrentVelocity = GetLinearVelocity() + vAcceleration * step;
	SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	SetLoc(GetLoc() + GetLinearVelocity()*step);

	//float fAngularAcceleration = m_pAlign->GetSteering(mParams.targetRotation);
	float fAngularAcceleration = m_pAlignToMovement->GetSteering();
	//float fAngularAcceleration = 0;
	float fCurrentAngularVelocity = GetAngularVelocity() + fAngularAcceleration;
	SetAngularVelocity(fCurrentAngularVelocity);
	float fAngleToSet = GetRot() + fCurrentAngularVelocity;
	while (fAngleToSet >= 360 || fAngleToSet < 0)
	{
		if (fAngleToSet >= 360)
		{
			fAngleToSet -= 360;
		}
		else if (fAngleToSet < 0)
		{
			fAngleToSet += 360;
		}

	}
	SetRot(fAngleToSet);

}

void Character::DrawDebug()
{
	//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//m_pSeek->DrawDebug();
	//m_pArrive->DrawDebug();
	//m_pPath->DrawDebug();
	//gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 0.5f);
	//MOAIDraw::DrawLine(GetLoc(), GetLoc() + GetLinearVelocity());
}
void Character::IncreaseTime()
{
	m_fCooldownTime = m_fCooldownTime + GetLastStep();
}


// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "checkIsEnemy",			_checkIsEnemy},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}

int Character::_checkIsEnemy(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	bool bIsEnemy = state.GetValue<bool>(2, 0.0f);
	self->SetIsEnemy(bIsEnemy);
	if (bIsEnemy)
	{
		self->SetParamsName("params_enemy.xml");
	}
	else
	{	
		Character* pToBePursued = state.GetLuaObject<Character>(3, 0.0f);
		self->SetParamsName("params_enemy.xml");
		//self->SetPursuedCharacter(pToBePursued);

		OtherIsAliveCondition* pOtherIsAlive = new OtherIsAliveCondition(pToBePursued);
		NotCondition* pOtherIsNotAlive = new NotCondition(pOtherIsAlive);

		State* idleState = new State();
		ActionIdle* idleAction = new ActionIdle(self);
		idleState->SetStateAction(idleAction);

		State* pursueState = new State();
		ActionPursue* pursueAction = new ActionPursue(self, pToBePursued);
		pursueState->SetStateAction(pursueAction);

		CanSeeEnemy* pCanSee = new CanSeeEnemy(self, pToBePursued);
		AndCondition* pCanSeeAndAlive = new AndCondition(pOtherIsAlive, pCanSee);
		Transition* pIdleToPursue = new Transition();
		pIdleToPursue->setCondition(pCanSeeAndAlive);
		pIdleToPursue->setTargetState(pursueState);
		idleState->AddTransition(pIdleToPursue);

		NotCondition* pCanNotSee = new NotCondition(pCanSee);
		OrCondition* pCanNotSeeOrNotAlive = new OrCondition(pCanNotSee, pOtherIsNotAlive);
		Transition* pPursueToIdle = new Transition();
		pPursueToIdle->setCondition(pCanNotSeeOrNotAlive);
		pPursueToIdle->setTargetState(idleState);
		pursueState->AddTransition(pPursueToIdle);

		State* pWindup = new State();
		ActionWindup* pWindupAction = new ActionWindup(self, pToBePursued);
		pWindup->SetStateAction(pWindupAction);

		State* pAttack = new State();
		AttackAction* pAttackAction = new AttackAction(self, pToBePursued);
		pAttack->SetStateAction(pAttackAction);

		NearCondition* pNear = new NearCondition(self, pToBePursued);
		AndCondition* pNearAndCanSee = new AndCondition(pNear, pCanSee);
		Transition* pAlertToWindup = new Transition();
		pAlertToWindup->setCondition(pNearAndCanSee);
		pAlertToWindup->setTargetState(pWindup);
		pursueState->AddTransition(pAlertToWindup);

		NotCondition* pNotNear = new NotCondition(pNear);
		OrCondition* pNotNearOrNotSee = new OrCondition(pNotNear, pCanNotSee);
		Transition* pAttackToAlert = new Transition();
		pAttackToAlert->setCondition(pNotNearOrNotSee);
		pAttackToAlert->setTargetState(pursueState);
		pWindup->AddTransition(pAttackToAlert);
		pAttack->AddTransition(pAttackToAlert);

		CooldownTimeCondition* pWindupCooldown = new CooldownTimeCondition(self, 0.5f);
		Transition* pWindupToAttack = new Transition();
		pWindupToAttack->setCondition(pWindupCooldown);
		pWindupToAttack->setTargetState(pAttack);
		pWindup->AddTransition(pWindupToAttack);

		CooldownTimeCondition* pAttackCooldown = new CooldownTimeCondition(self, 1.0f);
		Transition* pAttackToCooldown = new Transition();
		pAttackToCooldown->setCondition(pAttackCooldown);
		pAttackToCooldown->setTargetState(pWindup);
		pAttack->AddTransition(pAttackToCooldown);

		Transition* pAttackToIdle = new Transition();
		pAttackToIdle->setCondition(pOtherIsNotAlive);
		pAttackToIdle->setTargetState(idleState);
		pWindup->AddTransition(pAttackToIdle);
		pAttack->AddTransition(pAttackToIdle);


		SM* pDragonStateMachine = new SM();
		pDragonStateMachine->start(idleState);
		self->setSM(pDragonStateMachine);


	}

	return 0;
}
	