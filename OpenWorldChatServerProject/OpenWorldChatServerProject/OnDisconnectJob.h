#pragma once
#include "Job.h"
struct OnDisconnectJob: public Job
{
	void ProcessJob() override;
};