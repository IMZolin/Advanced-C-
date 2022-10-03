#include<iostream>
#include<sstream>
using namespace::std;

template <typename T> class Stack {
public:
    int capacity;
    int size;
    T* data;

    Stack() {
        capacity = 10;
        data = new T[10];
        size = 0;
    }

    Stack(Stack const& stack) {
        data = new T[stack.capacity];
        size = stack.size;
        capacity = stack.capacity;
        for (int i = 0; i < stack.size; ++i) {
            data[i] = stack.data[i];
        }
    }

    Stack(Stack&& stack) {
        data = new T[stack.capacity];
        for (int i = 0; i < stack.size; ++i) {
            data[i] = stack.data[i];
        }
        size = stack.size;
        capacity = stack.capacity;
        stack.data = nullptr;
        stack = nullptr;
    }

    //+
    Stack& operator=(Stack const& stack) {
        if (size < stack.capacity) {
            this = resize(this, stack.capacity);
        }
        for (int i = 0; i < stack.size; ++i) {
            data[i] = stack.data[i];
        }
        return this;
    }

    // +
    Stack& operator=(Stack&& stack) {
        if (this) {
            delete[] data;
        }
        data = stack.data;
        capacity = stack.capacity;
        size = stack.size;
        stack.data = nullptr;
        stack.capacity = 0;
        stack.size = 0;
        return *this;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            pop();
        }
    }

    ~Stack() {
        delete[] data;
    }

    void push(T const& el) {
        if (size == capacity-1) {
            capacity *= 2;
            data = resize(data, capacity);
        }
        data[size] = el;
        size++;
    }

    T* resize(T* data, int capacity) {
        T* tmp = new T[capacity];
        for (int i = 0; i < size; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        return tmp;
    }

    T top() {
        return data[size - 1];
    }

    T pop() {
        T tmp = data[size - 1];
        data[size - 1] = 0;
        size--;
        return tmp;
    }

    operator bool() {
        return size == 0;
    }

    void print() {
        cout << endl;
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

};

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
    if (stack) {
        cout << "not empty";
    }
    Stack<int>* second = new Stack<int>(*stack);
    second->print();
    Stack<int>* third = new Stack<int>();
    *third = std::move(*second);
    third->print();
    second->print();
    if (second) {
        cout << "not empty";
    }
}

