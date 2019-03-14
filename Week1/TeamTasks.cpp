#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

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

TaskStatus operator+(const TaskStatus& status, const int offset)
{
	int tmp = static_cast<int>(status) + offset;
	int max_value = static_cast<int>(TaskStatus::DONE);
	int min_value = static_cast<int>(TaskStatus::NEW);
	tmp = max(tmp, min_value);
	tmp = min(tmp, max_value);
	return static_cast<TaskStatus>(tmp);
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person, int task_count)
{
	TasksInfo refreshed;
	TasksInfo old;

	if (personTasks.count(person) > 0)
	{
		TasksInfo& tasks = personTasks[person];
        int refreshedNum = 0;
		for (auto taskType : tasks)
		{
			if (refreshedNum == task_count || taskType.first == TaskStatus::DONE)
			{
				old.insert(make_pair(taskType.first, taskType.second));
				continue;
			}

			if (taskType.second <= (task_count - refreshedNum))
			{
				refreshed.insert(make_pair(taskType.first + 1, taskType.second));
                refreshedNum += taskType.second;
			}
			else
			{
                refreshed.insert(make_pair(taskType.first + 1, task_count - refreshedNum));
				old.insert(make_pair(taskType.first, taskType.second - (task_count - refreshedNum)));
                refreshedNum += task_count - refreshedNum;
            }
		}
		tasks.clear();
		TaskStatus status = TaskStatus::NEW;
        TaskStatus lastStatus = TaskStatus::NEW;
        do
		{
			int num = (old.count(status) > 0 ? old[status] : 0) +
						(refreshed.count(status) > 0 ? refreshed[status] : 0);
    		tasks[status] = num;
            lastStatus = status;
			status = status + 1;
		} while (status != lastStatus);
        old.erase(TaskStatus::DONE);
	}

	return make_tuple(refreshed, old);
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

void pr(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks)
{
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
}

/*int main() {
	TeamTasks tasks;*/
	/*tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
    */
/*    TasksInfo updated_tasks, untouched_tasks;

    tasks.AddNewTask("a");
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("a", 1);
    pr(updated_tasks, untouched_tasks);

    tasks.AddNewTask("a");
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("a", 2);
    pr(updated_tasks, untouched_tasks);

    tasks.AddNewTask("a");
    PrintTasksInfo(tasks.GetPersonTasksInfo("a"));

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("a", 3);
    pr(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("a"));

    return 0;
}
*/