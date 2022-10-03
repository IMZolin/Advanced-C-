#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Node {
public:
    std::string name;
    Node* parent;
    std::vector<Node*> child; //  array of nodes

public:
    Node() {name = "unnamed"; parent = nullptr;}

};

class Tree {
public:
    Node* head;

public:
    Tree(std::string RootName) {head = new Node; head->parent = nullptr; head->name = RootName;}
    ~Tree() { DeleteTree(head); delete head; }

    Tree(Tree const& other) {
        head = new Node;
        head->name = other.head->name;
        AddElements(other.head, head);
    }

    Tree& operator = (Tree const& lhs) {
        head = new Node;
        head->name = lhs.head->name;
        AddElements(lhs.head, head);
        return *this;
    }

    Tree(Tree&& rhs) {
        head = rhs.head;
        rhs.head = nullptr;
    }

    Tree& operator = (Tree && rhs) {
        DeleteTree(head);
        head = rhs.head;
        rhs.head = nullptr;
    }

    void MakeTree(std::vector<std::string> input_vector) {
        head->name = input_vector[0];
        input_vector.erase(input_vector.begin());  //  Too much weight of operation ?
        Node* tmp = head;
        for(auto item: input_vector) {
            if(item[0] != 47) {
                Node* new_child = new Node;
                new_child->name = item;
                new_child->parent = tmp;
                tmp->child.push_back(new_child);
                tmp = new_child;
            }
            else {
                tmp = tmp->parent;
            }
        }
    }

    Node* FindElement(std::string const& element_name, Node* tmp) {
        /**
         * так себе реализация - рекурсивный вызов не-void функции без возврата. Да еще и static
         * в рекурсии
         */
        if(head->name == element_name) {return head;}
        static Node* buffer = head;
        if(!tmp->child.empty()) {                //  && buffer == nullptr
            for(auto item: tmp->child) {  //  хитрая строка, на которую не влияет static
                tmp = item;
                if(tmp->name == element_name) {
                    buffer = tmp;
                    break;
                }
                else {
                    FindElement(element_name, tmp);
                    if(buffer->name == element_name) {break;}
                }
            }
        }
        return buffer;
    }

    void FastTrack(std::string const& s1, std::string const& s2) {
        /**
         * Есть вопросы по оптимизации
         */
        Node* n1 = FindElement(s2, head);
        Node* n2 = FindElement(s1, head);
        std::vector<Node*> vec1;
        std::vector<Node*> vec2;

        Node* tmp = n1;
        while (tmp != head) {
            vec1.insert(vec1.begin(), tmp);
            tmp = tmp->parent;
        }
        vec1.insert(vec1.begin(), tmp);  // оно вероятно потом мной удалится, но на случай Root все-таки надо
        tmp = n2;
        while (tmp != head) {
            vec2.insert(vec2.begin(), tmp);
            tmp = tmp->parent;
        }
        vec2.insert(vec2.begin(), tmp);

        int flag = 0;  //  только для красоты вывода
        while(vec1[0]->name == vec2[0]->name) {
            if(vec1[0]->name == s1 || vec1[0]->name == s2) {
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
            std::cout << item->name << " <- ";
        }
        if(!flag) {
            std::cout << "\n" << vec1[0]->parent->name << "\n";
        }
        for(auto const& item: vec2) {
            std::cout << item->name << " -> ";
        }

    }

    void PrintTree(Node* tmp) {
        if(!tmp->child.empty()) {
            for(auto item: tmp->child) {  //  хитрая строка, на которую не влияет static
                tmp = item;
                std::cout << tmp->name << std::endl;
                PrintTree(tmp);
            }
        }
    }

    void AddElements(Node* const& other, Node* node) {
        if(!other->child.empty()) {
            int i = 0;
            for (auto item: other->child) {
                Node* new_node = new Node;
                new_node->name = item->name;
                new_node->parent = node;
                node->child.push_back(new_node);
                AddElements(other->child[i], new_node);
                i++;
            }
        }
    }

    void DeleteTree(Node* tmp) {
        if(tmp != nullptr && !tmp->child.empty()) {
            Node* buffer = tmp;
            for(auto item: tmp->child) {  //  хитрая строка, на которую не влияет static
                tmp = item;
                DeleteTree(tmp);
                delete item;
            }
            buffer->child.clear();
        }
    }

    void PrintTree_2(Node* const& node) {
        //std::cout << node->name << std::endl;
        for(auto items: node->child) {
            std::cout << items->name << " ";
        }
        std::cout << std::endl;
        for(auto items: node->child) {
            PrintTree_2(items);
            //std::cout << std::endl;
        }
    }

};

class Source {
public:
    std::string filename;
    std::vector<std::string> vec;

public:
    Source(std::string filename_) {filename = filename_;}
    ~Source() {vec.clear();}

    void Read() {
        std::ifstream input;
        input.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        try {
            input.open(filename);
            std::string teg;
            std::string buffer;
            input >> teg;
            buffer = teg;
            while (teg != "/" + buffer) {
                vec.push_back(teg);
                input >> teg;
            }
            vec.push_back(teg);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
};

int main() {
    std::string filename = "C:\\Users\\zolin\\University\\Science_programming\\Lessons\\Lesson-2-3\\file.txt";

    Tree t1("Root");
    Source s1(filename);
    s1.Read();

    t1.MakeTree(s1.vec);
    t1.PrintTree(t1.head);
    std::cout << std::endl;
    t1.FastTrack("Lvl_1_2", "Lvl_2_2");

    std::cout << std::endl;
    std::cout << std::endl;

    Tree t2 = t1;
    Tree t3(std::move(t2));
    t3.PrintTree(t3.head);

    Tree t4("Root");
    t4 = std::move(t3);
    t4.PrintTree(t4.head);

    return 0;
}
