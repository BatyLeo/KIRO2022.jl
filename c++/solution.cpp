#include "solution.h"

Solution::Solution(vector<int>& starts, vector<int>& machines, vector<int>& operators)
{
    _starts = starts;
    _machines = machines;
    _operators = operators;
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) { 
    for (int i = 0; i < solution.nb_tasks(); i++) {
        os << solution.start_of_task(i) << " ";
    }
    os << endl;
    for (int i = 0; i < solution.nb_tasks(); i++) {
        os << solution.machine_of_task(i) << " ";
    }
    os << endl;
    for (int i = 0; i < solution.nb_tasks(); i++) {
        os << solution.operator_of_task(i) << " ";
    }
    return os;
}
