#pragma once

#include "instance.h"
#include "solution.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// for convenience
using json = nlohmann::json;

Instance read_instance(string path);
Solution read_solution(string path);
void write_solution(Solution solution, string path);
