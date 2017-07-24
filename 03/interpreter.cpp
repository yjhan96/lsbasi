#include "interpreter.h"

// uncomment to disable assert
// #define NDEBUG
#include <cassert>
#include <cctype>
#include <iostream>

namespace comp {

// Helper function of isdigit to eliminate undefined behavior
bool my_isdigit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch));
}

std::string get_int_string(std::string text, size_t & pos) {
    int end = pos;
    while (my_isdigit(text[end])) {
        ++end;
    }
    std::string res(text, pos, end - pos);
    pos = end;
    return res;
}

void interpreter::skip_whitespace_() {
    while (pos < text.size() && std::isspace(text[pos])) {
        ++pos;
    }
}

token interpreter::get_next_token_() {
    size_t n = text.size();

    skip_whitespace_();

    // If the position exceeds the string index, send eof_token
    if (pos >= n) return token(EoF, "");

    if (my_isdigit(text[pos])) {
        std::string s = get_int_string(text, pos);
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
        default:
            throw std::invalid_argument( "Unable to parse. Invalid argument" );
    }
    ++pos;
    return result;
}

void interpreter::eat_(token_type type) {
    if (cur_token.type == type) {
        cur_token = get_next_token_();
    } else {
        throw std::invalid_argument( "Unable to parse. Invalid argument" );
    }
}

std::string interpreter::interpret() {
    cur_token = get_next_token_();

    // We expect to get INTEGER token
    token left = cur_token;
    eat_(INTEGER);
    int result = std::stoi(left.val);

    while (cur_token.type != EoF) {

        // We expect to get PLUS token
        token op = cur_token;
        assert(op.val.size() == 1);
        switch (op.val[0]) {
            case '+' :
                eat_(PLUS);
                break;
            case '-' :
                eat_(MINUS);
                break;
            case '*' :
                eat_(MULT);
                break;
            case '/' :
                eat_(DIVS);
                break;
            default :
               throw std::invalid_argument("Operation token is not found.");
        }

        // We expect to get integer again
        token right = cur_token;
        int num = std::stoi(right.val);
        eat_(INTEGER);
        switch (op.type) {
            case PLUS :
                result += num;
                break;
            case MINUS :
                result -= num;
                break;
            case MULT :
                result *= num;
                break;
            case DIVS :
                result /= num;
                break;
            default :
                throw std::invalid_argument( "op token type is not valid"); 
        }
    }
    return std::to_string(result);
}

} //namespace comp
