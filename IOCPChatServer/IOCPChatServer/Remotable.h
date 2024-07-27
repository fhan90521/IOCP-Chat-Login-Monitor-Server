#pragma once
#include "Session.h"
struct Remotable
{
	SessionInfo sessionInfo;
	ULONGLONG prevHeartBeat;
	ULONGLONG timeOutInterval;
	Remotable(SessionInfo sessionInfo, ULONGLONG curTime, ULONGLONG timeOutInterval)
	{
		sessionInfo = sessionInfo;
		prevHeartBeat = curTime;
		timeOutInterval = timeOutInterval;
	}
	Remotable()
	{ 
		sessionInfo.id = 0;
		prevHeartBeat = 0;
		timeOutInterval = 0;
	}
	void SetTimeOut(ULONGLONG Interval)
	{
		timeOutInterval = Interval;
	}
	bool isTimeOut(ULONGLONG curTime)
	{
		if (curTime - prevHeartBeat > timeOutInterval)
		{
			return true;
		}
		return false;
	}
};