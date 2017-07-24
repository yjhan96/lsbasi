#ifndef COMPILER_03_INTERPRETER_H_
#define COMPILER_03_INTERPRETER_H_

#include <string>

#include "token.h"

namespace comp {

class interpreter {
    public:
        token cur_token;
        interpreter(std::string s) :
            cur_token(token(INIT, "")), text(s), pos(0) {}
        std::string interpret();
    private:
        std::string text;
        size_t pos;
        void skip_whitespace_();
        token get_next_token_();
        void eat_(token_type type);
};

} // namespace comp
#endif // COMPILER_03_INTERPRETER_H_

