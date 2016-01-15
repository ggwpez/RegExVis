#include "parser.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <new>

#define ERR { fprintf(stderr, "Parsing error @ char %zu = '%c'", l, str[l]); abort(); return -1; };

parser::parser() { };

ast* parser::parse(char const* str, size_t& l)
{
    ast* ret = nullptr;

    while (str[l])
    {
        if (str[l] == '(')
        {
            ast* tmp = parse(str, ++l);
            if (str[l++] != ')')
                ERR;

            ret = !ret ? tmp : new ast(astid::op_concat, ret, tmp);
        }
        else if (str[l] == ')')
            return ret;
        else if (isdigit(str[l]))
            ret = parse_str(str, l);
        else if (str[l] == '+')
        {
            l++;
            ret = new ast(astid::op_plus, ret);
        }
        else if (str[l] == '*')
        {
            l++;
            ret = new ast(astid::op_star, ret);
        }
        else if (str[l] == '|')
        {
            l++;
            ast* tmp = parse(str, l);

            ret = new ast(astid::op_or, ret, tmp);
        }
    };

    return ret;
};

ast* parser::parse_exp(char const* str, size_t& l)
{
    char c = str[l];

    if (isdigit(c))
        return parse_str(str, l);

    /*else if (c == '(')
    {
        ast* ret = parse(str, ++l);
        return (str[l] == ')') ? l++, ret : nullptr;
    }
    else if (c == ')')
        return nullptr;
    else
        return nullptr;*/
    abort();

    /*return (c == '*' || c == '+' || c == '+') ?
                new ast((astid)c) :
                nullptr;*/
};

ast* parser::parse_str(char const* str, size_t& l)
{
    size_t str_l = 0;
    while (isdigit(str[l +str_l]))
        str_l++;

    void* mem = malloc(sizeof(ast) + str_l +1);                                 //save some ram
    ast* ret = new(mem) ast(astid::string, (char*)(mem + sizeof(ast)));

    memcpy(ret->str, str +l, str_l);
    ret->str[str_l] = 0;          //end string

    l += str_l;
    return ret;
};
