#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include "PathFollowingSteering.h"
#include "PursueSteering.h"
#include "AlignToMovement.h"
#include "PathFollowingSteering.h"


USVec2D RotateVector(USVec2D _vInitialVector, float _fAngle)
{
	return USVec2D(cos(_fAngle) * _vInitialVector.mX - sin(_fAngle) * _vInitialVector.mY, sin(_fAngle) * _vInitialVector.mX + cos(_fAngle) * _vInitialVector.mY);
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
		m_pPursueSteering = new PursueSteering(m_pArrive, this);
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
		vAcceleration = m_pPursueSteering->GetSteering();
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
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//m_pSeek->DrawDebug();
	m_pArrive->DrawDebug();
	//m_pPath->DrawDebug();
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(GetLoc(), GetLoc() + GetLinearVelocity());
}

void Character::SetPursuedCharacter(Character* _pPursued)
{ 
	m_pPursueSteering->SetTarget(_pPursued);
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
		self->SetPursuedCharacter(pToBePursued);
	}

	return 0;
}
	