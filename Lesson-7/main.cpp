#include "Stack.h"

int main() {
    auto x { 1 };
    Stack<int>* stack = new Stack<int>();
    if (*stack) {
        cout << "not empty" << endl;
    }
    for (int i = 0; i < 15; ++i) {
        stack->push(i);
    }
    stack->print();
    Stack<std::string>* stack_str = new Stack<std::string>();
    std::string str_el = "hello";
    stack_str->push(str_el);
    stack_str->print();
}
