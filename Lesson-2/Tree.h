#ifndef LESSON_2_TREE_H
#define LESSON_2_TREE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Node{
public:
    Node(){key = "unnamed"; parent = nullptr;}
    Node(std::string value){key = value; parent = nullptr;}
    Node* getParent(){return parent;}
    std::vector<Node*> getChildren(){return children;}
    std::string getKey(){return key;}
    void setKey(std::string value){this->key = value;}
    void setParent(Node* parent){this->parent = parent;}
    void setChildren(std::vector<Node*> children){this->children = children;}
    void Print(){std::cout << "[" << this->getKey() << "]";}
private:
    std::string key;
    Node* parent;
    std::vector<Node*> children;
};
class Tree {
public:
    Tree(std::string value);
    ~Tree();
//    void makeTree(std::vector<std::string> inp_vec);
//    Node* Find(std::string const& element_name, Node* node);
//    void shortestPath(std::string const& s1, std::string const& s2);
    void Print(Node* node);
    void Delete(Node* node);
    Node* getRoot(){return root;}
private:
    Node* root;
};
#endif //LESSON_2_TREE_H
