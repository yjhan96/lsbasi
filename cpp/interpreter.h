#ifndef COMPILER_CPP_INTERPRETER_H_
#define COMPILER_CPP_INTERPRETER_H_

#include <string>

#include "token.h"
#include "parser.h"

namespace comp {

class Interpreter {
    public:
        Parser * parser;
        Interpreter(Parser * par) {
            parser = par;
        }
        std::string interpret();
    private:
        int _eval_int_node(AST_t tree);
        int _eval_op_node(AST_t tree);
        int _eval_unary_node(AST_t tree);
        int _eval_tree(AST_t tree);
};

} // namespace comp
#endif // COMPILER_CPP_INTERPRETER_H_
