#include <functional>
#include <random>

std::vector<bool> mutate_bool_vector(std::vector<bool> initial_vector) {
    int index = rand() % initial_vector.size();
    initial_vector[index] = !initial_vector[index];
    return initial_vector;
}

std::vector<bool> generate_random(int size){
    static std::mt19937 device;
    static std::uniform_int_distribution<int> distr(0,1);
    std::vector<bool> out;
    for(int i=0;i<size;i++){
        out.push_back(distr(device) == 1);
    }
    return out;
}

std::function<std::vector<bool>(std::vector<bool>)>
bool_vector_modifier_factory(int min_mutation_count, int max_mutation_count) {
    return [=](std::vector<bool> input_vector) {
        int mutations = (rand() % (max_mutation_count - min_mutation_count + 1)) + min_mutation_count;
        for (int i = 0; i < mutations; i++) input_vector = mutate_bool_vector(input_vector);
        return input_vector;
    };
}

void print_vector(std::vector<bool> v){
    for(int i=0;i<v.size();i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
}

template <class T>
T random_member(std::vector<T> list){
    static std::mt19937 device;
    std::uniform_int_distribution<int> distr(0,list.size()-1);
    return list[distr(device)];
}

template<class T>
std::function<T(T)> make_random_neighbour_function(std::function<std::vector<T>(T)> neighbours_function){
    return [=](T t){
        return random_member(neighbours_function(t));
    };
}

std::vector<bool> random_neighbour(std::vector<bool> point){
    static std::mt19937 device;
    std::uniform_int_distribution<int> element_range(0,point.size()-1);
    std::uniform_int_distribution<int> mutation_count_range(1,2);
    int mutation_count = mutation_count_range(device);
    for(int i=0;i<mutation_count;i++){
        int index = element_range(device);
        point[index] = !point[index];
    }

    return point;
}