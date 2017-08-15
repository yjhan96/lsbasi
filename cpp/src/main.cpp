#include <iostream>
#include <string>

#include "interpreter.h"
int main()
{
    std::string s;
    std::cout << "calc> ";
    while (std::getline(std::cin, s)) {
        comp::Lexer lexer(s);
        comp::Parser parser(&lexer);
        comp::Interpreter interp(&parser);
        std::cout << interp.interpret();
        std::cout << std::endl;
        std::cout << "calc> ";
    }
    std::cout << std::endl;
    return 0;
}
