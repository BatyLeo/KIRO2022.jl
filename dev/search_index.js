var documenterSearchIndex = {"docs":
[{"location":"","page":"Home","title":"Home","text":"CurrentModule = KIRO2022","category":"page"},{"location":"#KIRO2022","page":"Home","title":"KIRO2022","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"Documentation for KIRO2022.","category":"page"},{"location":"#Parsing-functions","page":"Home","title":"Parsing functions","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"This package exports the three following parsing functions:","category":"page"},{"location":"","page":"Home","title":"Home","text":"read_instance: read an instance file from its path and returns a corresponding Instance object.\nread_solution: write a Solution object to a solution format json file.\nwrite_solution: read a solution file into a Solution object.","category":"page"},{"location":"#Data-structures","page":"Home","title":"Data structures","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"Instance\nMethods nb_tasks, nb_operators, nb_jobs, nb_machines can be used to query instance parameters.\nSolution","category":"page"},{"location":"","page":"Home","title":"Home","text":"Note: you may want to implement your own custom data structures that contain additional information that may be used by your algorithms.","category":"page"},{"location":"#Evaluation-utilities","page":"Home","title":"Evaluation utilities","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"is_feasible: function that tests if a solution is feasible for a given instance\ncost: function that computes the cost of a solution for given instance","category":"page"},{"location":"#Preparing-submission","page":"Home","title":"Preparing submission","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"prepare_submission: this function take as input a solver function and automatically produces a solution file for each instance file, ready for submission.","category":"page"},{"location":"","page":"Home","title":"Home","text":"","category":"page"},{"location":"#API","page":"Home","title":"API","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"","category":"page"},{"location":"","page":"Home","title":"Home","text":"Modules = [KIRO2022]","category":"page"},{"location":"#KIRO2022.Instance","page":"Home","title":"KIRO2022.Instance","text":"Instance\n\nAttributes\n\nnb_operators::Int\nα::Float64: penalty when a job is late\nβ::Float64: delay penalty for jobs\njobs::Vector{Job}: job list, in index order\ntasks::Vector{Task}: task list, in index order\noperators::Matrix{Vector{Int}}: operators[i, m] = list of operators that can operate task i on machine m\n\n\n\n\n\n","category":"type"},{"location":"#KIRO2022.Job","page":"Home","title":"KIRO2022.Job","text":"Job\n\nAttributes\n\nindex: j\ntask_sequence: list of task indices i\ndue_date: dⱼ\nweight: wⱼ\n\n\n\n\n\n","category":"type"},{"location":"#KIRO2022.Solution","page":"Home","title":"KIRO2022.Solution","text":"Solution\n\nAttributes\n\nstarts: starting date of each task.\nmachines: machines for each task.\noperators: operator for each task.\n\n\n\n\n\n","category":"type"},{"location":"#KIRO2022.Task","page":"Home","title":"KIRO2022.Task","text":"Task\n\nAttributes\n\nindex: i\nprocessing_time: pᵢ\nmachines: list of machine indices on which this task can be performed\n\n\n\n\n\n","category":"type"},{"location":"#KIRO2022.cost-Tuple{Solution, Instance}","page":"Home","title":"KIRO2022.cost","text":"cost(solution::Solution, instance::Instance)\n\nCompute the objective value of solution for given instance.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.is_feasible-Tuple{Solution, Instance}","page":"Home","title":"KIRO2022.is_feasible","text":"is_feasible(solution::Solution, instance::Instance; verbose=true)\n\nCheck if solution is feasible for instance. Prints some warnings when solution is infeasible and verbose is true.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.job_cost-Tuple{Int64, Solution, Instance}","page":"Home","title":"KIRO2022.job_cost","text":"job_cost(job_index::Int, solution::Solution, instance::Instance)\n\nCompute the value of job job_index in the objective for solution in instance.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.prepare_submission-Tuple{}","page":"Home","title":"KIRO2022.prepare_submission","text":"prepare_submission(solver, instances_folder, solutions_folder, group)\n\nRead instances from the instance_folder, use solver to generate solutions, and then write these solutions in the solutions_folder with the right format and group number.\n\nThe solver should be a function with one Instance argument, and return a (feasible) Solution.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.read_instance-Tuple{String}","page":"Home","title":"KIRO2022.read_instance","text":"read_instance(path::String)\n\nRead instance from json file path.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.read_solution-Tuple{String}","page":"Home","title":"KIRO2022.read_solution","text":"read_solution(path::String)\n\nRead solution from json file path.\n\n\n\n\n\n","category":"method"},{"location":"#KIRO2022.write_solution-Tuple{Solution, String}","page":"Home","title":"KIRO2022.write_solution","text":"write_solution(solution::Solution, path::String)\n\nWrite solution to file path with json format.\n\n\n\n\n\n","category":"method"}]
}