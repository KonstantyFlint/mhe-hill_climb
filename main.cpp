#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <cstdlib>

#include "hill_climb.cpp"

using namespace std;

struct backpack_t {
    double capacity{};
    vector<double> sizes;
    vector<double> values;
};

void log_backpack(backpack_t backpack) {
    cout << "capacity: " << backpack.capacity << "\n";
    cout << "all items:\n";
    cout << "[index]\t[size]\t[value]\n";
    for (int i = 0; i < backpack.values.size(); i++) {
        cout << i << ".\t" << backpack.sizes[i] << "\t" << backpack.values[i] << "\n";
    }
}

void log_solution(vector<bool> solution, backpack_t backpack) {
    cout << "backpack capacity:"<<backpack.capacity<<"\n";
    cout << "[index]\t"
            "[taken]\t"
            "[size]\t"
            "[value]\n";
    for (int i = 0; i < backpack.values.size(); i++) {
        cout << i << ".\t"
             << (solution[i] ? "*" : " ") << "\t"
             << backpack.sizes[i] << "\t"
             << backpack.values[i] << "\n";
    }
}

backpack_t read_backpack(const string &filename) {
    ifstream input_file(filename);
    backpack_t out;
    input_file >> out.capacity;
    while (!input_file.eof()) {
        double size, value;
        input_file >> size >> value;
        out.sizes.push_back(size);
        out.values.push_back(value);
    }
    return out;
}

auto goal_function_factory(const backpack_t &backpack) {
    return [=](vector<bool> taken_items) {
        double sum_size = 0;
        double sum_value = 0;
        for (int i = 0; i < taken_items.size(); i++) {
            if (taken_items[i]) {
                sum_size += backpack.sizes[i];
                sum_value += backpack.values[i];
            }
        }
        if (sum_size > backpack.capacity)return backpack.capacity - sum_size;
        return sum_value;
    };
}

vector<bool> bool_vector_mutation(vector<bool> initial_vector) {
    int index = rand() % initial_vector.size();
    initial_vector[index] = !initial_vector[index];
    return initial_vector;
}

auto bool_vector_modifier_factory(int min_mutation_count, int max_mutation_count) {
    return [=](vector<bool> input_vector) {
        int mutations = (rand() % (max_mutation_count - min_mutation_count + 1)) + min_mutation_count;
        for (int i = 0; i < mutations; i++) input_vector = bool_vector_mutation(input_vector);
        return input_vector;
    };
}

int main(int argc, char **argv) {
    srand(time(NULL));
    backpack_t backpack;
    if (argc == 2) backpack = read_backpack(argv[1]);
    else backpack = read_backpack("plecak1.txt");
    auto solution = hill_climb(
            goal_function_factory(backpack),
            bool_vector_modifier_factory(1, 4),
            vector<bool>{0, 0, 0, 0, 0, 0},
            1000
    );

    log_solution(solution, backpack);

    return 0;
}
