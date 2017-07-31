//Albert Han
//lexer.h
//Lexer tokenizes the string input and outputs tokens
#ifndef COMPILER_CPP_LEXER_H_
#define COMPILER_CPP_LEXER_H_
#include <string>
#include "token.h"

namespace comp {

class Lexer {
    public:
        std::string text;
        size_t pos;
        Lexer() = default;
        Lexer(std::string text) :
            text(text), pos(0) {}
        token get_next_token();
    private:
        void skip_whitespace_();
        std::string get_int_string_();
};

} //namespace comp

#endif // COMPILER_CPP_LEXER_H_
