#include "parsing.h"

Instance parse_instance(string path) {
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
        vector<int> task_sequence;
        for (auto i : job["sequence"]) {
             task_sequence.push_back(i);
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
        int processing_time = task["processing_time"];
        vector<int> machines;
        for (auto machine : task["machines"]) {
            machines.push_back(machine["machine"]);
        }
        tasks.push_back(Task(index, processing_time, machines));
    }

    // read operators
    vector<vector<vector<int>>> operators(nb_tasks);
    for (int i_machine = 0; i_machine < nb_machines; i_machine++) {
        vector<vector<int>> a(nb_machines);
        operators.push_back(a);
    }
    for (auto task : tasks_data) {
        int i = task["task"];
        for (auto machine : task["machine"]) {
            int m = machine["machine"];
            vector<int> operator_list = machine["operators"];
            operators[i][m] = operator_list;
        }
    }

    std::cout << data["parameters"] << typeid(data["parameters"]).name() << std::endl;
    std::cout << data["jobs"] << std::endl;
    std::cout << data["tasks"] << std::endl;

    return Instance(nb_operators, alpha, beta, jobs, tasks, operators);
}
