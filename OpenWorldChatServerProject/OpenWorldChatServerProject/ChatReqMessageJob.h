#pragma once
#include "CSendBuffer.h"
#include "CRecvBuffer.h"
#include "Job.h"
struct ChatReqMessageJob: public Job
{
	INT64	_accountNo;
	Vector<char> _msg;
	void ProcessJob() override;
};
