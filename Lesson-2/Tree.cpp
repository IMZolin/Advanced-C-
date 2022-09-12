#include "Tree.h"

Tree::Tree()
{
    root = new Node();
    numChildren = 0;
}
Tree::~Tree()
{
    delete root;
}
void Tree::traverse() {
}
void Tree::Parser() {
    std::ifstream input;
    input.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    std::string y;
    try {
        input.open("C:\\Users\\zolin\\University\\Science_programming\\Lessons\\Lesson-2\\example.txt");
        input >> y;
        std::cout << y;
        input.close();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
