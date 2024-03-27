#pragma once
#include "Job.h"
struct SectorMoveJob : public Job
{
	INT64 _accountNo;
	WORD _nextX;
	WORD _nextY;
	void ProcessJob() override;
};