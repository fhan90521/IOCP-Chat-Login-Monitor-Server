#pragma once
#include "Session.h"
struct Remotable
{
	SessionInfo _sessionInfo;
	ULONGLONG _prevHeartBeat;
	ULONGLONG _timeOutInterval;
	Remotable(SessionInfo sessionInfo, ULONGLONG curTime, ULONGLONG timeOutInterval)
	{
		_sessionInfo = sessionInfo;
		_prevHeartBeat = curTime;
		_timeOutInterval = timeOutInterval;
	}
	Remotable()
	{ 
		_sessionInfo.id = 0;
		_prevHeartBeat = 0;
		_timeOutInterval = 0;
	}
	void SetTimeOut(ULONGLONG timeOutInterval)
	{
		_timeOutInterval = timeOutInterval;
	}
	bool isTimeOut(ULONGLONG curTime)
	{
		if (curTime - _prevHeartBeat > _timeOutInterval)
		{
			return true;
		}
		return false;
	}
};