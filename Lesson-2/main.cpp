#include "Parser.h"
#include "Tree.h"
int main() {
    std::string filename = "C:\\Users\\zolin\\University\\Science_programming\\Lessons\\Lesson-2\\example.txt";
    Parser parser(filename);
    Tree tree ("Root");
    parser.Parse();
//    tree.Print(tree.getRoot());
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
