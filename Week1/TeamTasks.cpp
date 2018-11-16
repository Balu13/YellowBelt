﻿#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>

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
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const;

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person);

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
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
		for (auto taskType : tasks)
		{
			int refreshedNum = refreshed.size();
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
			}
			else
			{
				refreshed.insert(make_pair(++taskType.first, task_count - refreshedNum));
				old.insert(make_pair(taskType.first, taskType.second - (task_count - refreshedNum)));
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

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
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

	return 0;
}
