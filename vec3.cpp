#include "vec3.h"

vec3::vec3()
{
    x = y = z = 0;
};

vec3::vec3(u_int32_t X, u_int32_t Y, u_int32_t Z)
{
    x = X;
    y = Y;
    z = Z;
};


bool vec3::operator==(const vec3& b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
};

vec3 vec3::operator+(const vec3& b)
{
    return vec3(this->x +b.x, this->y +b.y, this->z +b.z);
};
