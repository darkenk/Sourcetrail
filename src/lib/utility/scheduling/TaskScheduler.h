#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <deque>
#include <memory>
#include <mutex>

#include "Task.h"
#include "TaskRunner.h"

class TaskScheduler
{
public:
	TaskScheduler(TabId schedulerId);
	~TaskScheduler();

	void pushTask(std::shared_ptr<Task> task);
	void pushNextTask(std::shared_ptr<Task> task);

	void startSchedulerLoopThreaded();
	void startSchedulerLoop();
	void stopSchedulerLoop();

	bool loopIsRunning() const;
	bool hasTasksQueued() const;

	void terminateRunningTasks();

private:
	void processTasks();

	const TabId m_schedulerId;

	bool m_loopIsRunning = false;
	bool m_threadIsRunning = false;
	bool m_terminateRunningTasks = false;

	std::deque<std::shared_ptr<TaskRunner>> m_taskRunners;

	mutable std::mutex m_tasksMutex;
	mutable std::mutex m_loopMutex;
	mutable std::mutex m_threadMutex;
};

#endif	  // TASK_SCHEDULER_H
