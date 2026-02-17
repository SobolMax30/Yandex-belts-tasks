#include <iostream>
#include <map>

using namespace std;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
private:
    map<string, TasksInfo> person_tasks;
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return person_tasks.at(person);
    }

    void AddNewTask(const string& person) {
        ++person_tasks[person][TaskStatus::NEW];
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated_tasks, untouched_tasks;

        TasksInfo& tasks = person_tasks[person];

        for (TaskStatus status = TaskStatus::NEW;
            status != TaskStatus::DONE;
            status = Next(status)) {
            updated_tasks[Next(status)] = min(task_count, tasks[status]);
            task_count -= updated_tasks[Next(status)];
        }

        for (TaskStatus status = TaskStatus::NEW;
            status != TaskStatus::DONE;
            status = Next(status)) {
            untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
            tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
        }

         tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

         return {updated_tasks, untouched_tasks};
    }
};

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

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}

