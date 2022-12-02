#include "instance.h"
#include "solution.h"
#include "parsing.h"
#include "eval.h"

using namespace std;


int main() {
    Instance instance = read_instance("../../instances/tiny.json");
    cout << instance << endl;
    Solution solution = read_solution("../../solutions/KIRO-tiny-sol_42.json");
    cout << solution << endl;
    write_solution(solution, "../../sol.json");
    cout << "Is feasible? " << is_feasible(solution, instance) << endl;
    cout << "Solution cost? " << cost(solution, instance) << endl;
    return 0;
}
