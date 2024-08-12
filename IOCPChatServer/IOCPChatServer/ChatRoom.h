#pragma once
#include "Room.h"
#include <mutex>
#include <thread>
class ChatRoom :public Room
{
private:
	class ChatServer* _pServer=nullptr;
	LONG _ReqMsgCnt = 0;
	LONG _SendMsgCnt = 0;
	DWORD _onConnectCnt = 0;
	HashMap<SessionInfo::ID, class ChatSession*>_chatSessionMap;
	HashMap<INT64, class ChatPlayer*>_chatPlayerMap;
	List<class ChatPlayer*> _sectorMap[52][52];
	int _playerCnt = 0;
	void GetSessionInfoAroundSector(List<SessionInfo>& sessionInfoList, WORD sectorX, WORD sectorY);
	void OnEnter(SessionInfo sessionInfo) override;
	void OnLeave(SessionInfo sessionInfo) override;
	virtual void Update(float deltaTime) override;
	void OnLeaveRoomSystem(SessionInfo sessionInfo) override;
	int RequestEnter(SessionInfo sessionInfo) { return ENTER_SUCCESS; };
	void CheckHeartBeat();

public:
	void HeartBeatCS(SessionInfo sessionInfo);
	ChatRoom(class ChatServer* pServer);
	void ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& nickName);
	void ReqMessage(SessionInfo sessionInfo, INT64 accountNo, String& chatMessage);
	void SectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD nextX, WORD nextY);
	int GetPlayerCnt() { return _playerCnt; }
	int GetReqMsgCnt()
	{
		int ret = _ReqMsgCnt;
		_ReqMsgCnt = 0;
		return ret;
	}
	int GetSendMsgCnt()
	{
		int ret = _SendMsgCnt;
		_SendMsgCnt = 0;
		return ret;
	}
};