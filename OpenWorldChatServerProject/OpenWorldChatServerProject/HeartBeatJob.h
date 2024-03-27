#pragma once
#include "Job.h"
struct HeartBeatJob : public Job
{
	void ProcessJob() override;
};