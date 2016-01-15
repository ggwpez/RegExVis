#ifndef PARSER_H
#define PARSER_H

#include <ast.h>

//actualisy is tokenizer+parser     *coughing*

class parser
{
public:
    parser();
    ast* parse(char const* str, size_t& l);
    ast* parse_exp(char const* str, size_t& l);
    ast* parse_str(char const* str, size_t& l);
};

#endif // PARSER_H
