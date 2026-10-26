# Mini C++ Projects

Random very small educational C++ projects that represent implementations of small core parts for bigger projects.

## F1
- Simple To-Do list with 4 commands that parses input from the user.
- The main focus of this code is the parsing part.

### Build
```bash
g++ -std=c++20 -Wall -Wextra -o main main.cpp
```

### Run
```bash
./main
```

## F2
- Played around with constructors/deconstructors, smart pointers, RAII.

### Build
```bash
g++ -std=c++20 -Wall -Wextra -o classA classA.cpp \
g++ -std=c++20 -Wall -Wextra -o classB classB.cpp
```

### Run
```bash
./classA
./classB
```

## F3
- Takes lines from a "./in.txt" file and writes lines that only contain a number and no other garbage characters into a "./out.txt" file.
- The focus here was on line parsing safely, optional types, packing a C API with RAII and filesystem work.

### Build
```bash
g++ -std=c++20 -Wall -Wextra -o main main.cpp
```

### Run
```bash
./main
```
