#ifndef LESSON_8_STACK_H
#define LESSON_8_STACK_H


#include<iostream>
#include<sstream>
#include <vector>

using namespace::std;
//static Stack create(T args..)
//clone
template <typename T> class Stack {
private:
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
public:
    int capacity;
    int size;
    T* data;
    //shared_ptr
    static void init(Stack<T>* stack, T head)
    {
        stack->push(head);
    }
    template<typename ...Arg>
    static void init(Stack<T>* stack, T head, Arg... tail)
    {
        stack->push(head);
        init(stack, tail...);
    }
    template<typename ...Arg>
    static Stack<T>* create(Arg... args)
    {
        auto* stack = new Stack<T>();
        stack->init(stack, args...);
        return stack;
    }
    template<typename ...Arg>
    static Stack<T> clone(Stack& other)
    {
        Stack stack();
        std::vector<T> buf;
        while(other)
        {
            buf.push_back(other.top());
            other.pop();
        }
        for(auto it = buf.rbegin(); it != buf.rbegin(); ++it)
        {
            stack.push(*it);
            other.push(*it);
        }

        return std::move(stack);
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






#endif //LESSON_8_STACK_H
