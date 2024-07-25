#pragma once
#include "IOCPServer.h"
#include "MyStlContainer.h"
#include "SSMonitorServerProxy.h"
#include "SSMonitorStub.h"
#include "DBManager.h"
#include <time.h>
class MonitorServer :public IOCPServer, public SSMonitorServerProxy, public SSMonitorStub
{
private:
	DBManager _logDB;
	class CSMonitorServer* _pCSMonitorServer = nullptr;
	HashMap<SessionInfo::ID,int> _serverNoMap;
	HashSet<int> _severNoSet;
	SRWLOCK _serverNoLock;
	SharedPtr<class DBJobQueue>_pDBJobQ;
	class MonitorDatas
	{
		friend class MonitorServer;
		enum
		{
			MAX_DATA_TYPE = 64,
		};
		int _cnt[MAX_DATA_TYPE] = { 0, };
		float _avg[MAX_DATA_TYPE] = { 0, };
		int _max[MAX_DATA_TYPE] = { 0, };
		int _min[MAX_DATA_TYPE];
		SRWLOCK _dataLocks[MAX_DATA_TYPE];
		MonitorDatas()
		{
			for (int i = 0; i < MAX_DATA_TYPE; i++)
			{
				InitializeSRWLock(&_dataLocks[MAX_DATA_TYPE]);
				_min[i] = INT_MAX;
			}
		}
	};
	HashMap<int, MonitorDatas*> _monitorDatasMap;
	virtual bool OnAcceptRequest(const char* ip, USHORT port) override;
	virtual void OnAccept(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;

	virtual void ProcReqLoginByServer(SessionInfo sessionInfo, int serverNo) override;
	virtual void ProcMonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp) override;

	void LogOnDB(int serverNo, int type, float avr, int min, int max);
public:
	MonitorServer();
	~MonitorServer();
	virtual void Run() override;
	void CheckSessionStatus();
	void Monitor();
};