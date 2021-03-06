/*
 * Albert Han
 * token.h
 * Token is a class that represents the token during lexical analysis.
 * Token types are represented in enum type.
 */

#ifndef COMPILER_CPP_TOKEN_H_
#define COMPILER_CPP_TOKEN_H_
#include <string>

namespace comp {

enum token_type {
    INIT,
    //Integer type
    INTEGER,
    //Operator type
    PLUS, MINUS, MULT, DIVS,
    //Paren type
    LPAREN, RPAREN,

    BEGIN, END, DOT,

    ID, ASSIGN, SEMI,
    //Eof type
    EoF
};

static const char * token_strings[] = {"INIT", 
                                       "INTEGER", 
                                       "PLUS", "MINUS", "MULT", "DIVS", 
                                       "LPAREN", "RPAREN",
                                       "BEGIN", "END", "DOT",
                                       "ID", "ASSIGN", "SEMI",
                                       "EoF"};

class Token {
    public:
        token_type type;
        // String representation of token value
        std::string val;

        Token() = default;
        Token(token_type type, std::string s) :
            type(type), val(s) {}
        operator std::string();
};

} // namespace comp

#endif // COMPILER_CPP_TOKEN_H_
