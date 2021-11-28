#include <vector>
#include <iostream>
#include <functional>
#include <random>

struct backpack_problem {
    double capacity{};
    std::vector<double> sizes;
    std::vector<double> values;

    int size(){
        return values.size();
    }
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

std::vector<std::vector<bool>> neighbours_linear(std::vector<bool> point) {
    std::vector<std::vector<bool>> out;
    for (int i = 0; i < point.size(); i++) {
        auto p2 = point;
        p2[i] = !p2[i];
        out.push_back(p2);
    }
    return out;
}

std::vector<std::vector<bool>> neighbours_square(std::vector<bool> point) {
    std::vector<std::vector<bool>> out;
    for (int i = 0; i < point.size(); i++) {
        auto p2 = point;
        p2[i] = !p2[i];
        out.push_back(p2);
    }
    for (int i = 0; i < point.size(); i++) {
        for (int j = i + 1; j < point.size(); j++) {
            auto p2 = point;
            p2[i] = !p2[i];
            p2[j] = !p2[j];
            out.push_back(p2);
        }
    }
    return out;
}