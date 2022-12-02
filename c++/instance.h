#pragma once

#include <fstream>
#include <vector>

using namespace std;

class Job
{
private:
    int _index;
    vector<int> _task_sequence;
    int _release_date;
    int _due_date;
    float _weight;
public:
    Job(int index, vector<int>& task_sequence, int release_date, int due_date, float weight);
    int index() {return _index;};
    vector<int> task_sequence() const {return _task_sequence;};
    int release_date() const {return _release_date;};
    int due_date() const {return _due_date;};
    int weight() const {return _weight;};
    int nb_tasks() const { return _task_sequence.size(); }
    int get_task_index(int index_in_sequence) const { return _task_sequence[index_in_sequence]; }
};

class Task
{
private:
    int _index;
    int _processing_time;
    vector<int> _machines;
public:
    Task(int index, int processing_time, vector<int>& machines);
    int index() const { return _index; }
    int processing_time() const { return _processing_time; }
    bool has_machine(int machine_index) const {
        return find(_machines.begin(), _machines.end(), machine_index) != _machines.end();
    }
};

class Instance
{
private:
    int _nb_operators;
    float _alpha;
    float _beta;
    vector<Job> _jobs;
    vector<Task> _tasks;
    vector<vector<vector<int>>> _operators;
public:
    Instance(int nb_operators, float alpha, float beta, vector<Job>& jobs, vector<Task>& tasks, vector<vector<vector<int>>>& operators);
    float alpha() const { return _alpha; }
    float beta() const { return _beta; }
    int nb_jobs() const { return _jobs.size(); }
    int nb_tasks() const { return _tasks.size(); }
    int nb_machines() const { return _operators[0].size(); }
    int nb_operators() const { return _nb_operators; }
    Job get_job(int job_index) const { return _jobs[job_index]; }
    Task get_task(int task_index) const { return _tasks[task_index]; }
    bool operator_compatibility(int operator_index, int task_index, int machine_index) const {
        vector<int> m_list = _operators[task_index][machine_index];
        return find(m_list.begin(), m_list.end(), operator_index) != m_list.end();
    }
};

std::ostream& operator<<(std::ostream &os, Instance const& instance);
