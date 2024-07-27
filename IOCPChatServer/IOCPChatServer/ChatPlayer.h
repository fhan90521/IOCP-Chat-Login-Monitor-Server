#pragma once
#include "MyWindow.h"
#include "TlsObjectPool.h"
#include "Session.h"
#include "MyStlContainer.h"
struct ChatPlayer
{
	INT64	accountNo;
	SessionInfo sessionInfo;
	Array<WCHAR,20>	id;				
	Array<WCHAR,20>	nickName;
	WORD sectorX;
	WORD sectorY;
	//Array<char,64>_sessionKey;
};