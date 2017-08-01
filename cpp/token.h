/*
 * Albert Han
 * token.h
 * Token is a class that represents the token during lexical analysis.
 * Token types are represented in enum type.
 */

#ifndef COMPILER_CPP_TOKEN_H_
#define COMPILER_CPP_TOKEN_H_
#include <string>
#include <set>

namespace comp {

enum token_type {
    INIT,
    INTEGER,
    PLUS,
    MINUS,
    MULT,
    DIVS,
    LPAREN,
    RPAREN,
    EoF
};

static const char * token_strings[] = {"INIT", "INTEGER", "PLUS", "MINUS",
                                       "MULT", "DIVS", "LPAREN", "RPAREN",
                                       "EoF"};

static const std::set<token_type> operations = {PLUS, MINUS, MULT, DIVS};

class token {
    public:
        token_type type;
        // String representation of token value
        std::string val;

        token() = default;
        token(token_type type, std::string s) :
            type(type), val(s) {}
        operator std::string();
};

} // namespace comp

#endif // COMPILER_CPP_TOKEN_H_
