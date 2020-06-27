#include "stdafx.h"
#include "AlignSteering.h"

float AlignSteering::GetSteering(float _fTarget)
{
	float fResult = 0;
	float fCurrentAngle = m_pChararacter->GetRot();
	while (_fTarget >= 360 || _fTarget < 0)
	{
		if (_fTarget >= 360)
		{
			_fTarget -= 360;
		}
		else if (_fTarget < 0)
		{
			_fTarget += 360;
		}

	}

	float fAlternateAngle = _fTarget - 360;

	if (abs(fCurrentAngle - fAlternateAngle) < abs(fCurrentAngle - _fTarget))
	{
		_fTarget = fAlternateAngle;
	}
	m_fDesiredAngle = _fTarget - fCurrentAngle;
	float fDistance = abs(m_fDesiredAngle);
	float fDistanceFactor = 1;
	if (fDistance > 0)
	{
		if (fDistance < m_pChararacter->GetParams().angular_arrive_radius)
		{
			fDistanceFactor = fDistance / m_pChararacter->GetParams().angular_arrive_radius;
		}
		m_fDesiredAngle = (m_fDesiredAngle / fDistance) * m_fMaxSpeed * fDistanceFactor;

		fResult = m_fDesiredAngle - m_pChararacter->GetAngularVelocity();
		float fAbsResult = abs(fResult);
		if (fAbsResult > m_fMaxAcceleration)
		{
			fResult = (fResult / fAbsResult) * m_fMaxAcceleration;
		}
		m_fAngularAcceleration = fResult;

	}
	return fResult;
}

void AlignSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();


}

AlignSteering::AlignSteering(Character* _pCharacter) : m_pChararacter(_pCharacter)
{
}
void AlignSteering::Initialize()
{
	m_fMaxSpeed = m_pChararacter->GetParams().max_angular_velocity;
	m_fMaxAcceleration = m_pChararacter->GetParams().max_angular_acceleration;
	printf("");
}