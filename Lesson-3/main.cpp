#include <iostream>
// Header File including all string functions
#include <string>

using namespace std;

// Taking size of stack as 10
#define SIZE 5

template <class T> class Stack {
public:
    Stack();
    Stack(int size);
    Stack(Stack<T> const& other);
    Stack(Stack&& rhs);
    Stack& operator = (Stack const& lhs);
    Stack& operator = (Stack && rhs);
    void push(T k);
    T pop();
    T topElement();
    bool isFull();
    bool isEmpty();
    ~Stack();
private:
    int top;
    int capacity;
    T* arr;
};


template <class T> Stack<T>::Stack() { top = -1; }
template <class T> Stack<T>::Stack(int size) { top = -1; capacity = size; arr = new T[size];}
template <class T> Stack<T>::Stack(const Stack &other) : capacity(other.capacity), top(other.top), arr(nullptr) {
    if (capacity) {
        arr = new int[capacity];
        for (int i = 0; i != top; i++) {
            arr[i] = other.arr[i];
        }
    }
}
//template <class T> Stack<T>::(Stack<T>&& rhs)
//{
//    arr = rhs.arr;
//    capacity = rhs.capacity;
//    rhs.arr = NULL;
//}
template <class T> Stack<T>::~Stack() {
    delete[] arr;
}
template <class T> void Stack<T>::push(T k)
{
    if (isFull()) {
        std::cout << "Stack is full\n";
    }
    top = top + 1;
    arr[top] = k;
}
template <class T> bool Stack<T>::isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}
template <class T> bool Stack<T>::isFull()
{
    return top == capacity - 1;
}
template <class T> T Stack<T>::pop()
{
    T popped_element = arr[top];
    top--;
    return popped_element;
}
template <class T> T Stack<T>::topElement()
{
    T top_element = arr[top];
    return top_element;
}

int main()
{
    Stack<int> int_stack(3);
    //Stack<int> int_stack2 = int_stack;
    Stack<string> string_stack(1);
    string_stack.push("hello");
    int_stack.push(2);
    int_stack.push(54);
    int_stack.push(255);
    std::cout << int_stack.isEmpty();
    std::cout << string_stack.isEmpty();
    //std::cout << int_stack2.isEmpty();


    return 0;
}