#include <functional>

#include <vector>
#include <set>

template<class T>
T randomised_hill_climb(std::function<double(T)> goal_function, std::function<T(T)> modifier, T start_point,
                        int iterations) {
    double highest_value = goal_function(start_point);
    T highest_point = start_point;
    int fail_count=0;
    for (int i = 0; i < iterations; i++) {
        auto new_point = modifier(highest_point);
        double new_value = goal_function(new_point);
        if (new_value > highest_value) {
            highest_value = new_value;
            highest_point = new_point;
            fail_count=0;
        }else{
            fail_count++;
            if(fail_count>=100)return highest_point;
        }
    }
    return highest_point;
}

template<class T>
T hill_climb(std::function<double(T)> reward_function, std::function<std::vector<T>(T)> neighbours_f, T start_point,
             int iterations) {
    T current_point = start_point;
    for (int i = 0; i < iterations; i++) {
        std::vector<std::vector<bool>> neighbours = neighbours_f(current_point);

        auto best_neighbour = neighbours[0];
        for (int i = 1; i < neighbours.size(); i++) {
            if(reward_function(neighbours[i]) > reward_function(best_neighbour)){
                best_neighbour = neighbours[i];
            }
        }

        if (reward_function(best_neighbour) > reward_function(current_point)) {
            current_point = best_neighbour;
        }else{
            break;
        }
    }
    return current_point;
}

template<class T>
T taboo_search(std::function<double(T)> reward_function, std::function<std::vector<T>(T)> neighbours_f, T start_point,
             int iterations) {
    T current_point = start_point;
    std::set<T> taboo;
    for (int i = 0; i < iterations; i++) {
        std::vector<std::vector<bool>> neighbours = neighbours_f(current_point);

        for (int i = 0; i < neighbours.size(); i++){
            if(taboo.count(neighbours[i]))neighbours.erase(i--);
        }

        if(neighbours.size()==0)break;

        for (int i = 1; i < neighbours.size(); i++) {
            if(reward_function(neighbours[i]) > reward_function(best_neighbour)){
                best_neighbour = neighbours[i];
            }
        }

        if (reward_function(best_neighbour) > reward_function(current_point)) {
            current_point = best_neighbour;
            taboo.insert(current_point);
        }else{
            break;
        }
    }
    return current_point;
}
