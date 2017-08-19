//Albert Han
//lexer.cpp
//Lexer tokenizes the string input and outputs tokens
#include "lexer.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>

namespace comp {

keyword_map reserved_keywords( { {"BEGIN", Token(BEGIN, "BEGIN")},
                                {"END", Token(END, "END")},
                                {"DIV", Token(DIVS, "DIV")},
                               } );

// Helper function of isdigit to eliminate undefined behavior
bool my_isdigit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch));
}

bool my_isalpha(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch));
}

bool my_isalnum(char ch) {
    return std::isalnum(static_cast<unsigned char>(ch));
}

bool Lexer::_has_next_char() {
    return pos < text.size() - 1;
}

char Lexer::_peek() {
    return text[pos+1];
}

void Lexer::_advance(int step = 1) {
    pos += step;
}

void Lexer::skip_whitespace_() {
    while (std::isspace(text[pos])) {
        _advance();
    }
}

std::string Lexer::get_int_string_() {
    size_t end = pos;
    while (end < text.size() && my_isdigit(text[end])) {
        ++end;
    }
    std::string res(text.begin() + pos, text.begin() + end);
    _advance(end - pos);
    return res;
}

Token Lexer::_id() {
    size_t end = pos;
    while (end < text.size() && (text[end] == '_' || my_isalnum(text[end]))) {
        ++end;
    }
    std::string res(text.begin() + pos, text.begin() + end);
    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    _advance(end - pos);
    if (reserved_keywords.find(res) == reserved_keywords.end()) {
        reserved_keywords[res] = Token(ID, res);
    }
    return reserved_keywords[res];
}

Token Lexer::get_next_token() {
    size_t n = text.size();

    skip_whitespace_();

    // If the position exceeds the string index, send EoF token
    if (pos >= n) return Token(EoF, "");

    // Integer Token
    if (my_isdigit(text[pos])) {
        std::string s = get_int_string_();
        Token result = Token(INTEGER, s);
        return result;
    }

    // alphanumerical Tokens
    if (text[pos] == '_' || my_isalpha(text[pos])) {
        return _id();
    }

    // ASSIGN token
    if (text[pos] == ':' && _has_next_char() && _peek() == '=') {
        std::string s = text.substr(pos, 2);
        _advance(2);
        Token result = Token(ASSIGN, s);
        return result;
    }

    std::string s;
    Token result;
    switch (text[pos]) {
        // All one-char tokens
        case '+' :
            s.push_back(text[pos]);
            result = Token(PLUS, s);
            break;
        case '-' :
            s.push_back(text[pos]);
            result = Token(MINUS, s);
            break;
        case '*' :
            s.push_back(text[pos]);
            result = Token(MULT, s);
            break;
        case '(' :
            s.push_back(text[pos]);
            result = Token(LPAREN, s);
            break;
        case ')' :
            s.push_back(text[pos]);
            result = Token(RPAREN, s);
            break;
        case '.' :
            s.push_back(text[pos]);
            result = Token(DOT, s);
            break;
        case ';' :
            s.push_back(text[pos]);
            result = Token(SEMI, s);
            break;
        default:
            throw std::invalid_argument("Lexer: Unable to parse. Invalid Argument");
    }
    _advance();
    return result;
}
} // namespace comp
