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
	
	static USVec2D RotateVector(USVec2D _vInitialVector, float _fAngle);
	static float AngleBetweenVectors(USVec2D _v0, USVec2D _v1);
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
private:
	float m_fPreviousTime = 0;
	float m_fCurrentTime = 0;
	USVec2D mLinearVelocity;
	USVec2D m_vRandomPos;
	float mAngularVelocity;
	float m_fTimeCounter;
	float m_fSecondsToChangeTarget = 5;
	float m_fLastStep;
	
	Params mParams;

	SeekSteering* m_pSeek;
	ArriveSteering* m_pArrive;
	AlignSteering* m_pAlign;
	AlignToMovement* m_pAlignToMovement;
	PathFollowingSteering* m_pPathSteering;
	Path* m_pPath;
	std::string m_sParamsName;
	bool m_bIsEnemy = false;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
	inline Params GetParams() { return mParams; };
	float GetLastStep() { return m_fLastStep; }
	ArriveSteering* GetArrive() { return m_pArrive; }
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _checkIsEnemy(lua_State* L);
};

#endif