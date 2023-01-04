"""
    is_feasible(solution::Solution, instance::Instance; verbose=true)

Check if `solution` is feasible for `instance`.
Prints some warnings when solution is infeasible and `verbose` is `true`.
"""
function is_feasible(solution::Solution, instance::Instance; verbose=true)
    (; starts, machines, operators) = solution

    n = nb_tasks(instance)
    @assert n == length(starts) "Not all tasks are in the solution"
    @assert n == length(machines) "Not all tasks are in the solution"
    @assert n == length(operators) "Not all tasks are in the solution"

    # Check job related constraints
    for job in instance.jobs
        current_time = job.release_date

        for task_index in job.task_sequence
            task = instance.tasks[task_index]

            start_time = starts[task_index]
            # start time should occur after end of previous task (constraints 4 and 5)
            if start_time < current_time
                verbose && @warn "Task $task_index started before previous one (or before the release date if it's the first one)"
                return false
            end

            current_time += task.processing_time

            machine_index = machines[task_index]
            # the task needs to be compatible with the chosen machine
            if !(machine_index in task.machines)
                verbose && @warn "Machine $machine_index is not compatible with task $task_index"
                return false
            end

            operator = operators[task_index]
            # the chosen machine should be compatible with the chosen operator
            if ! (operator in instance.operators[task_index, machine_index])
                @warn "Operator $operator cannot operate machine $machine_index"
                return false
            end
        end
    end

    # A machine cannot operate two tasks at the same time (constraint 7)
    for m in 1:nb_machines(instance)
        tasks_with_m = sort(findall(x -> x == m, machines); by=i -> starts[i])

        m_time = 0
        for i in tasks_with_m
            if starts[i] < m_time
                @warn "Two tasks (including $i) at the same time on machine $m"
                return false
            end
            m_time = starts[i] + instance.tasks[i].processing_time
        end
    end

    # An operator cannot operate two tasks at the same time (constraint 7)
    for o in 1:nb_operators(instance)
        tasks_with_o = sort(findall(x -> x == o, operators); by=i -> starts[i])
        o_time = 0
        for i in tasks_with_o
            if starts[i] < o_time
                @warn "Two tasks at the same time with operator $o ($(starts[i]), $o_time)"
                return false
            end
            o_time = starts[i] + instance.tasks[i].processing_time
        end
    end

    return true
end

"""
    job_cost(job_index::Int, solution::Solution, instance::Instance)

Compute the value of job `job_index` in the objective for `solution` in `instance`.
"""
function job_cost(job_index::Int, solution::Solution, instance::Instance)
    (; α, β, jobs, tasks) = instance

    job = jobs[job_index]

    # Compute the job completion time
    last_task_index = job.task_sequence[end]
    last_task = tasks[last_task_index]
    completion_time = solution.starts[last_task_index] + last_task.processing_time

    is_late = completion_time > job.due_date
    tardiness = is_late ? completion_time - job.due_date : 0

    return job.weight * (completion_time + α * is_late + β * tardiness)
end

"""
    cost(solution::Solution, instance::Instance)

Compute the objective value of `solution` for given `instance`.
"""
function cost(solution::Solution, instance::Instance)
    return sum(job_cost(j, solution, instance) for j in 1:nb_jobs(instance))
end
