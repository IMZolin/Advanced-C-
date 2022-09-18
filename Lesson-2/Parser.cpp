#include "Parser.h"
void Parser::Parse() {
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
void Parser::printVec() {
    for(auto item:this->vec)
    {
        std::cout<< item<<std::endl;
    }
}