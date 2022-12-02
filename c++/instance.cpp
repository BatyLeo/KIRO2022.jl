#include "instance.h"

Job::Job(int index, vector<int>& task_sequence, int release_date, int due_date, float weight)
{
    _index = index;
    _task_sequence = task_sequence;
    _release_date = release_date;
    _due_date = due_date;
    _weight = weight;
}

Task::Task(int index, int processing_time, vector<int>& machines)
{
    _index = index;
    _processing_time = processing_time;
    _machines = machines;
}

Instance::Instance(int nb_operators, float alpha, float beta, vector<Job>& jobs, vector<Task>& tasks, vector<vector<vector<int>>>& operators)
{
    _nb_operators = nb_operators;
    _alpha = alpha;
    _beta = beta;
    _jobs = jobs;
    _tasks = tasks;
    _operators = operators;
}

std::ostream& operator<<(std::ostream& os, const Instance& instance) { 
    os << "Nb jobs: " << instance.nb_jobs() << endl;
    os << "Nb tasks: " << instance.nb_tasks() << endl;
    os << "Nb operators: " << instance.nb_operators() << endl;
    os << "Nb machines: " << instance.nb_machines();
    return os;
}
