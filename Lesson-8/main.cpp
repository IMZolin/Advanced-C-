#include "Stack.h"

int main() {
    auto x { 1 };

    Stack<int>* stack = Stack<int>::create(1, 2);
    if (*stack) {
        cout << "not empty" << endl;
    }
    stack->print();

    /*Stack<std::string>* stack_str = new Stack<std::string>();
    std::string str_el = "hello";
    stack_str->push(str_el);
    stack_str->print();*/
}
