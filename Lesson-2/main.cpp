#include "Parser.h"

int main() {
    std::string filename = "C:\\Users\\zolin\\University\\Science_programming\\Lessons\\Lesson-2\\example.txt";
    Parser parser(filename);
    parser.Parse();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
