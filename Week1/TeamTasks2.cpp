#include <iostream>
#include <map>
#include <vector>

using namespace std;

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const;
void AddNewTask(const string& person);
tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count);
private:
	map<string, TasksInfo> personTasks;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const
{
	return personTasks.at(person);
}

void TeamTasks::AddNewTask(const string& person)
{
	++personTasks[person][TaskStatus::NEW];
}

TaskStatus operator++(const TaskStatus& status)
{
	int tmp = static_cast<int>(status);
	return static_cast<TaskStatus>(++tmp);
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person, int task_count)
{
	TasksInfo refreshed;
	TasksInfo old;

	if (personTasks.count(person) > 0)
	{
		TasksInfo& tasks = personTasks[person];
		int refreshedNum{ 0 };
		for (auto taskType : tasks)
		{
			if (taskType.second == 0)
			{
				continue;
			}
			if (refreshedNum == task_count)
			{
				old.insert(make_pair(taskType.first, taskType.second));
				if (taskType.first == TaskStatus::DONE)
				{
					break;
				}
			}

			if (taskType.second < (task_count - refreshedNum))
			{
				refreshed.insert(make_pair(++taskType.first, taskType.second));
				refreshedNum += taskType.second;
			}
			else
			{
				refreshed.insert(make_pair(++taskType.first, task_count - refreshedNum));
				if (taskType.second == task_count - refreshedNum)
				{
					old.insert(make_pair(taskType.first, taskType.second - (task_count - refreshedNum)));
				}
				refreshedNum += taskType.second;
			}
		}
		tasks.clear();
		TaskStatus last;
		for (auto taskType : refreshed)
		{
			tasks.insert(taskType);
			last = taskType.first;
		}
		for (auto taskType : old)
		{
			if (taskType.first == last)
			{
				int& num = tasks[last];
				num = +taskType.second;
			}
			else {
				tasks.insert(taskType);
			}
		}
	}

	return make_tuple(refreshed, old);
}
