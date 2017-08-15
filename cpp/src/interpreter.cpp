#include "interpreter.h"

#include "parser.h"

// uncomment to disable assert
// #define NDEBUG

namespace comp {

int Interpreter::_eval_int_node(Num_t tree) {
    return std::stoi((tree -> token).val);
}

int Interpreter::_eval_op_node(BinOp_t tree) {
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

int Interpreter::_eval_unary_node(UnaryOp_t tree) {
    switch ((tree -> token).type) {
        case PLUS :
            return _eval_tree(tree -> child);
            break;
        case MINUS :
            return -1 * _eval_tree(tree -> child);
            break;
        default :
            throw std::invalid_argument("Interpreter: Invalid token type");
    }
}

int Interpreter::_eval_tree(AST_t tree) {
    std::string type = tree -> get_id();
    if (type == "Num") {
        return _eval_int_node(static_cast<Num_t>(tree));
    } else if (type == "UnaryOp") {
        // There is only one child tree, which means it's unary.
        return _eval_unary_node(static_cast<UnaryOp_t>(tree));
    } else if (type == "BinOp") {
        return _eval_op_node(static_cast<BinOp_t>(tree));
    } else {
        throw std::invalid_argument("Interpreter: Invalid tree type");
    }
}

//returns the result of interpreter
std::string Interpreter::interpret() {
    AST_t tree = parser -> parse();
    return std::to_string(_eval_tree(tree));
}

} //namespace comp
