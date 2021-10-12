#include <vector>
#include <iostream>
#include <fstream>
#include <functional>

struct backpack_problem {
    double capacity{};
    std::vector<double> sizes;
    std::vector<double> values;
};

void log_solution(std::vector<bool> solution, backpack_problem problem) {
    std::cout << "backpack capacity:" << problem.capacity << "\n";
    std::cout << "[index]\t"
            "[taken]\t"
            "[size]\t"
            "[value]\n";
    for (int i = 0; i < problem.values.size(); i++) {
        std::cout << i << ".\t"
                  << (solution[i] ? "*" : " ") << "\t"
                  << problem.sizes[i] << "\t"
                  << problem.values[i] << "\n";
    }
}

backpack_problem read_problem(const std::string &filename) {
    std::ifstream input_file(filename);
    backpack_problem out;
    input_file >> out.capacity;
    while (!input_file.eof()) {
        double size, value;
        input_file >> size >> value;
        out.sizes.push_back(size);
        out.values.push_back(value);
    }
    return out;
}

std::function<double(std::vector<bool>)> goal_function_factory(const backpack_problem &problem) {
    return [problem](std::vector<bool> taken_items) {
        double sum_size = 0;
        double sum_value = 0;
        for (int i = 0; i < taken_items.size(); i++) {
            if (taken_items[i]) {
                sum_size += problem.sizes[i];
                sum_value += problem.values[i];
            }
        }
        if (sum_size > problem.capacity)return problem.capacity - sum_size;
        return sum_value;
    };
}