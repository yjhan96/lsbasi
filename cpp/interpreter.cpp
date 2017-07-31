#include "interpreter.h"

// uncomment to disable assert
// #define NDEBUG
#include <iostream>

namespace comp {

void interpreter::eat_(token_type type) {
    if (cur_token.type == type) {
        cur_token = lexer -> get_next_token();
    } else {
        throw std::invalid_argument( "Unable to parse. Invalid argument" );
    }
}

int interpreter::factor_() {
    token num_token = cur_token;
    eat_(INTEGER);
    return std::stoi(num_token.val);
}

std::string interpreter::interpret() {
/*
 * expr : factor ( (MUL | DIV) factor)*
 * factor : INTEGER
 */
    int result = factor_();

    while (operations.find(cur_token.type) != operations.end()) {
        // ( (MUL | DIV) factor)*
        token op = cur_token;

        // We expect to get factor again
        switch (op.type) {
            case PLUS :
                eat_(PLUS);
                result += factor_();
                break;
            case MINUS :
                eat_(MINUS);
                result -= factor_();
                break;
            case MULT :
                eat_(MULT);
                result *= factor_();
                break;
            case DIVS :
                eat_(DIVS);
                result /= factor_();
                break;
            default :
                throw std::invalid_argument( "op token type is not valid"); 
        }
    }
    return std::to_string(result);
}

} //namespace comp
