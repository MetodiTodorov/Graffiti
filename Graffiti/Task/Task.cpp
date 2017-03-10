#include <stdafx.h>
#include "Task.h"

///////////////////////////////////////////////////////////////////////////////
Task::Task()
	: percent_(0.0f)
{
}

///////////////////////////////////////////////////////////////////////////////
bool Task::IsRunning() const
{
	bool running = true;
	if (mutex_.try_lock())
	{
		running = percent_ < 1.0f;
		mutex_.unlock();
	}

	return running;
}

///////////////////////////////////////////////////////////////////////////////
float Task::GetPercent() const
{
	std::unique_lock<std::mutex> lk(mutex_);
	return percent_;
}

///////////////////////////////////////////////////////////////////////////////
void Task::SetPercent(float f)
{
	std::unique_lock<std::mutex> lk(mutex_);
	percent_ = f;
}

///////////////////////////////////////////////////////////////////////////////