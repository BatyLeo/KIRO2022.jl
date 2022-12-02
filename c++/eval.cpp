#include "eval.h"

#include <iostream>
#include <cassert>
using namespace std;

bool is_feasible(const Solution& solution, const Instance& instance, bool verbose) {
    int n = instance.nb_tasks();
    assert(n == solution.nb_tasks() && "Not all tasks are in the solution");

    // Job related constraints
    for (int job_index = 0; job_index < instance.nb_jobs(); job_index++) {
        Job job = instance.get_job(job_index);
        int current_time = job.release_date();

        for (int i = 0; i < job.nb_tasks(); i++) {
            int task_index = job.get_task_index(i);
            Task task = instance.get_task(task_index);

            // start time should occutr after end of previous task
            int start_time = solution.start_of_task(task_index);
            if (start_time < current_time) {
                cout << "Task " << task_index << " started before previous one";
                return false;
            }

            current_time += task.processing_time();

            // the task needs to be compatible with the chosen machine
            int machine_index = solution.machine_of_task(task_index);
            if (!task.has_machine(machine_index)) {
                cout << "Machine " << machine_index << " is not compatible with task " << task_index << endl;
                return false;
            }

            // the chosen machine should be compatible with the chosen operator
            int operator_index = solution.operator_of_task(task_index);
            if (!instance.operator_compatibility(operator_index, task_index, machine_index)) {
                cout << "Operator " << operator_index << " cannot operate machine " << machine_index << " for task " << task_index << endl;
                return false;
            }
        }
    }

    // TODO: A machine cannot operate two tasks at the same time (constraint 7)
    for (int m = 0; m < instance.nb_machines(); m++) {
        // TODO
    }

    // TODO: An operator cannot operate two tasks at the same time (constraint 7)
    return true;
}

float job_cost(int job_index, const Solution& solution, const Instance& instance) {
    Job job = instance.get_job(job_index);

    // Compute completion time
    int last_task_index = job.get_task_index(job.nb_tasks()-1);
    Task last_task = instance.get_task(last_task_index);
    float completion_time = solution.start_of_task(last_task_index) + last_task.processing_time();

    bool is_late = completion_time > job.due_date();
    float tardiness = is_late ? completion_time - job.due_date() : 0;
    return job.weight() * (completion_time + instance.alpha() * is_late + instance.beta() * tardiness);
}

float cost(const Solution& solution, const Instance& instance) {
    float total_cost = 0.0;
    for (int job_index = 0; job_index < instance.nb_jobs(); job_index++) {
        total_cost += job_cost(job_index, solution, instance);
    }
    return total_cost;
}
