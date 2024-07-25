#pragma once
#include "MyWindow.h"
#include "TlsObjectPool.h"
#include "Session.h"
#include "MyStlContainer.h"
#include "Remotable.h"
class Field;
struct Player: public Remotable
{
	INT64	accountNo;
	Array<WCHAR,20>	id;				
	Array<WCHAR,20>	nickName;
	WORD sectorX;
	WORD sectorY;
	//Array<char,64>_sessionKey;
};