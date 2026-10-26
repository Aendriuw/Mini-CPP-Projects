#include <iostream>
#include <memory>
#include <stdexcept>

class Time {
public:
    Time(int start_hour, int start_minute) : hour_(start_hour), minute_(start_minute) {
        if (start_hour < 0 || start_hour > 23) {
            throw std::invalid_argument("hour must be 0-23");
        }

        if (start_minute < 0 || start_minute > 59) {
            throw std::invalid_argument("minute must be 0-60");
        }
    }

    [[nodiscard]] bool increase_time(int hours, int minutes) {
        if (hours < 0 || minutes < 0 || minutes > 59) {
            return false;
        }

        hour_ += minutes / 60 + (hours % 24);
        minute_ += minutes % 60;

        if (minute_ >= 60) {
            minute_ %= 60;
            hour_++;
        }

        hour_ %= 24;

        return true;
    }

    int get_hour() const {
        return hour_;
    }

    int get_minute() const {
        return minute_;
    }
private:
    int hour_, minute_;
};

int main() {
    auto curr_time = std::make_unique<Time>(22, 4);

    std::cout << curr_time->get_hour() << ':' << curr_time->get_minute() << '\n';

    if (!curr_time->increase_time(1, 24)) {
        std::cout << "Wrong input.\n";
    }

    std::cout << curr_time->get_hour() << ':' << curr_time->get_minute() << '\n';

    try {
        curr_time = std::make_unique<Time>(60, 20);
    } catch (const std::invalid_argument&) {
        std::cout << "Please provide a valid time: hour is 0-23, minute is 0-59\n"; 
    }
}
