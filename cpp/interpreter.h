#ifndef COMPILER_CPP_INTERPRETER_H_
#define COMPILER_CPP_INTERPRETER_H_

#include <string>

#include "token.h"
#include "lexer.h"

namespace comp {

class interpreter {
    public:
        token cur_token;
        Lexer * lexer;
        interpreter(Lexer * lex) {
            lexer = lex;
            cur_token = lexer -> get_next_token();
        }
        std::string interpret();
    private:
        // Eats the current token and gets the next token
        void eat_(token_type type);
        // Gets the int value of int token
        int factor_();
};

} // namespace comp
#endif // COMPILER_CPP_INTERPRETER_H_
