#include "vec3.h"

vec3::vec3()
{
    x = y = z = 0;
};

vec3::vec3(GLint X, GLint Y, GLint Z)
{
    x = X;
    y = Y;
    z = Z;
};

GLint vec3::sq_length()
{
    return this->x * this->x + this->y * this->y + this->z * this->z;
};

bool vec3::operator==(const vec3& b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
};

vec3 vec3::operator+(const vec3& b)
{
    return vec3(this->x +b.x, this->y +b.y, this->z +b.z);
};
