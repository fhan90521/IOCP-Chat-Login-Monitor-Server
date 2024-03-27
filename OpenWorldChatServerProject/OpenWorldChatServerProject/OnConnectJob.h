#pragma once
#include "Job.h"
struct OnConnectJob :public Job
{
	void ProcessJob() override;
};