#include <iostream>
#include <string>

#include "token.h"
#include "interpreter.h"
int main()
{
    std::string s;
    std::cout << "calc> ";
    while (std::getline(std::cin, s)) {
        comp::interpreter interp(s);
        std::cout << interp.interpret();
        std::cout << std::endl;
        std::cout << "calc> ";
    }
    std::cout << std::endl;
    return 0;
}
