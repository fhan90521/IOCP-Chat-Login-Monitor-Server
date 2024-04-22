#pragma once
#include "Room.h"
#include "Remotable.h"
class ChatRoom :public Room
{
private:
	class ChatServer* _pServer=nullptr;
	virtual void Update() override {} ;
	virtual void OnEnter(SessionInfo sessionInfo) override;
	virtual int RequestEnter(SessionInfo sessionInfo) override;
	virtual void OnLeave(SessionInfo sessionInfo) override;
	LONG _updateCnt = 0;
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
	ChatRoom(class ChatServer* pServer) :_pServer(pServer) {};
	void ReqLogin(SessionInfo _sessionInfo, INT64	_accountNo, Array<WCHAR, 20> _id, Array<WCHAR, 20> _nickName);
	void ReqMessage(SessionInfo _sessionInfo, INT64 _accountNo, Vector<char> _msg);
	void SectorMove(SessionInfo _sessionInfo, INT64 _accountNo, WORD _nextX, WORD _nextY);
	void HeartBeat(SessionInfo _sessionInfo);
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