"""
    Solution

## Attributes
- `starts`: starting date of each task.
- `machines`: machines for each task.
- `operators`: operator for each task.
"""
Base.@kwdef struct Solution
    starts::Vector{Int}
    machines::Vector{Int}
    operators::Vector{Int}
end
