#include "List.h"
Node::Node(){
    data = 0;
    next = nullptr;
}
Node::Node(int value) {
    data = value;
    next = nullptr;
}
bool List::isEmpty() {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
}