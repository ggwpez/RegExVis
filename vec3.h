#ifndef VEC3_H
#define VEC3_H

#include <QGLWidget>

struct vec3
{
    vec3();
    vec3(u_int32_t X,u_int32_t Y, u_int32_t Z);
    bool operator==(const vec3& b);
    vec3 operator+(const vec3& b);

    u_int32_t x, y, z;
} __attribute__((packed));

#endif // VEC3_H
