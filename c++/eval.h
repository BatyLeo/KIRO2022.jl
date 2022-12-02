#pragma once

#include "instance.h"
#include "solution.h"

bool is_feasible(const Solution& solution, const Instance& instance, bool verbose=true);
float job_cost(int job_index, const Solution& solution, const Instance& instance);
float cost(const Solution& solution, const Instance& instance);
