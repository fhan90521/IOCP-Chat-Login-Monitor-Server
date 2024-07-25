#include <iostream>
#include <memory>
#include <vector>
#include "MonitorServer.h"
#include "CSendBuffer.h"
#include "Room.h"
#include "MyNew.h"
#include "CCrashDump.h"
CCrashDump gCrashDump;
int main()
{
	MonitorServer* pServer = new MonitorServer;
	pServer->Run();
	while (pServer->_bShutdown == false)
	{
		if (pServer->ServerControl() == false)
		{
			pServer->Monitor();
		}
		Sleep(1000);
	}
	delete pServer;
	return 0;
}