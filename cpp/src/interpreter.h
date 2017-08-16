#ifndef COMPILER_CPP_INTERPRETER_H_
#define COMPILER_CPP_INTERPRETER_H_

#include <string>
#include <unordered_map>

#include "token.h"
#include "parser.h"

namespace comp {

class Interpreter {
    public:
        typedef std::unordered_map<std::string, int> global_scope_map;
        global_scope_map scope_table;
        Parser * parser;
        Interpreter(Parser * par) {
            parser = par;
        }
        std::string interpret();
    private:
        union return_val {
            int val;
        };
        int _eval_num_node(Num_t tree);
        int _eval_binop_node(BinOp_t tree);
        int _eval_unaryop_node(UnaryOp_t tree);
        int _eval_compound_node(Compound_t tree);
        int _eval_assign_node(Assign_t tree);
        int _eval_var_node(Var_t tree);
        int _eval_noop_node(NoOp_t tree);
        int _eval_tree(AST_t tree);
};

} // namespace comp
#endif // COMPILER_CPP_INTERPRETER_H_
