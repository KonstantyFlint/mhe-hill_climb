#include <vector>
#include <cstdlib>
#include <ctime>

#include "backpack_problem.cpp"
#include "hill_climb.cpp"
#include "util.cpp"

using namespace std;


int main(int argc, char **argv) {

    srand(time(NULL));

    string filename = "plecak1.txt";
    if (argc == 2) filename = argv[1];

    backpack_problem problem = read_problem(filename);

    auto solution = hill_climb<vector<bool>>(
            goal_function_factory(problem),
            bool_vector_modifier_factory(1, 4),
            get_initial_vector(problem.values.size()),
            1000
    );

    log_solution(solution, problem);

    return 0;
}
