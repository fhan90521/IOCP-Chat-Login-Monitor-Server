//#ifndef __GODDAMNBUG_ONLINE_PROTOCOL__
//#define __GODDAMNBUG_ONLINE_PROTOCOL__




enum en_PACKET_CS_LOGIN_RES_LOGIN 
{
	dfLOGIN_STATUS_NONE				= -1,		// ����������
	dfLOGIN_STATUS_FAIL				= 0,		// ���ǿ���
	dfLOGIN_STATUS_OK				= 1,		// ����
	dfLOGIN_STATUS_GAME				= 2,		// ������
	dfLOGIN_STATUS_ACCOUNT_MISS		= 3,		// account ���̺� AccountNo ����
	dfLOGIN_STATUS_SESSION_MISS		= 4,		// Session ���̺� AccountNo ����
	dfLOGIN_STATUS_STATUS_MISS		= 5,		// Status ���̺� AccountNo ����
	dfLOGIN_STATUS_NOSERVER			= 6,		// �������� ������ ����.
};


enum en_PACKET_CS_GAME_RES_LOGIN 
{
	dfGAME_LOGIN_FAIL				= 0,		// ����Ű ���� �Ǵ� Account ���̺���� ����
	dfGAME_LOGIN_OK					= 1,		// ����
	dfGAME_LOGIN_NOCHARACTER		= 2,		// ���� / ĳ���� ���� > ĳ���� ����ȭ������ ��ȯ. 
	dfGAME_LOGIN_VERSION_MISS		= 3,		// ����,Ŭ�� ���� �ٸ�
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

	dfMONITOR_SERVER_CONTROL_SHUTDOWN			= 1,		// ���� �������� (���Ӽ��� ����)
	dfMONITOR_SERVER_CONTROL_TERMINATE			= 2,		// ���� ���μ��� ��������
	dfMONITOR_SERVER_CONTROL_RUN				= 3,		// ���� ���μ��� ���� & ����
};







//#endif