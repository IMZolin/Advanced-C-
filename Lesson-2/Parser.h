#ifndef LESSON_2_PARSER_H
#define LESSON_2_PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Parser {
public:
    Parser(std::string filename_){filename = filename_;}
    ~Parser(){vec.clear();}
    void Parse();
    void printVec();
    std::vector<std::string> getVec(){return vec;}
private:
    std::string filename;
    std::vector<std::string> vec;
};


#endif //LESSON_2_PARSER_H


