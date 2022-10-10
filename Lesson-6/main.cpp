#include <iostream>
#include <functional>
#include<stack>
#define MAX_LENGTH 5

class StringStack{
private:
    std::string str;
    std::stack<std::function<std::string(std::string)>> ops;
public:
    std::string Run(){
        while(!ops.empty()){
            str = (ops.top())(str);
            ops.pop();
        }
        return str;
    }
    void clear_ops(){
        while(!ops.empty()){
            ops.pop();
        }
    }
    void push_ops(std::function<std::string(std::string)> op){
        ops.push(op);
    }
    void pop_ops(){
        ops.pop();
    }
    void set_string(std::string set_str){
        str = set_str;
    }
    void print(){
        std::cout<<str<<std::endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    StringStack stringStack;
    stringStack.set_string("hello");
    stringStack.print();
    stringStack.push_ops([](std::string str){str.append("1"); return str;});
    stringStack.pop_ops();
    stringStack.push_ops([](std::string str){str.append("2"); return str;});
    stringStack.push_ops([](std::string str){str.append("3"); return str;});
    stringStack.push_ops([](std::string str){str.append("4"); return str;});
    stringStack.pop_ops();
    stringStack.push_ops([](std::string str){str.append("5"); return str;});
    std::cout<<stringStack.Run();
    return 0;
}
