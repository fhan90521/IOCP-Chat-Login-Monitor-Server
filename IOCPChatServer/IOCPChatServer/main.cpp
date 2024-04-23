#include <iostream>
#include <memory>
#include <vector>
#include "ChatServer.h"
#include "CCrashDump.h"
CCrashDump gCrashDump;
int main()
{
	ChatServer* pServer = new ChatServer;
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