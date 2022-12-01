"""
    read_instance(path::String)

Read instance from json file `path`.
"""
function read_instance(path::String)
    @assert endswith(path, ".json")

    data = JSON.parsefile(path)
    parameters_data = data["parameters"]
    nb_tasks = parameters_data["size"]["nb_tasks"]
    nb_machines = parameters_data["size"]["nb_machines"]
    nb_operators = parameters_data["size"]["nb_operators"]
    α = parameters_data["costs"]["unit_penalty"]
    β = parameters_data["costs"]["tardiness"]

    jobs_data = data["jobs"]
    jobs = [
        Job(;
            index=job["job"],
            task_sequence=job["sequence"],
            release_date=job["release_date"],
            due_date=job["due_date"],
            weight=job["weight"],
        ) for job in jobs_data
    ]

    tasks_data = data["tasks"]
    tasks = [
        Task(;
            index=task["task"],
            processing_time=task["processing_time"],
            machines=[machine["machine"] for machine in task["machines"]],
        ) for task in tasks_data
    ]

    operators = [Int[] for _ in 1:nb_tasks, _ in 1:nb_machines]

    for task in tasks_data
        i = task["task"]
        for machine in task["machines"]
            m = machine["machine"]
            operator_list = machine["operators"]
            operators[i, m] = operator_list
        end
    end

    return Instance(; nb_operators, α, β, jobs, tasks, operators)
end

"""
    read_solution(path::String)

Read solution from json file `path`.
"""
function read_solution(path::String)
    @assert endswith(path, ".json")

    data = JSON.parsefile(path)
    nb_tasks = length(data)
    starts = zeros(Int, nb_tasks)
    machines = zeros(Int, nb_tasks)
    operators = zeros(Int, nb_tasks)
    for task in data
        task_index = task["task"]
        starts[task_index] = task["start"]
        machines[task_index] = task["machine"]
        operators[task_index] = task["operator"]
    end
    return Solution(; starts, machines, operators)
end

"""
    write_solution(solution::Solution, path::String)

Write `solution` to file `path` with json format.
"""
function write_solution(solution::Solution, path::String)
    @assert endswith(path, ".json")

    (; starts, machines, operators) = solution
    data = []
    for (task_index, (start, machine, operator)) in
        enumerate(zip(starts, machines, operators))
        push!(
            data,
            Dict(
                "task" => task_index,
                "start" => start,
                "machine" => machine,
                "operator" => operator,
            ),
        )
    end
    open(path, "w") do f
        JSON.print(f, data)
    end
end

"""
    prepare_submission(solver, instances_folder, solutions_folder, group)

Read instances from the `instance_folder`, use `solver` to generate solutions, and then write these solutions in the `solutions_folder` with the right format and `group` number.

The `solver` should be a function with one `Instance` argument, and return a (feasible) `Solution`.
"""
function prepare_submission(;
    solver,
    instances_folder::String="instances",
    solutions_folder::String="solutions",
    group::Int=42,
)
    names = ["tiny", "medium", "large", "huge"]
    total_cost = 0.0
    for name in names
        @info "Solving $name instance"
        instance = read_instance(joinpath(instances_folder, "$name.json"))
        sol = solver(instance)  # call the solver
        feasible = is_feasible(sol, instance)
        if feasible
            write_solution(sol, joinpath(solutions_folder, "KIRO-$name-sol_$group.json"))
            total_cost += cost(sol, instance)
        else
            total_cost += Inf
        end
    end
    @info "Total cost: $total_cost"
    return nothing
end
