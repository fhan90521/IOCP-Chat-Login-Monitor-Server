#pragma once
#include "JobQueue.h"
#include "Remotable.h"
class ChatRoom :public JobQueue
{
private:
	class ChatServer* _pServer=nullptr;
	virtual void OnEnter(SessionInfo sessionInfo);
	virtual void OnLeave(SessionInfo sessionInfo);
	LONG _ReqMsgCnt = 0;
	LONG _SendMsgCnt = 0;
	DWORD _onConnectCnt = 0;
	HashMap<SessionInfo::ID, class Player*>_playerMap;
	HashMap<INT64, class Player*>_accountNoMap;
	HashMap<SessionInfo::ID, Remotable>_guestMap;
	List<Player*> _sectorMap[52][52];
	int _playerCnt = 0;
	void GetSessionInfoAroundSector(List<SessionInfo>& sessionInfoList, WORD sectorX, WORD sectorY);
public:
	ChatRoom(class ChatServer* pServer);
	void EnterRoom(SessionInfo sessionInfo);
	void LeaveRoom(SessionInfo sessionInfo);
	void ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20> id, Array<WCHAR, 20> nickName);
	void ReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char> msg);
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