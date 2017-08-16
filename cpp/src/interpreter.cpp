#include "interpreter.h"

#include "parser.h"

// uncomment to disable assert
// #define NDEBUG

namespace comp {

int Interpreter::_eval_num_node(Num_t tree) {
    return std::stoi((tree -> token).val);
}

int Interpreter::_eval_binop_node(BinOp_t tree) {
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

int Interpreter::_eval_unaryop_node(UnaryOp_t tree) {
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

int Interpreter::_eval_compound_node(Compound_t tree) {
    int n = tree -> children.size();
    for (int i = 0; i < n; ++i) {
        _eval_tree(tree -> children[i]);
    }
    return 0;
}

int Interpreter::_eval_assign_node(Assign_t tree) {
    //Left node should be a variable node
    std::string variable = static_cast<Var_t>(tree->left) -> val;
    int num = _eval_tree(tree -> right);
    scope_table[variable] = num;

    return 0;
}

int Interpreter::_eval_var_node(Var_t tree) {
    std::string variable = tree -> val;
    if (scope_table.find(variable) == scope_table.end()) {
        throw std::invalid_argument("Interpreter: No variable named " + variable);
    }
    return scope_table[variable];
}

int Interpreter::_eval_noop_node(NoOp_t tree) {
    return 0;
}

int Interpreter::_eval_tree(AST_t tree) {
    std::string type = tree -> get_id();
    if (type == "Num") {
        return _eval_num_node(static_cast<Num_t>(tree));
    } else if (type == "UnaryOp") {
        // There is only one child tree, which means it's unary.
        return _eval_unaryop_node(static_cast<UnaryOp_t>(tree));
    } else if (type == "BinOp") {
        return _eval_binop_node(static_cast<BinOp_t>(tree));
    } else if (type == "Compound") {
        return _eval_compound_node(static_cast<Compound_t>(tree));
    } else if (type == "Assign") {
        return _eval_assign_node(static_cast<Assign_t>(tree));
    } else if (type == "Var") {
        return _eval_var_node(static_cast<Var_t>(tree));
    } else if (type == "NoOp") {
        return _eval_noop_node(static_cast<NoOp_t>(tree));
    } else {
        throw std::invalid_argument("Interpreter: Invalid tree type");
    }
}

//returns the result of interpreter
std::string Interpreter::interpret() {
    AST_t tree = parser -> parse();
    _eval_tree(tree);
    std::string res;
    for (auto it = scope_table.begin(); it != scope_table.end(); ++it) {
        res += (it -> first);
        res.push_back(' ');
        res += std::to_string(it -> second);
        res.push_back('\n');
    }
    return res;
}

} //namespace comp
