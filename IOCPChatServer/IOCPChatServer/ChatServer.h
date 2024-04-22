#pragma once
#pragma comment (lib, "cpp_redis.lib")
#pragma comment (lib, "tacopie.lib")
#pragma comment (lib, "ws2_32.lib")
#include <cpp_redis/cpp_redis>
#include "IOCPServer.h"
#include "ChatServerStub.h"
#include "ChatServerProxy.h"
#include "Player.h"
#include "Session.h"
#include "NetworkHeader.h"
#include <process.h>
#include "PerformanceMonitor.h"
#include "SSMonitorClient.h"
#define DEFAULT_SECTOR 55
class ChatServer : public IOCPServer, public ChatServerStub, public ChatServerProxy
{
public:
	ChatServer();
	~ChatServer();
	void Run() override;
private:
	inline thread_local static cpp_redis::client* _pRedisClient = nullptr;
	static cpp_redis::client* GetRedisConnection()
	{
		if (_pRedisClient == nullptr)
		{
			_pRedisClient = new cpp_redis::client;
			_pRedisClient->connect();
		}
		return _pRedisClient;
	}
	bool OnAcceptRequest(const char* ip, USHORT port) override;
	void OnAccept(SessionInfo sessionInfo) override;
	void OnDisconnect(SessionInfo sessionInfo) override;
	void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;

	virtual void ProcChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& nickName, Array<char, 64>& sessionKey) override;
	virtual void ProcChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY) override;
	virtual void ProcChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg) override;
	virtual void ProcChatReqHeartbeat(SessionInfo sessionInfo) override;
	PerformanceMonitor _monitor;

public:
	class ChatRoom* _pRoom = nullptr;
	DWORD _onConnectCnt = 0;
	void Monitor();

private:
	SSMonitorClient _monitorClient;
};