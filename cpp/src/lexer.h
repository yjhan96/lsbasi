/* Albert Han
 * lexer.h
 * Lexer tokenizes the string input and outputs tokens
 */
#ifndef COMPILER_CPP_LEXER_H_
#define COMPILER_CPP_LEXER_H_
#include <string>
#include <unordered_map>

#include "token.h"

namespace comp {

typedef std::unordered_map<std::string, Token> keyword_map;
extern keyword_map reserved_keywords;

class Lexer {
    public:
        Lexer() = default;
        Lexer(std::string text) :
            text(text), pos(0) {}
        // Gets next token of the string
        Token get_next_token();
    private:
        std::string text;
        size_t pos;

        Token _id();
        bool _has_next_char();
        // Peeks at the next character
        char _peek();
        // Advances the pos by step
        void _advance(int step);
        // Erases whitespace
        void skip_whitespace_();
        // get integer string
        std::string get_int_string_();
};

} //namespace comp

#endif // COMPILER_CPP_LEXER_H_
