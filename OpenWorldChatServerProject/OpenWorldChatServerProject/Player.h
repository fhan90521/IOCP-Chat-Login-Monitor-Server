#pragma once
#include "MyWindow.h"
#include "TlsObjectPool.h"
#include "Session.h"
#include "MyStlContainer.h"
#include "Remotable.h"
class Field;
struct Player: public Remotable
{
	INT64	_accountNo;
	Array<WCHAR,20>	_id;				
	Array<WCHAR,20>	_nickName;
	WORD _sectorX;
	WORD _sectorY;
	//Array<char,64>_sessionKey;
};