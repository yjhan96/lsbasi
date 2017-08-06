#include "interpreter.h"

#include "parser.h"

// uncomment to disable assert
// #define NDEBUG

namespace comp {

int Interpreter::_eval_int_node(AST_t tree) {
    return std::stoi((tree -> token).val);
}

int Interpreter::_eval_op_node(AST_t tree) {
    int left, right;
    switch ((tree -> token).type) {
        case PLUS :
            left = _eval_tree(tree -> left);
            right = _eval_tree(tree -> right);
            return left + right;
            break;
        case MINUS :
            left = _eval_tree(tree -> left);
            right = _eval_tree(tree -> right);
            return left - right;
            break;
        case MULT :
            left = _eval_tree(tree -> left);
            right = _eval_tree(tree -> right);
            return left * right;
            break;
        case DIVS :
            left = _eval_tree(tree -> left);
            right = _eval_tree(tree -> right);
            return left / right;
            break;
        default :
            throw std::invalid_argument("Interpreter: Invalid token type");
    }
}

int Interpreter::_eval_tree(AST_t tree) {
    if ( (tree->token).type == INTEGER) {
        return _eval_int_node(tree);
    } else {
        return _eval_op_node(tree);
    }
}

//returns the result of interpreter
std::string Interpreter::interpret() {
    AST_t tree = parser -> parse();
    return std::to_string(_eval_tree(tree));
}

} //namespace comp
