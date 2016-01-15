#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

enum class astid : char
{
    uninit = '\0',     //error

    string = 's',

    op_or = '|',
    op_star = '*',
    op_plus = '+',
    op_concat = '.'
};

class ast
{
public:
    ast();
    ast(astid Id);
    void free();
    ~ast();

    ast(astid Id, char* string);        // abc
    ast(astid Id, ast* V1);             // * +
    ast(astid Id, ast* V1, ast* V2);    // |

    astid id;

    void write(QDebug str);

    //union
    //{
        char* str;  //no free for this string needed, freed with delete of (this)
        ast* v1, *v2;
    //};
};

#endif // AST_H
