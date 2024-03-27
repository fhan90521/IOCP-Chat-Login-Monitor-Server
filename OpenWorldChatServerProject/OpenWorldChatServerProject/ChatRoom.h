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
	LONG _RecvMsgCnt = 0;
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
	void ReqLogin(SessionInfo _sessionInfo, INT64	_accountNo, Array<WCHAR, 20> _id, Array<WCHAR, 20> _nickName, Array<char, 64>	_sessionKey);
	int GetPlayerCnt() { return _playerCnt; }
};