#include <memory>
#include <iostream>

int main() {
    auto p = std::make_unique<std::string>("hello");   // allocates and constructs
    std::cout << *p << ' ' << p->size() << '\n';
}
