#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#define SIZE 10

class Stack {
    int *arr;
    int top;
    int capacity;

public:
    Stack(int capacity = SIZE);

    ~Stack();

    Stack(const Stack &other) : capacity(other.capacity), top(other.top), arr(nullptr) {
        if (capacity) {
            arr = new int[capacity];
            for (int i = 0; i != capacity; i++) {
                arr[i] = other.arr[i];
            }
        }
    }

    Stack &operator=(const Stack &other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            arr = new int[other.capacity + 1];
            for (int i = 0; i != other.capacity; i++) {
                arr[i] = other.arr[i];
            }
            top = other.top;
        }
        return *this;
    }

    Stack (Stack && other){
        arr = other.arr;
        top = other.top;
        capacity = other.capacity;
        other.arr = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    Stack& operator =(Stack&& other) noexcept{
        delete[] arr;
        arr = other.arr;
        top = other.top;
        capacity = other.capacity;
        other.arr = nullptr;
        other.top = 0;
        other.capacity = 0;
        return *this;
    }

    void push(int);
    int pop();
    int peek();

    int size();
    bool isEmpty();
    bool isFull();
};

Stack::Stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}
Stack::~Stack() {
    delete[] arr;
}
void Stack::push(int x)
{
    if (isFull())
    {
        exit(EXIT_FAILURE);
    }

    cout << "add element — "<< x << endl;
    arr[++top] = x;
}

int Stack::pop()
{
    if (isEmpty())
    {
        exit(EXIT_FAILURE);
    }

    cout << "pop element — " <<peek() << endl;

    return arr[top--];
}
int Stack::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
int Stack::size() {
    return top + 1;
}
bool Stack::isEmpty() {
    return top == -1;
}
bool Stack::isFull() {
    return top == capacity - 1;
}

class CoolStack : public Stack {
public:
    CoolStack(int maxSize): Stack(maxSize){}
    CoolStack(const CoolStack& other): Stack(other){}
    CoolStack(CoolStack&& other): Stack(std::move(other)){}

    void push(vector<int>);
    void push(int* arr, int size);
    int* pop(int size);
};

void CoolStack :: push(vector<int> v){
    auto iter = v.begin();
    while (iter!=v.end()){
        Stack ::push(*iter);
    }
}

void CoolStack :: push(int* arr_, int size){
    for (int i = 0; i!=size; i++ ){
        Stack:: push(arr_[i]);
    }
}

int* CoolStack:: pop(int size){
    int* array = new int[size];
    for (int i = 0; i!=size; i++){
        array[i] = Stack:: pop();
    }
    return array;
}

int main()
{
    Stack pt(3);
    Stack pt1(3);
    Stack pt2(3);


    pt.push(1);
    pt.push(2);

    pt.pop();
    pt.pop();

    pt.push(3);
    pt1 = Stack(pt);
    cout << "The top element pt is " << pt.peek() << endl;
    cout << "The stack capacity is " << pt.size() << endl;
    cout << "----------------------------" << endl;
    cout << "Copy constructor\n" << endl;
    cout << "The top element pt1 is " << pt1.peek() << endl;
    cout << "The stack capacity pt1 is " << pt1.size() << endl;
    cout << "----------------------------" << endl;

    pt.push(1);
    pt.push(2);



    pt.pop();

    if (pt.isEmpty()) {
        cout << "The stack is empty\n";
    }
    else {
        cout << "The stack is not empty\n";
    }

    return 0;
}



