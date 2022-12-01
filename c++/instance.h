#pragma once

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
    vector<int> task_sequence() {return _task_sequence;};
    int release_date() {return _release_date;};
    int due_date() {return _due_date;};
    int weight() {return _weight;};
};

class Task
{
private:
    int _index;
    int _processing_time;
    vector<int> _machines;
public:
    Task(int index, int processing_time, vector<int>& machines);
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
    int nb_jobs() { return _jobs.size(); }
    int nb_tasks() { return _tasks.size(); }
    int nb_machines() { return _operators[0].size(); }
    int nb_operators() { return _nb_operators; }
};
