//Albert Han
//lexer.cpp
//Lexer tokenizes the string input and outputs tokens
#include "lexer.h"
#include <cctype>
#include <iostream>

namespace comp {

// Helper function of isdigit to eliminate undefined behavior
bool my_isdigit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch));
}

void Lexer::skip_whitespace_() {
    while (std::isspace(text[pos])) {
        ++pos;
    }
}

std::string Lexer::get_int_string_() {
    size_t end = pos;
    while (my_isdigit(text[end])) {
        ++end;
    }
    std::string res(text.begin() + pos, text.begin() + end);
    pos = end;
    return res;
}

token Lexer::get_next_token() {
    size_t n = text.size();

    skip_whitespace_();

    // If the position exceeds the string index, send EoF token
    if (pos >= n) return token(EoF, "");

    if (my_isdigit(text[pos])) {
        std::string s = get_int_string_();
        token result = token(INTEGER, s);
        return result;
    }

    std::string s;
    token result;
    switch (text[pos]) {
        case '+' :
            s.push_back(text[pos]);
            result = token(PLUS, s);
            break;
        case '-' :
            s.push_back(text[pos]);
            result = token(MINUS, s);
            break;
        case '*' :
            s.push_back(text[pos]);
            result = token(MULT, s);
            break;
        case '/' :
            s.push_back(text[pos]);
            result = token(DIVS, s);
            break;
        case '(' :
            s.push_back(text[pos]);
            result = token(LPAREN, s);
            break;
        case ')' :
            s.push_back(text[pos]);
            result = token(RPAREN, s);
            break;
        default:
            throw std::invalid_argument("Lexer: Unable to parse. Invalid Argument");
    }
    ++pos;
    return result;
}
} // namespace comp
