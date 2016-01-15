#include "point3f.h"

point3f::point3f(float X, float Y, float Z, unsigned char R, unsigned char G, unsigned char B, unsigned char A)
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

point3f::set_clr(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
    r = R;
    g = G;
    b = B;
    a = A;
}
