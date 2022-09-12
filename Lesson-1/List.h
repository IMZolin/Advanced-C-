#ifndef LESSON_1_LIST_H
#define LESSON_1_LIST_H

class Node{
private:
    int data;
    Node* next;
public:
    Node();
    Node(int value);
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
    List(List const& list);
    bool isEmpty();
};


#endif //LESSON_1_LIST_H
