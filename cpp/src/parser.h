/* Albert Han
 * parser.h
 * Parser creates an abstract-syntax tree (AST)
 * and returns the tree to the interpreter.
 */

#ifndef COMPILER_CPP_PARSER_H_
#define COMPILER_CPP_PARSER_H_
#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"

namespace comp {

struct AST {
    public:
        AST() = default;
        virtual std::string get_id() = 0;
};
typedef AST* AST_t;

struct Compound : AST {
    public:
        std::vector<AST_t> children;
        Compound(std::vector<AST_t> nodes) :
            children(nodes) {}
        std::string get_id() { return "Compound"; }
};
typedef Compound* Compound_t;

struct Assign : AST {
    public:
        Token token;
        AST *left, *right;
        Assign (AST *l, Token t, AST *r) :
            token(t), left(l), right(r) {}
        std::string get_id() { return "Assign"; }
};
typedef Assign* Assign_t;

struct Var : AST {
    Token token;
    std::string val;
    Var (Token t) : token(t) {
        val = t.val;
    }
    std::string get_id() { return "Var"; }
};
typedef Var* Var_t;

struct NoOp : AST {
    NoOp() = default;
    std::string get_id() { return "NoOp"; }
};
typedef NoOp* NoOp_t;

struct BinOp : AST {
    public:
        Token token;
        AST *left, *right;
        BinOp (AST *l, Token t, AST *r) :
            token(t), left(l), right(r) {}
        std::string get_id() {return "BinOp"; }
};
typedef BinOp* BinOp_t;

struct Num : AST {
    public:
        Token token;
        Num (Token t) : token(t) {}
        std::string get_id() {return "Num"; }
};
typedef Num* Num_t;

struct UnaryOp : AST {
    public:
        Token token;
        AST *child;
        UnaryOp(Token t, AST *child) :
            token(t), child(child) {}
        std::string get_id() {return "UnaryOp"; }
};
typedef UnaryOp* UnaryOp_t;

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
        AST_t _program();
        AST_t _compound_statement();
        std::vector<AST_t> _statement_list();
        AST_t _statement();
        AST_t _assignment_statement();
        AST_t _empty();
        AST_t _variable();
        AST_t _factor();
        AST_t _term();
        AST_t _expr();
};
} //namespace comp

#endif // COMPILER_CPP_PARSER_H_
