/* Albert Han
 * parser.cpp
 * Implementation of parser.h
 * Parser parses the input into a Abstract-Syntax Tree (AST).
 */

#include "parser.h"

namespace comp {

void Parser::_eat(token_type type) {
    if (cur_token.type == type) {
        cur_token = lexer -> get_next_token();
    } else {
        throw std::invalid_argument("Parser: Wrong token. caanot parse"); 
    }
}

/* START OF CONTEXT-FREE GRAMMARS
 *
 * Context-free Grammars
 *
 * program : compound_statement DOT
 *
 * compound_statement : BEGIN statement_list END
 *
 * statement_list : statement
 *                | statement SEMI statement_list
 *
 * statement : compound_statement
 *           | assignment_statement
 *           | empty
 *
 * assignment_statement : variable ASSIGN expr
 *
 * empty : 
 *
 * epxr : term ( (PLUS | MINUS) term)*
 *
 * term : factor ( (MULT | DIVS) factor)*
 *
 * factor : PLUS factor
 *        | MINUS factor
 *        | INTEGER
 *        | LPAREN expr RPAREN
 *        | variable
 *
 * variable : ID
 */

// program : compound_statement DOT
AST_t Parser::_program() {
    AST_t res = _compound_statement();
    _eat(DOT);
    return res;
}

// compound_statement : BEGIN statement_list END
AST_t Parser::_compound_statement() {
    _eat(BEGIN);
    std::vector<AST_t> nodes = _statement_list();
    _eat(END);
    return new Compound(nodes);
}

// statement_list : statement | statement SEMI statement_list
std::vector<AST_t> Parser::_statement_list() {
    std::vector<AST_t> res;
    res.push_back(_statement());
    while (cur_token.type == SEMI) {
        _eat(SEMI);
        res.push_back(_statement());
    }
    return res;
}

// statement : compound_statement | assignment_statement | empty
AST_t Parser::_statement() {
    AST_t res;
    if (cur_token.type == BEGIN) {
        res = _compound_statement();
    } else if (cur_token.type == ID) {
        res = _assignment_statement();
    } else {
        res = _empty();
    }
    return res;
}

// assignment_statement : variable ASSIGN expr
AST_t Parser::_assignment_statement() {
    AST_t var = _variable();
    Token t = cur_token;
    _eat(ASSIGN);
    AST_t expr = _expr();
    return new Assign(var, t, expr);
}

// empty
AST_t Parser::_empty() {
    return new NoOp();
}

// variable : ID
AST_t Parser::_variable() {
    Token t = cur_token;
    _eat(ID);
    Var_t res = new Var(t);
    return res;
}

/* factor : PLUS factor
 *        | MINUS factor
 *        | INTEGER
 *        | LPAREN expr RPAREN
 *        | variable
 */
AST_t Parser::_factor() {
    AST_t res;
    if (cur_token.type == PLUS) {
        Token token = cur_token;
        _eat(PLUS);
        res = new UnaryOp(token, _factor());
    } else if (cur_token.type == MINUS) {
        Token token = cur_token;
        _eat(MINUS);
        res = new UnaryOp(token, _factor());
    } else if (cur_token.type == INTEGER) {
        res = new Num(cur_token);
        _eat(INTEGER);
    } else if (cur_token.type == LPAREN) {
        _eat(LPAREN);
        res = _expr();
        _eat(RPAREN);
    } else {
        res = _variable();
    }
    return res;
}

// term : factor ( (MULT | DIVS) factor)*
AST_t Parser::_term() {
    AST_t res = _factor();
    while (cur_token.type == MULT || cur_token.type == DIVS) {
        if (cur_token.type == MULT) {
            _eat(MULT);
            AST_t right = _factor();
            res = new BinOp(res, Token(MULT, "*"), right);
        } else {
            _eat(DIVS);
            AST_t right = _factor();
            res= new BinOp(res, Token(DIVS, "/"), right);
        }
    }
    return res;
}

// expr : term ( (PLUS | MINUS) term)*
AST_t Parser::_expr() {
    AST_t res = _term();
    while (cur_token.type == PLUS || cur_token.type == MINUS) {
        if (cur_token.type == PLUS) {
            _eat(PLUS);
            AST_t right = _term();
            res = new BinOp(res, Token(PLUS, "+"), right); 
        } else {
            _eat(MINUS);
            AST_t right = _term();
            res = new BinOp(res, Token(MINUS, "-"), right);
        }
    }
    return res;
}

/*
 *  End of CONTEXT-FREE GRAMMARS
 */

AST_t Parser::parse() {
    AST_t res = _program();
    if (cur_token.type != EoF) {
        throw std::invalid_argument("Parser: Last cur_token type not EoF");
    }
    return res;
}

} // namespace comp
