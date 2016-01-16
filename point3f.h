#ifndef POINT3F_H
#define POINT3F_H

#include "vec3.h"

struct point3f
{
    float x, y, z;
    unsigned char r, g, b, a;

    point3f(float X, float Y, float Z, unsigned char R, unsigned char G, unsigned char B, unsigned char A);
    point3f(vec3 pos, unsigned char R, unsigned char G, unsigned char B, unsigned char A);
    bool operator==(const point3f& b);
    bool operator!=(const point3f& b);

    set_clr(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
};

#endif // POINT3F_H
