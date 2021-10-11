auto hill_climb(auto goal_function, auto modifier, auto start_point, int iterations) {
    double highest_value = goal_function(start_point);
    auto highest_point = start_point;
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