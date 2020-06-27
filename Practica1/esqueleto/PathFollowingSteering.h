#pragma once
#include "SeekSteering.h"
#include "Path.h"
class PathFollowingSteering
{
protected:
	int m_iCurrentPoint = 0;
	float m_fLookAhead = 0;
	float m_fTimeAhead = 0;
	float m_fDestinationRadius = 0;
	Character* m_pCharacter;
public:
	SeekSteering* m_pSeek;
	Path* m_pPath;
	PathFollowingSteering(SeekSteering* _pSeek, Path* _pPath, Character* _pCharacter);
	USVec2D GetSteering();
	void Initialize();
};

