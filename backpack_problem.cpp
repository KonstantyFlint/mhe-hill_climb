#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <random>

struct backpack_problem {
    double capacity{};
    std::vector<double> sizes;
    std::vector<double> values;
};

std::function<double(std::vector<bool>)> reward_function_factory(const backpack_problem &problem) {
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

void log_solution(std::ostream &out, std::vector<bool> solution, backpack_problem problem) {
    std::function<double(std::vector<bool>)> goal_function = reward_function_factory(problem);
    double value = goal_function(solution);
    out << "backpack capacity:" << problem.capacity << "\n";
    out << "solution value: " << value << ((value < 0) ? " (capacity exceeded)" : "") << "\n";
    out << "[index]\t"
           "[taken]\t"
           "[size]\t"
           "[value]\n";
    for (int i = 0; i < problem.values.size(); i++) {
        out << i << ".\t"
            << (solution[i] ? "*" : " ") << "\t"
            << problem.sizes[i] << "\t"
            << problem.values[i] << "\n";
    }
}

std::ostream &operator<<(std::ostream &o, std::pair<std::vector<bool>, backpack_problem> solved) {
    log_solution(o, solved.first, solved.second);
    return o;
}

backpack_problem read_problem(std::istream & i) {
    backpack_problem out;
    i >> out.capacity;
    while (!i.eof()) {
        double size, value;
        i >> size >> value;
        if(size == 0 && value == 0)break;
        out.sizes.push_back(size);
        out.values.push_back(value);
    }
    return out;
}

std::istream &operator>>(std::istream &i, backpack_problem & problem) {
    problem = read_problem(i);
    return i;
}

std::vector<bool> example_solution(const backpack_problem &problem) {
    return std::vector<bool>(problem.values.size());
}

std::vector<bool> example_solution_random(const backpack_problem &problem) {
    static std::random_device device;
    static std::mt19937 generator(device());
    static std::uniform_int_distribution<int> distribution(0, 1);
    std::vector<bool> out(problem.values.size());
    for (int i = 0; i < out.size(); i++) {
        out[i] = (distribution(generator) == 1);
    }
    return out;
}

bool increment(std::vector<bool> &v) {
    int index = v.size();
    do {
        index--;
        v[index] = !v[index];
    } while (index > 0 && v[index] == 0);
    return !(index == 0 && v[0] == 0);
}