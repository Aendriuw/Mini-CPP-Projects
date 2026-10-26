#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

void split_command(std::string const& curr_line, std::string& command, std::string &argument) {
    std::size_t space_idx = curr_line.find(' ');

    command = curr_line.substr(0, space_idx);

    if (space_idx == std::string::npos) {
        argument = "";
        return;
    }

    std::size_t arg_start = curr_line.find_first_not_of(' ', space_idx);
    if (arg_start == std::string::npos) {
        argument = "";
        return;
    }

    argument = curr_line.substr(arg_start);
}

void print_list(std::vector<std::string> const& todo_list) {
    if (todo_list.empty()) {
        std::cout << "List is empty.\n";
        return;
    }

    int idx = 0;
    for (const auto& element : todo_list) {
        std::cout << idx << ' ' << element << '\n';
        idx++;
    }
}

void add_element(std::vector<std::string> &todo_list, std::string const& argument) {
    if (argument.empty()) {
        std::cout << "\"add <argument>\" needs an argument.\n";
        return;
    }

    todo_list.push_back(argument);
}

void remove_element(std::vector<std::string>& todo_list, std::string const& argument) {
    if (argument.empty()) {
        std::cout << "\"remove <argument>\" needs an argument.\n";
        return;
    }

    for (const auto& character : argument) {
        if (character < '0' || character > '9') {
            std::cout << "\"" << argument << "\" is not a number.\n";
            return;
        }
    }

    std::size_t curr_id;
    try {
        curr_id = std::stoul(argument);
    } catch (const std::out_of_range&) {
        std::cout << "\"" << argument << "\" is too big.\n";
        return;
    } catch (const std::invalid_argument&) {
        std::cout << "\"" << argument << "\" is not a number.\n";
        return;
    }

    if (curr_id >= todo_list.size()) {
        std::cout << "No element has id " << argument << ".\n";
        return;
    }

    todo_list.erase(todo_list.begin() + curr_id);
}

int main() {

    std::vector<std::string> todo_list;
    std::string curr_line;

    while (std::getline(std::cin, curr_line)) {
        std::string command, argument;

        split_command(curr_line, command, argument);

        if (command == "quit") {
            break;
        } else if (command == "add") {
            add_element(todo_list, argument);
        } else if (command == "remove") {
            remove_element(todo_list, argument);
        } else if (command == "list") {
            print_list(todo_list);
        } else {
            std::cout << "Wrong command.\n";
        }
    }

    return 0;
}
