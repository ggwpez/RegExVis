#include "point3f.h"

point3f::point3f()
    : point3f(0,0,0,0,0,0,0)
{ };

point3f::point3f(vec3 pos)
    : point3f(pos, 0, 0, 0, 0)
{ };

point3f::point3f(GLint X, GLint Y, GLint Z, unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
    x = X;
    y = Y;
    z = Z;
    r = R;
    g = G;
    b = B;
    a = A;
}

point3f::point3f(vec3 pos, unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
    x = pos.x;
    y = pos.y;
    z = pos.z;
    r = R;
    g = G;
    b = B;
    a = A;
}

bool point3f::operator==(const point3f& b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;      //not checking the color, clr in my case always 0,0,0,0
};

bool point3f::operator!=(const point3f& b)
{
    return this->x != b.x || this->y != b.y || this->z != b.z;      //""
};

point3f::set_clr(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
    r = R;
    g = G;
    b = B;
    a = A;
}
