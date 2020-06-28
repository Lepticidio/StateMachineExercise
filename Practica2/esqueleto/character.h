#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class SeekSteering;
class ArriveSteering;
class AlignSteering;
class AlignToMovement;
class PathFollowingSteering;
class Path;
class SM;
class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	void SetParamsName(std::string _sName) { m_sParamsName = _sName;}
	void SetIsEnemy(bool _bIsEnemy) { m_bIsEnemy = _bIsEnemy;}
	void SetCooldownTime(float _fNewValue) { m_fCooldownTime = _fNewValue; }
	void TakeDamage(float _fAmount) { m_fHealth -= _fAmount; }
	void IncreaseTime();
	
	static USVec2D RotateVector(USVec2D _vInitialVector, float _fAngle);
	static float AngleBetweenVectors(USVec2D _v0, USVec2D _v1);
	float GetCooldownTime() { return m_fCooldownTime; }
	float GetHealth() { return m_fHealth; }
	float GetAngularVelocity() const { return mAngularVelocity;}
	USVec2D GetLinearVelocity() const { return mLinearVelocity; }
private:
	bool m_bIsEnemy = false;
	float m_fPreviousTime = 0;
	float m_fCurrentTime = 0;
	float mAngularVelocity;
	float m_fTimeCounter;
	float m_fSecondsToChangeTarget = 5;
	float m_fLastStep;
	float m_fHealth = 100;
	float m_fCooldownTime = 100;
	USVec2D mLinearVelocity;
	USVec2D m_vRandomPos;
	std::string m_sParamsName;
	Params mParams;
	SeekSteering* m_pSeek;
	ArriveSteering* m_pArrive;
	AlignSteering* m_pAlign;
	AlignToMovement* m_pAlignToMovement;
	PathFollowingSteering* m_pPathSteering;
	Path* m_pPath;
	SM* m_pSM;
	
	// Lua configuration
public:
	void setSM(SM* _pSM) { m_pSM = _pSM; };
	virtual void RegisterLuaFuncs(MOAILuaState& state);
	float GetLastStep() { return m_fLastStep; }
	ArriveSteering* GetArrive() { return m_pArrive; }
	inline Params GetParams() { return mParams; };
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _checkIsEnemy(lua_State* L);
};

#endif