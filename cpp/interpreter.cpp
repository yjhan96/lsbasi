#include "interpreter.h"

// uncomment to disable assert
// #define NDEBUG

namespace comp {

// Eats the token and updates the cur_token
void interpreter::eat_(token_type type) {
    if (cur_token.type == type) {
        cur_token = lexer -> get_next_token();
    } else {
        throw std::invalid_argument( "Unable to parse. Invalid argument" );
    }
}

/*
 * START OF CONTEXT-FREE GRAMMARS
 * 
 * expr : term ( (PLUS | MINUS) term)*
 * term : factor ( (MULT | DIVS) factor)*
 * factor : INTEGER | LPAREN expr RPAREN
 */

// factor : INTEGER | LPAREN expr RPAREN
int interpreter::factor_() {
    if (cur_token.type == INTEGER) {
        int res = std::stoi(cur_token.val);
        eat_(INTEGER);
        return res;
    } else {
        eat_(LPAREN);
        int res = expr_();
        eat_(RPAREN);
        return res;
    }
}

// term : factor ( (MULT | DIVS) factor)*
int interpreter::term_() {
    int result = factor_();
    while (cur_token.type == MULT || cur_token.type == DIVS) {
        if (cur_token.type == MULT) {
            eat_(MULT);
            result *= factor_();
        } else {
            eat_(DIVS);
            result /= factor_();
        }
    }
    return result;
}

// expr : term ( (PLUS | MINUS) term)*
int interpreter::expr_() {
    int result = term_();

    while (cur_token.type == PLUS || cur_token.type == MINUS) {
        if (cur_token.type == PLUS) {
            eat_(PLUS);
            result += term_();
        } else {
            eat_(MINUS);
            result -= term_();
        }
    }
    return result;
}

/*
 * END OF CONTEXT-FREE GRAMMARS
 */

//returns the result of interpreter
std::string interpreter::interpret() {
    return std::to_string(expr_());
}

} //namespace comp
