#ifndef POINT3F_H
#define POINT3F_H

#include "vec3.h"

struct point3f
{
    GLint x, y, z;
    unsigned char r, g, b, a;

    point3f();
    point3f(GLint X, GLint Y, GLint Z, unsigned char R, unsigned char G, unsigned char B, unsigned char A);
    point3f(vec3 pos, unsigned char R, unsigned char G, unsigned char B, unsigned char A);
    point3f(vec3 pos);
    bool operator==(const point3f& b);
    bool operator!=(const point3f& b);

    set_clr(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
};

#endif // POINT3F_H
