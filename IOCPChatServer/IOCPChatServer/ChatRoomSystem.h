#pragma once
#include "RoomSystem.h"
class ChatRoomSystem: public RoomSystem
{
private:
	void OnLeaveByChangingRoomSession(SessionInfo sessionInfo) override;
public:
	ChatRoomSystem(class ChatServer* pServer);
};