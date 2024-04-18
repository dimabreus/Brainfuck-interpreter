#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " file.bf" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<char> code((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();

    std::vector<unsigned char> tape(30000, 0);
    size_t ptr = 0;

    std::stack<size_t> loops;
    for (size_t pc = 0; pc < code.size(); ++pc) {
        switch (code[pc]) {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++tape[ptr];
                break;
            case '-':
                --tape[ptr];
                break;
            case '.':
                std::cout << tape[ptr];
                break;
            case ',':
                tape[ptr] = std::cin.get();
                break;
            case '[':
                if (tape[ptr] == 0) {
                    size_t depth = 1;
                    while (depth > 0) {
                        ++pc;
                        if (code[pc] == '[') ++depth;
                        if (code[pc] == ']') --depth;
                    }
                } else {
                    loops.push(pc);
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    pc = loops.top();
                } else {
                    loops.pop();
                }
                break;
        }
    }

    return 0;
}
