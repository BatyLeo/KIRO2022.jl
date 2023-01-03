Base.@kwdef struct Job
    index::Int
    task_sequence::Vector{Int}
    release_date::Int
    due_date::Int
    weight::Float64
end

Base.@kwdef struct Task
    index::Int
    processing_time::Int
    machines::Vector{Int} # list of machine indices on which this task can be performed
end

"""
    Instance

## Attributes
- `nb_jobs`
- `nb_tasks`
- `nb_machines`
- `α`: penalty when a job is late
- `β`: delay penalty for jobs
- `jobs`: job list, in index order
- `tasks`: task list, in index order
- `operators`:
"""
Base.@kwdef struct Instance
    nb_operators::Int
    α::Float64 # unit penalty
    β::Float64 # tardiness
    jobs::Vector{Job}
    tasks::Vector{Task}
    operators::Matrix{Vector{Int}}  # operators[i, m] = list of operators that can operate task i on machine m
end

nb_jobs(instance::Instance) = length(instance.jobs)
nb_tasks(instance::Instance) = length(instance.tasks)
nb_machines(instance::Instance) = size(instance.operators, 2)
nb_operators(instance::Instance) = instance.nb_operators
