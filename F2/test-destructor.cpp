#include <iostream>

class Noisy {
public:
    Noisy()  { std::cout << "created\n"; }
    ~Noisy() { std::cout << "destroyed\n"; }
};

void f() {
    Noisy n;                 // "created"
    if (1) return;   // "destroyed" still prints
}

int main() {
    f();
}
