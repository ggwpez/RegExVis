#include "ast.h"

ast::ast()
{
    this->id = astid::uninit;
    this->v1 = this->v2 = nullptr;
    this->str = nullptr;
}

ast::ast(astid Id)
{
    this->id = Id;
};

ast::ast(astid Id, char* string)
{
    this->id = Id;
    this->str = string;

    this->v1 = this->v2 = nullptr;
};

ast::ast(astid Id, ast* V1)
{
    this->id = Id;
    this->v1 = V1;
    this->v2 = nullptr;
};

ast::ast(astid Id, ast* V1, ast* V2)
{
    this->id = Id;
    this->v1 = V1;
    this->v2 = V2;
};

void ast::write(QDebug str)
{
    str << '(';
    switch (this->id)
    {
        case astid::string:
            str << this->str;
            break;
        case astid::op_or:
            this->v1->write(str);
            str << '|';
            this->v2->write(str);
            break;
        case astid::op_plus:
            this->v1->write(str);
            str << '+';
            break;
        case astid::op_star:
            this->v1->write(str);
            str << '*';
            break;
        case astid::op_concat:
            this->v1->write(str);
            str << '.';
            this->v2->write(str);
            break;
        default:
            str << "#error#";
            break;

    };
    str << ')';
};

ast::~ast()
{

};

void ast::free()
{
    if (this->v1)
        delete v1;
    if (this->v2)
        delete v2;
}
