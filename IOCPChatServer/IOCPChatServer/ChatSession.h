#pragma once
#include "Session.h"
enum class SessionType
{
	Guest,
	Player
};
struct ChatSession
{
	SessionType sessionType;
	SessionInfo sessionInfo;
	ULONG64 lastRecvTime = 0;
	class ChatPlayer* pPlayer = nullptr;
};