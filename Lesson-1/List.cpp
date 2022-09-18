#include "List.h"
Node::Node(){
    this->data = 0;
    this->next = nullptr;
}
Node::Node(int value) {
    this->data = value;
    this->next = nullptr;
}
Node::Node(const Node& tmp)
{
    this->data = tmp.data;
    this->next = tmp.next;
}
List::~List()
{
    Node* currentNode = this->head; // initialize current node to root
    while (currentNode)
    {
        Node* nextNode = currentNode->getNext();    // get next node
        delete currentNode;                         // delete current
        currentNode = nextNode;                     // set current to "old" next
    }
}
bool List::isEmpty() {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
}
void List::Insert(int data) {
    Node* new_node = new Node(data);
    Node* node = this->head;
    while(node->getNext() != nullptr)
    {
        node = node->getNext();
    }
    node->setNext(new_node);
}
void List::Print() {
    Node* node = this->head;
    while(node != nullptr)
    {
        node->Print();
        std::cout<<" -> ";
        node = node->getNext();
    }
    std::cout<<"NULL";
}
void List::Reverse() {
    Node* cur = this->head;
    Node *prev = nullptr, *next = nullptr;
    while (cur != nullptr) {
        // Store next
        next = cur->getNext();
        // Reverse current node's pointer
        cur->setNext(prev);
        // Move pointers one position ahead.
        prev = cur;
        cur = next;
    }
    this->head = prev;
}
List::List(List const& list)
{
    if(!list.head)
    {
        this->head = nullptr;
        return;
    }
    this->head = new Node(list.head->getData());
    Node* listCurNode = list.head;
    Node* thisCurNode = this->head;
    while(listCurNode->getNext() != nullptr)
    {
        Node* newNode = new Node(listCurNode->getNext()->getData());
        thisCurNode->setNext(newNode);
        thisCurNode = thisCurNode->getNext();
        listCurNode = listCurNode->getNext();
    }
}