#include "Tree.h"
Tree::Tree(std::string value)
{
    root = new Node(value);
}
Tree::~Tree()
{
    delete root;
}
void Tree::makeTree(std::vector<std::string> inp_vec) {
    root->setKey(inp_vec[0]);
    inp_vec.erase(inp_vec.begin());
    Node* tmp = root;
    for(auto item: inp_vec) {
        if(item[0] != 47) {
            Node* new_child = new Node;
            new_child->setKey(item);
            new_child->setParent(tmp);
            tmp->getChildren().push_back(new_child);
            tmp = new_child;
        }
        else {
            tmp = tmp->getParent();
        }
    }
}
Node* Tree::Find(const std::string &element_name, Node *node) {
    if(root->getKey() == element_name) {return root;}
    static Node* buffer = root;
    if(!node->getChildren().empty()) {
        for(auto item: node->getChildren()) {
            node = item;
            if(node->getKey() == element_name) {
                buffer = node;
                break;
            }
            else {
                Find(element_name, node);
                if(buffer->getKey() == element_name) {break;}
            }
        }
    }
    return buffer;
}
void Tree::shortestPath(const std::string &s1, const std::string &s2) {
    Node* n1 = Find(s2, root);
    Node* n2 = Find(s1, root);
    std::vector<Node*> vec1;
    std::vector<Node*> vec2;

    Node* tmp = n1;
    while (tmp != root) {
        vec1.insert(vec1.begin(), tmp);
        tmp = tmp->getParent();
    }
    vec1.insert(vec1.begin(), tmp);  // оно вероятно потом мной удалится, но на случай Root все-таки надо
    tmp = n2;
    while (tmp != root) {
        vec2.insert(vec2.begin(), tmp);
        tmp = tmp->getParent();
    }
    vec2.insert(vec2.begin(), tmp);

    int flag = 0;  //  только для красоты вывода
    while(vec1[0]->getKey() == vec2[0]->getKey()) {
        if(vec1[0]->getKey() == s1 || vec1[0]->getKey() == s2) {
            flag = 1;
            if(vec1.size() == 1) {
                vec1.clear();
            } else {
                vec2.clear();
            }
            break;
        }
        vec1.erase(vec1.begin());  //  не уверен в скорости работы erase
        vec2.erase(vec2.begin());
    }

    for(auto const& item: vec1) {
        std::cout << item->getKey() << " <- ";
    }
    if(!flag) {
        std::cout << "\n" << vec1[0]->getParent()->getKey() << "\n";
    }
    for(auto const& item: vec2) {
        std::cout << item->getKey() << " -> ";
    }
}
void Tree::Print(Node* node) {
    while(!node->getChildren().empty())
    {
        for(auto item: node->getChildren())
        {
            node = item;
            node->Print();
            Print(node);
        }
    }
    if(node->getChildren().empty() && node!= nullptr)
    {
        std::cout << node->getKey() << std::endl;
    }
}
void Tree::Delete(Node* node) {
    if(!node->getChildren().empty()) {
        for(auto item: node->getChildren()) {
            node = item;
            Delete(node);
            delete item;
        }
    }
}

