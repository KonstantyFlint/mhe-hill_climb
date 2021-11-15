#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "backpack_problem.cpp"
#include "hill_climb.cpp"
#include "util.cpp"

using namespace std;

void increment_test(int n) {
    vector<bool> v(n);
    do {
        print_vector(v);
    } while (increment(v));
}

vector<bool> brute_force(backpack_problem &problem) {
    auto goal_function = reward_function_factory(problem);
    auto candidate = example_solution(problem);
    auto best_candidate = candidate;
    double best_value = goal_function(candidate);
    do {
        double new_value = goal_function(candidate);
        if (new_value > best_value) {
            best_value = new_value;
            best_candidate = candidate;
        }
    } while (increment(candidate));
    return best_candidate;
}

vector<vector<bool>> neighbours(vector<bool> point) {
    vector<vector<bool>> out;
    for (int i = 0; i < point.size() - 1; i++) {
        auto p2 = point;
        p2[i] = !p2[i];
        out.push_back(p2);
    }
    for (int i = 0; i < point.size() - 1; i++) {
        for (int j = i + 1; j < point.size(); j++) {
            auto p2 = point;
            p2[i] = !p2[i];
            p2[j] = !p2[j];
            out.push_back(p2);
        }
    }
    return out;
}

void solve_brute(istream &input_stream, ostream &output_stream) {
    backpack_problem problem;
    input_stream >> problem;

    auto random_candidate = example_solution_random(problem);
    auto solution = brute_force(problem);

    output_stream << make_pair(solution, problem);
}

void solve_hc(istream &input_stream, ostream &output_stream) {
    backpack_problem problem;
    input_stream >> problem;

    std::vector<bool> random_candidate = example_solution_random(problem);
    auto solution = hill_climb<std::vector<bool>>(reward_function_factory(problem), neighbours,
                                                  generate_random(problem.values.size()), 10000);

    output_stream << make_pair(solution, problem);
}

void solve_rhc(istream &input_stream, ostream &output_stream) {
    backpack_problem problem;
    input_stream >> problem;

    std::vector<bool> random_candidate = example_solution_random(problem);
    auto solution = randomised_hill_climb<std::vector<bool>>(reward_function_factory(problem),
                                                         make_random_neighbour_function<std::vector<bool>>(neighbours),
                                                  generate_random(problem.values.size()), 10000);

    output_stream << make_pair(solution, problem);
}

void compare(backpack_problem problem) {
    std::vector<bool> random_candidate = example_solution_random(problem);
    auto reward_f = reward_function_factory(problem);
    auto t1 = std::chrono::system_clock::now();
    auto solution_hc = hill_climb<std::vector<bool>>(reward_function_factory(problem), neighbours,
                                                     generate_random(problem.values.size()), 10000);
    auto t2 = std::chrono::system_clock::now();
    auto solution_rhc = randomised_hill_climb<std::vector<bool>>(reward_function_factory(problem),
                                                             random_neighbour,
                                                     std::vector<bool>(problem.values.size()), 10000);
    auto t3 = std::chrono::system_clock::now();
    auto solution_brute = brute_force(problem);
    auto t4 = std::chrono::system_clock::now();

    std::cout << "brute: value:\t" << reward_f(solution_brute) << ", time: " << (t4 - t3).count() << endl;
    std::cout << "random hill: value:\t" << reward_f(solution_rhc) << ", time: " << (t3 - t2).count() << endl;
    std::cout << "hill: value:\t" << reward_f(solution_hc) << ", time: " << (t2 - t1).count() << endl;
}

void compare(std::string filename) {
    cout << "comparing for " << filename << ":\n";
    ifstream input_stream = ifstream(filename);
    backpack_problem problem;
    input_stream >> problem;
    compare(problem);
}

int main(int argc, char **argv) {

    compare("problem1.txt");
    compare("problem2.txt");
    compare("problem3.txt");

    return 0;
}