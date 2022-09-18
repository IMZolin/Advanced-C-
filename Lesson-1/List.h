#ifndef LESSON_1_LIST_H
#define LESSON_1_LIST_H
#include <iostream>
class Node{
private:
    int data;
    Node* next;
public:
    Node();
    Node(int value);
    Node(const Node& tmp);
    void Print(){std::cout << "[" << this->getData() << "]";}
    Node* getNext(){ return next; }
    int getData(){ return data; }
    void setData(int value){ this->data = value;}
    void setNext(Node* _next){ this->next = _next; }
};

class List {
private:
    Node* head;
public:
    List(){ head = nullptr; }
    List(int value){ this->head = new Node(value); }
    List(List const& list);
    bool isEmpty();
    void Insert(int data);
    void Print();
    void Reverse();
    ~List();
};


#endif //LESSON_1_LIST_H