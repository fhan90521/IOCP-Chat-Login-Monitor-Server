#include "ChatRoomSystem.h"
#include "ChatServer.h"
void ChatRoomSystem::OnLeaveByChangingRoomSession(SessionInfo sessionInfo)
{
}

ChatRoomSystem::ChatRoomSystem(class ChatServer* chatServer)
{
	_chatServer = chatServer;
}

void ChatRoomSystem::OnError(SessionInfo sessionInfo, RoomError error)
{
	_chatServer->Disconnect(sessionInfo);
}
