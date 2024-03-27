#pragma once
#include "IOCPServer.h"
#include "ChatServerStub.h"
#include "ChatServerProxy.h"
#include "Player.h"
#include "Job.h"
#include "Session.h"
#include "NetworkHeader.h"
#include <process.h>
#include "PerformanceMonitor.h"
#define DEFAULT_SECTOR 55
class ChatServer : public IOCPServer, public ChatServerStub, public ChatServerProxy
{
public:
	ChatServer();
	~ChatServer();
	void Run() override;
private:
	bool OnAcceptRequest(const char* ip, USHORT port) override;
	void OnAccept(SessionInfo sessionInfo) override;
	void OnDisconnect(SessionInfo sessionInfo) override;
	void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;

	virtual void ProcChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& nickName, Array<char, 64>& sessionKey) override;
	virtual void ProcChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY) override;
	virtual void ProcChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg) override;
	virtual void ProcChatReqHeartbeat(SessionInfo sessionInfo) override;
	PerformanceMonitor _monitor;

	static unsigned JobWorkFunc(PVOID pVoid);
	void JobWork();

public:
	class ChatRoom* pRoom = nullptr;
	LONG _RecvMsgCnt = 0;
	LONG _SendMsgCnt = 0;
	DWORD _onConnectCnt = 0;
	int GetReqMsgCnt();
	int GetResMsgCnt();
	void Monitor();
};