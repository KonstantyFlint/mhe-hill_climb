#include <functional>

std::vector<bool> mutate_bool_vector(std::vector<bool> initial_vector) {
    int index = rand() % initial_vector.size();
    initial_vector[index] = !initial_vector[index];
    return initial_vector;
}

std::function<std::vector<bool>(std::vector<bool>)>
bool_vector_modifier_factory(int min_mutation_count, int max_mutation_count) {
    return [=](std::vector<bool> input_vector) {
        int mutations = (rand() % (max_mutation_count - min_mutation_count + 1)) + min_mutation_count;
        for (int i = 0; i < mutations; i++) input_vector = mutate_bool_vector(input_vector);
        return input_vector;
    };
}

std::vector<bool> get_initial_vector(int length) {
    std::vector<bool> out;
    while (length--)
        out.push_back(false);
    return out;
}