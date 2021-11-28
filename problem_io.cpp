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

std::ostream &operator<<(std::ostream &o, std::pair<std::vector<bool>, backpack_problem> solved) {
    log_solution(o, solved.first, solved.second);
    return o;
}

std::istream &operator>>(std::istream &i, backpack_problem & problem) {
    problem = read_problem(i);
    return i;
}