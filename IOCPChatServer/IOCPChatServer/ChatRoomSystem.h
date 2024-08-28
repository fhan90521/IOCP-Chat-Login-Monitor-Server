#pragma once
#include "RoomSystem.h"
class ChatRoomSystem: public RoomSystem
{
private:
	class ChatServer* _chatServer = nullptr;
	void OnLeaveByChangingRoomSession(SessionInfo sessionInfo) override;
public:
	ChatRoomSystem(class ChatServer* chatServer);
	virtual void OnError(SessionInfo sessionInfo, RoomError error);
};