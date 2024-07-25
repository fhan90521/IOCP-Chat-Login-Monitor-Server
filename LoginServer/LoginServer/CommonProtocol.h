//#ifndef __GODDAMNBUG_ONLINE_PROTOCOL__
//#define __GODDAMNBUG_ONLINE_PROTOCOL__




enum en_PACKET_CS_LOGIN_RES_LOGIN 
{
	dfLOGIN_STATUS_NONE				= -1,		// 미인증상태
	dfLOGIN_STATUS_FAIL				= 0,		// 세션오류
	dfLOGIN_STATUS_OK				= 1,		// 성공
	dfLOGIN_STATUS_GAME				= 2,		// 게임중
	dfLOGIN_STATUS_ACCOUNT_MISS		= 3,		// account 테이블에 AccountNo 없음
	dfLOGIN_STATUS_SESSION_MISS		= 4,		// Session 테이블에 AccountNo 없음
	dfLOGIN_STATUS_STATUS_MISS		= 5,		// Status 테이블에 AccountNo 없음
	dfLOGIN_STATUS_NOSERVER			= 6,		// 서비스중인 서버가 없음.
};


enum en_PACKET_CS_GAME_RES_LOGIN 
{
	dfGAME_LOGIN_FAIL				= 0,		// 세션키 오류 또는 Account 데이블상의 오류
	dfGAME_LOGIN_OK					= 1,		// 성공
	dfGAME_LOGIN_NOCHARACTER		= 2,		// 성공 / 캐릭터 없음 > 캐릭터 선택화면으로 전환. 
	dfGAME_LOGIN_VERSION_MISS		= 3,		// 서버,클라 버전 다름
};



enum en_PACKET_SS_LOGINSERVER_LOGIN
{
	dfSERVER_TYPE_GAME		= 1,
	dfSERVER_TYPE_CHAT		= 2,
	dfSERVER_TYPE_MONITOR	= 3,
};

enum en_PACKET_SS_HEARTBEAT
{
	dfTHREAD_TYPE_WORKER	= 1,
	dfTHREAD_TYPE_DB		= 2,
	dfTHREAD_TYPE_GAME		= 3,
};

// en_PACKET_SS_MONITOR_LOGIN
enum en_PACKET_CS_MONITOR_TOOL_SERVER_CONTROL
{
	dfMONITOR_SERVER_TYPE_LOGIN		= 1,
	dfMONITOR_SERVER_TYPE_GAME		= 2,
	dfMONITOR_SERVER_TYPE_CHAT		= 3,
	dfMONITOR_SERVER_TYPE_AGENT		= 4,

	dfMONITOR_SERVER_CONTROL_SHUTDOWN			= 1,		// 서버 정상종료 (게임서버 전용)
	dfMONITOR_SERVER_CONTROL_TERMINATE			= 2,		// 서버 프로세스 강제종료
	dfMONITOR_SERVER_CONTROL_RUN				= 3,		// 서버 프로세스 생성 & 실행
};







//#endif