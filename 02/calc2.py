'''
Token types

EOF (end-of-file) token is used to indicate that
there is no more input left for lexical analysis
'''
INTEGER = 'INTEGER'
PLUS, MINUS, MULT, DIVS = 'PLUS', 'MINUS', 'MULT', 'DIVS'
EOF = 'EOF'
OPERATORS = {'+', '-', '*', '/'}

class Token(object):
    def __init__(self, symbol, value):
        # toekn symbol: INTEGER, PLUS, or EOF
        self.symbol = symbol
        # token value: 0-9, '+', or None
        self.value = value

    def __str__(self):
        '''String representation of the class instance.

        Examples:
            Token(INTEGER, 3)
            Token(PLUS, '+')
        '''
        return 'Token({symbol}, {value})'.format(
                symbol = self.symbol,
                value = repr(self.value)
        )

    def __repr__(self):
        return self.__self__()


class Interpreter(object):
    def __init__(self, text):
        # client string input, e.g. "3+5"
        self.text = text
        # self.pos is an index into self.text
        self.pos = 0
        # current token instance
        self.current_token = None

    def error(self):
        raise Exception('Error parsing input')

    def __get_nonwhitespace_pos(self):
        '''Sets the self.pos to the next non-whitespace character
        '''
        text = self.text
        while (self.pos < len(text) and text[self.pos].isspace()):
            self.pos += 1

    def __get_integer(self):
        # Gets next integer from text
        text = self.text
        current_char = text[self.pos]
        num = 0
        while (current_char.isdigit()):
            num *= 10
            num += int(current_char)
            self.pos += 1
            if (self.pos == len(text)): break
            current_char = text[self.pos]
        return num

    def get_next_token(self):
        '''Lexical analyzer (also known as scanner or tokenizer)

        This method is responsible for breaking a sentence
        apart into tokens. One token at a time.
        '''
        text = self.text

        # is self.pos index past the end of the self.text?
        # if so, then return EOF token because there is no more
        # input left to convert into tokens
        self.__get_nonwhitespace_pos()
        if self.pos >= len(text):
            return Token(EOF, None)

        # get a character at the position self.pos and decide
        # what token to create based on the single character
        current_char = text[self.pos]

        # if the character is a digit then convert it to
        # integer, create an INTEGER token, increment self.pos
        # index to point to the next character after the digit
        # and return the INTEGER token
        if current_char.isdigit():
            num = self.__get_integer()
            token = Token(INTEGER, num)
            return token
        if current_char in OPERATORS:
            if current_char == '+':
                token = Token(PLUS, current_char)
            elif current_char == '-':
                token = Token(MINUS, current_char)
            elif current_char == '*':
                token = Token(MULT, current_char)
            else:
                assert(current_char == '/')
                token = Token(DIVS, current_char)
            self.pos += 1
            return token

        return self.error()

    def eat(self, token_type):
        # compare the current token type with the passed token
        # type and if they match then "eat" the current token
        # and assign the next token to the self.current_token,
        # otherwise raise an exception
        if self.current_token.symbol == token_type:
            self.current_token = self.get_next_token()
        else:
            self.error()

    def expr(self):
        '''expr -> INTEGER PLUS INTEGER'''
        # set current token to the first token taken from the input
        self.current_token = self.get_next_token()

        # we expect the current token to be a single-digit integer
        left = self.current_token
        self.eat(INTEGER)
        result = left.value

        while (self.current_token.symbol != EOF):
            # we expect the current token to be a '+' token
            op = self.current_token
            if op.symbol == PLUS:
                self.eat(PLUS)
            elif op.symbol == MINUS:
                self.eat(MINUS)
            elif op.symbol == MULT:
                self.eat(MULT)
            else:
                self.eat(DIVS)

            # we expect the current token to be a single-digit integer
            right = self.current_token
            self.eat(INTEGER)
            # after the above call the self.current_token is set to
            # EOF token

            # at this point INTEGER PLUS INTEGER sequence of tokens
            # has been successfully found and the method can just
            # return the result of adding two integers, thus
            # effectively interpreting client input
            if op.symbol == PLUS:
                result += right.value
            elif op.symbol == MINUS:
                result -= right.value
            elif op.symbol == MULT:
                result *= right.value
            else:
                assert(op.symbol == DIVS)
                result /= right.value

        return result

def main():
    while True:
        try:
            text = input('calc> ')
        except EOFError:
            break
        if not text:
            coninue
        interpreter = Interpreter(text)
        result = interpreter.expr()
        print(result)
    print()

if __name__ == '__main__':
    main()

