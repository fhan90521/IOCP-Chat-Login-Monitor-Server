#include "ChatRoomSystem.h"
#include "ChatServer.h"
void ChatRoomSystem::OnLeaveByChangingRoomSession(SessionInfo sessionInfo)
{
}

ChatRoomSystem::ChatRoomSystem(ChatServer* pServer):RoomSystem(pServer)
{
}
