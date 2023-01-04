"""
    Job

## Attributes
- `index`: j
- `task_sequence`: list of task indices i
- `due_date`: dⱼ
- `weight`: wⱼ
"""
Base.@kwdef struct Job
    index::Int
    task_sequence::Vector{Int}
    release_date::Int
    due_date::Int
    weight::Float64
end

"""
    Task

## Attributes
- `index`: i
- `processing_time`: pᵢ
- `machines`: list of machine indices on which this task can be performed
"""
Base.@kwdef struct Task
    index::Int
    processing_time::Int
    machines::Vector{Int}
end

"""
    Instance

## Attributes
- `nb_operators::Int`
- `α::Float64`: penalty when a job is late
- `β::Float64`: delay penalty for jobs
- `jobs::Vector{Job}`: job list, in index order
- `tasks::Vector{Task}`: task list, in index order
- `operators::Matrix{Vector{Int}}`: operators[i, m] = list of operators that can operate task i on machine m
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
