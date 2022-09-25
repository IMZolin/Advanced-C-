#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * В данном коде большой баг: использование статических переменных в методах класса
 * губительно влияет на работоспособность программы при создании более чем одного объекта
 * или просто при вызове одного и того же метода как минимум дважды.
 * Поэтому надо все переписывать, наверное
 * ...
 * Вроде исправил
 */

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

    void DeleteTree(Node* tmp) {
        if(!tmp->child.empty()) {
            for(auto item: tmp->child) {  //  хитрая строка, на которую не влияет static
                tmp = item;
                DeleteTree(tmp);
                delete item;
            }
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

void fun(int& x) {
    x++;
}

int& fun2(int& x) {
    return x;
}

template <typename T>
void print (const T& x) {
    std::cout << &x;
}

int main() {
    std::string filename = "C:\\Users\\Le\\Desktop\\AppMath\\CPP\\2_Lesson\\file.txt";

    Tree t1("Root");
    Source s1(filename);
    s1.Read();

    t1.MakeTree(s1.vec);
    t1.PrintTree(t1.head);
    std::cout << std::endl;
    t1.FastTrack("Lvl_1_2_3", "Lvl_2_1");

    std::cout << std::endl;
    int x = 5;
    int &rx = x;

    fun2(x) = 21;
    std::cout << x;

    print <int> (45);



    return 0;
}
