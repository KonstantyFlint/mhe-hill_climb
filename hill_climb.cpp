#include <functional>

template<class T> T hill_climb(std::function<double(T)> goal_function, std::function<T(T)> modifier, T start_point, int iterations) {
    double highest_value = goal_function(start_point);
    T highest_point = start_point;
    for (int i = 0; i < iterations; i++) {
        auto new_point = modifier(highest_point);
        double new_value = goal_function(new_point);
        if (new_value > highest_value) {
            highest_value = new_value;
            highest_point = new_point;
        }
    }
    return highest_point;
}