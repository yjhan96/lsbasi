/* Albert Han
 * parser.h
 * Parser creates an abstract-syntax tree (AST)
 * and returns the tree to the interpreter.
 */

#ifndef COMPILER_CPP_PARSER_H_
#define COMPILER_CPP_PARSER_H_
#include <string>

#include "token.h"
#include "lexer.h"

namespace comp {

struct AST {
    public:
        Token token;
        AST * left, * right;
        AST() = default;
        AST(AST *l, Token t, AST *r) :
            token(t), left(l), right(r) {}
};
typedef AST* AST_t;

struct BinOp : AST {
    public:
        using AST::AST;
};

struct Num : AST {
    public:
        Num(Token t) :
            AST(NULL, t, NULL) {}
};

class Parser {
    public:
        Lexer * lexer;
        Token cur_token;
        Parser(Lexer * lex) {
            lexer = lex;
            cur_token = lexer -> get_next_token();
        }
        AST_t parse();
    private:
        // Eats the current token and gets the next token
        void _eat(token_type type);
        // Gets the int value of int token
        AST_t _factor();
        AST_t _term();
        AST_t _expr();
};
} //namespace comp

#endif // COMPILER_CPP_PARSER_H_
