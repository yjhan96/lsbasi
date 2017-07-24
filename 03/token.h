#ifndef COMPILER_03_TOKEN_H_
#define COMPILER_03_TOKEN_H_
#include <string>

namespace comp {

enum token_type {
    INIT,
    INTEGER,
    PLUS,
    MINUS,
    MULT,
    DIVS,
    EoF
};

static const char * token_strings[] = {"INIT", "INTEGER", "PLUS", "MINUS",
                                       "EoF", "MULT", "DIVS"};

class token {
    public:
        token_type type;
        std::string val;

        token() = default;
        token(token_type type, std::string s) :
            type(type), val(s) {}
        operator std::string();
};

} // namespace comp

#endif // COMPILER_03_TOKEN_H_
