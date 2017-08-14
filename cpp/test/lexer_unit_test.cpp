#include "../src/lexer.h"
#include <string>
#include <cassert>
#include <iostream>

void lexer_test_1() {
    comp::Lexer lex("3 + 4");
    
    comp::Token t = lex.get_next_token();
    assert(t.type == comp::INTEGER);
    assert(t.val == "3");

    t = lex.get_next_token();
    assert(t.type == comp::PLUS);
    assert(t.val == "+");

    t = lex.get_next_token();
    assert(t.type == comp::INTEGER);
    assert(t.val == "4");
}

void lexer_test_2() {
    comp::Lexer lex("BEGIN END.");

    comp::Token t = lex.get_next_token();
    assert(t.type == comp::BEGIN);
    assert(t.val == "BEGIN");

    t = lex.get_next_token();
    assert(t.type == comp::END);
    assert(t.val == "END");

    t = lex.get_next_token();
    assert(t.type == comp::DOT);
}

void lexer_test_3() {
    comp::Lexer lex("BEGIN a := 5; END.");

    comp::Token t = lex.get_next_token();
    assert(t.type == comp::BEGIN);
    assert(t.val == "BEGIN");

    t = lex.get_next_token();
    assert(t.type == comp::ID);
    assert(t.val == "a");

    t = lex.get_next_token();
    assert(t.type == comp::ASSIGN);
    
    t = lex.get_next_token();
    assert(t.type == comp::INTEGER);

    t = lex.get_next_token();
    assert(t.type == comp::SEMI);

    t = lex.get_next_token();
    assert(t.type == comp::END);

    t = lex.get_next_token();
    assert(t.type == comp::DOT);
}

int main() {
    lexer_test_1();
    lexer_test_2();
    lexer_test_3();
    std::cout << "Unit test Passed!" << std::endl;
    return 0;
}
