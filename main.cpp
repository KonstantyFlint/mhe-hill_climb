#include <vector>
#include <fstream>
#include <chrono>

#include "backpack_problem.cpp"
#include "algorithms.cpp"
#include "problem_io.cpp"
#include "util.cpp"

using namespace std;

std::vector<bool> uniform_brute_force(backpack_problem problem, int iterations) {
    return brute_force(problem);
}

std::vector<bool> uniform_hill_climb(backpack_problem problem, int iterations) {
    return hill_climb<vector<bool>>(reward_function_factory(problem), neighbours_square, vector<bool>(problem.size()),
                                    iterations);
}

std::vector<bool> uniform_random_hill_climb(backpack_problem problem, int iterations) {
    return randomised_hill_climb<vector<bool>>(reward_function_factory(problem), mutate_bool_vector,
                                               vector<bool>(problem.size()), iterations);
}

std::vector<bool> uniform_taboo(backpack_problem problem, int iterations) {
    return taboo_search<vector<bool>>(reward_function_factory(problem), neighbours_linear, vector<bool>(problem.size()),
                                      iterations, iterations / 10);
}

function<vector<bool>(backpack_problem, int)> get_function_from_name(string name) {
    if (name == "brute_force") return uniform_brute_force;
    if (name == "hill_climb")return uniform_hill_climb;
    if (name == "random_hill_climb")return uniform_random_hill_climb;
    if (name == "taboo_search")return uniform_taboo;
    throw "wrong name";
}

void test_uniform_function(function<vector<bool>(backpack_problem, int)> uniform_function, int iterations,
                           string input_filename,
                           string output_filename) {
    backpack_problem problem;
    ifstream input(input_filename);
    input >> problem;

    auto t1 = chrono::system_clock::now();
    vector<bool> solution = uniform_function(problem, iterations);
    auto t2 = chrono::system_clock::now();

    double value = reward_function_factory(problem)(solution);
    auto milis = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    ofstream output(output_filename, fstream::app);

    output << problem.size() << " " << milis << " " << value << "\n";
}

int main(int argc, char **argv) {

    if (argc != 5)return -1;
    string function_name = argv[1];
    string iterations = argv[2];
    string input = argv[3];
    string output = argv[4];

    try {
        test_uniform_function(
                get_function_from_name(function_name),
                stoi(iterations),
                input,
                output
        );
    }catch(exception e){
        return -2;
    }

    return 0;
}