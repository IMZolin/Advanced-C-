//
// Created by zolin on 12.09.2022.
//

#ifndef LESSON_2_TREE_H
#define LESSON_2_TREE_H
#include <string>
#include <iostream>
#include <fstream>

struct Node{
    std::string* keys;
    Node* parent;
    Node** children;
};
class Tree {
public:
    Tree();
    ~Tree();
    void Parser();
    void traverse();

private:
    Node* root;
    int numChildren;
    std::ifstream input;
};



#endif //LESSON_2_TREE_H
