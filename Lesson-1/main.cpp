#include <iostream>
#include "List.h"
int main() {
    List* list = new List(1);
    list->Insert(2);
    list->Insert(3);
    list->Insert(4);
    list->Insert(5);
    list->Print();
    List* copy_list = new List(*list);
    list->Reverse();
    std::cout<<"\n";
    list->Print();
    std::cout<<"\n";
    copy_list->Print();
    return 0;
}