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
 * epxr : term ( (PLUS | MINUS) term)*
 * term : factor ( (MULT | DIVS) factor)*
 * factor : (PLUS | MINUS) factor |  INTEGER | LPAREN expr RPAREN
 */

// factor : (PLUS | MINUS) factor | INTEGER | LPAREN expr RPAREN
AST_t Parser::_factor() {
    if (cur_token.type == PLUS || cur_token.type == MINUS) {
        Token token = cur_token;
        if (cur_token.type == PLUS) {
            _eat(PLUS);
        } else {
            _eat(MINUS);
        }
        AST_t res = new UnaryOp(token, _factor());
        return res;
    }
    if (cur_token.type == INTEGER) {
        AST_t res = new Num(cur_token);
        _eat(INTEGER);
        return res;
    } else {
        _eat(LPAREN);
        AST_t res = _expr();
        _eat(RPAREN);
        return res;
    }
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
    return _expr();
}

} // namespace comp
