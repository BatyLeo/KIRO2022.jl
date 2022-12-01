#pragma once

#include "instance.h"
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace std;

// for convenience
using json = nlohmann::json;

Instance parse_instance(string path);
// Solution read_solution(string path);
