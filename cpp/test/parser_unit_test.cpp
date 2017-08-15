#include "../src/parser.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

void print_compound(comp::Compound_t root, int depth);
void print_assign(comp::Assign_t root, int depth);
void print_var(comp::Var_t root, int depth);
void print_noop(comp::NoOp_t root, int depth);
void print_binop(comp::BinOp_t root, int depth);
void print_num(comp::Num_t root, int depth);
void print_unaryop(comp::UnaryOp_t root, int depth);
void pretty_print(comp::AST_t root, int depth);

void print_compound(comp::Compound_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "Compound" << std::endl;
    int n = root -> children.size();
    for (int i = 0; i < n; ++i) {
        pretty_print(root->children[i], depth+1);
    }
}

void print_assign(comp::Assign_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "Assign" << std::endl;
    pretty_print(root -> left, depth+1);
    pretty_print(root -> right, depth+1);
}

void print_var(comp::Var_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "Var: " << root -> val << std::endl;
}

void print_noop(comp::NoOp_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "NoOp" << std::endl;
}

void print_binop(comp::BinOp_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "BinOp: " << root -> token.val << std::endl;
    pretty_print(root -> left, depth + 1);
    pretty_print(root -> right, depth + 1);
}

void print_num(comp::Num_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "Num: " << root -> token.val << std::endl;
}

void print_unaryop(comp::UnaryOp_t root, int depth) {
    std::string pad(depth, ' ');
    std::cout << pad << "Unary: " << root -> token.val << std::endl;
    pretty_print(root -> child, depth+1);
}

void pretty_print(comp::AST_t root, int depth) {
    std::string s = root -> get_id();
    if (s == "Compound") {
        print_compound(static_cast<comp::Compound_t>(root), depth);
    } else if (s == "Assign") {
        print_assign(static_cast<comp::Assign_t>(root), depth);
    } else if (s == "Var") {
        print_var(static_cast<comp::Var_t>(root), depth);
    } else if (s == "NoOp") {
        print_noop(static_cast<comp::NoOp_t>(root), depth);
    } else if (s == "BinOp") {
        print_binop(static_cast<comp::BinOp_t>(root), depth);
    } else if (s == "Num") {
        print_num(static_cast<comp::Num_t>(root), depth);
    } else {
        assert(s == "UnaryOp");
        print_unaryop(static_cast<comp::UnaryOp_t>(root), depth);
    }
}

int main() {
    std::string s = "BEGIN BEGIN number := 2; a := number; END; x := 11; END.";
    comp::Lexer lexer(s);
    comp::Parser p(&lexer);
    pretty_print(p.parse(), 0);
    return 0;
}
