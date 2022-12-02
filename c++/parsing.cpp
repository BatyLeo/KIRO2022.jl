#include "parsing.h"

Instance read_instance(string path) {
    std::ifstream f(path);
    json data = json::parse(f);

    // read parameters
    json parameters_data = data["parameters"];
    int nb_tasks = parameters_data["size"]["nb_tasks"];
    int nb_machines = parameters_data["size"]["nb_machines"];
    int nb_operators = parameters_data["size"]["nb_operators"];
    float alpha = parameters_data["costs"]["unit_penalty"];
    float beta = parameters_data["costs"]["tardiness"];

    // read jobs
    json jobs_data = data["jobs"];
    vector<Job> jobs;
    for (auto job : jobs_data) {
        int index = job["job"];
        index--;
        vector<int> task_sequence;
        for (auto i : job["sequence"]) {
            int task_index = i;
            task_index--;
            task_sequence.push_back(task_index);
        }
        int release_date = job["release_date"];
        int due_date = job["due_date"];
        float weight = job["weight"];
        jobs.push_back(Job(index, task_sequence, release_date, due_date, weight));
    }

    // read tasks
    json tasks_data = data["tasks"];
    vector<Task> tasks;
    for (auto task : tasks_data) {
        int index = task["task"];
        index--;
        int processing_time = task["processing_time"];
        vector<int> machines;
        for (auto machine : task["machines"]) {
            int machine_index = machine["machine"];
            machine_index--;
            machines.push_back(machine_index);
        }
        tasks.push_back(Task(index, processing_time, machines));
    }


    // read operators
    vector<vector<vector<int>>> operators;
    for (int i_task = 0; i_task < nb_tasks; i_task++) {
        vector<vector<int>> a(nb_machines, vector<int>());
        operators.push_back(a);
    }

    for (auto task : tasks_data) {
        int i = task["task"];
        i--;
        for (auto machine : task["machines"]) {
            int m = machine["machine"];
            m--;
            vector<int> operator_list = machine["operators"];
            operators[i][m] = operator_list;
        }
    }

    return Instance(nb_operators, alpha, beta, jobs, tasks, operators);
}

Solution read_solution(string path) {
    std::ifstream f(path);
    json data = json::parse(f);

    int nb_tasks = data.size();
    vector<int> starts(nb_tasks, 0);
    vector<int> machines(nb_tasks, 0);
    vector<int> operators(nb_tasks, 0);
    for (auto task : data) {
        int task_index = task["task"];
        task_index--;
        starts[task_index] = task["start"];
        int m = task["machine"];
        machines[task_index] = m - 1;
        operators[task_index] = task["operator"];
    }

    return Solution(starts, machines, operators);
}

void write_solution(Solution solution, string path){
    json data;

    for (int task_index = 0; task_index < solution.nb_tasks(); task_index++) {
        json task;
        task["task"] = task_index + 1;
        task["start"] = solution.start_of_task(task_index);
        task["machine"] = solution.machine_of_task(task_index) + 1;
        task["operator"] = solution.operator_of_task(task_index);
        data.push_back(task);
    }

    // Write data to json file
    std::ofstream file(path);
    file << data;
    return;
}
