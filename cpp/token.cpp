#include "token.h"
namespace comp
{
    Token::operator std::string() {
        std::string result;
        result.push_back(type);
        result.append(", ");
        result.append(token_strings[type]);
        
        return result;
    }

} // namespace comp
