module KIRO2022

using JSON

include("instance.jl")
include("solution.jl")
include("parsing.jl")
include("eval.jl")

export Instance, Solution
export nb_jobs, nb_tasks, nb_machines, nb_operators
export read_instance, read_solution, write_solution
export is_feasible, cost
export prepare_submission

end
