#ifndef VEC3_H
#define VEC3_H

#include <QGLWidget>

struct vec3
{
    vec3();
    vec3(GLint X,GLint Y, GLint Z);
    GLint sq_length();
    bool operator==(const vec3& b);
    vec3 operator+(const vec3& b);

    GLint x, y, z;
} __attribute__((packed));

#endif // VEC3_H
