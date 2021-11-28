#include <functional>

#include <vector>
#include <set>
#include <queue>

std::vector<bool> brute_force(backpack_problem &problem) {
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

template <class T>
class taboo{

    int limit;
    std::set<T> taboo_set;
    std::queue<T> taboo_list;

    void trim(){
        if(taboo_set.size() > limit){
            T oldest = taboo_list.at(0);
            taboo_set.erase(oldest);
            taboo_list.pop();
        }
    }

public:
    taboo(int limit) : limit(limit){}
    void insert(T element){
        taboo_set.insert(element);
        taboo_list.push_back(element);
        trim();
    }

    bool contains(T element){
        return taboo_set.count(element);
    }
};

template<class T>
T taboo_search(std::function<double(T)> reward_function, std::function<std::vector<T>(T)> neighbours_f, T start_point,
             int iterations, int taboo_limit) {

    T current_point = start_point;
    T all_time_best = start_point;

    taboo<T> taboo_list(taboo_limit);

    for (int i = 0; i < iterations; i++) {
        std::vector<std::vector<bool>> neighbours = neighbours_f(current_point);

        std::vector<std::vector<bool>> valid_neighbours;

        for(T neighbour : neighbours){
            if(!taboo_list.contains(neighbour))valid_neighbours.push_back(neighbour);
        }

        if(valid_neighbours.empty())break;

        T best_neighbour = neighbours[0];
        for (int j = 1; j < valid_neighbours.size(); j++) {
            if(reward_function(valid_neighbours[j]) > reward_function(best_neighbour)){
                best_neighbour = valid_neighbours[j];
            }
        }

        current_point = best_neighbour;

        if(reward_function(current_point) > reward_function(all_time_best))
            all_time_best = current_point;

    }
    return all_time_best;
}
