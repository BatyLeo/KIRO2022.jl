#pragma once

#include <fstream>
#include <vector>

using namespace std;

class Solution
{
private:
    vector<int> _starts;
    vector<int> _machines;
    vector<int> _operators;
public:
    Solution(vector<int>& starts, vector<int>& machines, vector<int>& operators);
    //vector<int> starts() { return _starts; }
    //vector<int> machines() { return _machines; }
    //vector<int> operators() { return _operators; }
    int nb_tasks() const { return _starts.size(); }
    int start_of_task(int task_index) const { return _starts[task_index]; }
    int machine_of_task(int task_index) const { return _machines[task_index]; }
    int operator_of_task(int task_index) const { return _operators[task_index]; }
};

std::ostream& operator<<(std::ostream &os, Solution const& m);
