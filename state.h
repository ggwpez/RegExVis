#ifndef STATE_H
#define STATE_H

#include "vec3.h"
#include "point3f.h"
#include <vector>

class state
{
public:
    state();
    state(vec3 Pos, std::vector<state> Child);
    std::vector<point3f>* calc_lines(point3f start, std::vector<point3f> *v);

    void attach_children_vectors(state* v);
    u_int64_t size();

    vec3 pos;
    std::vector<state> child;
};

#endif // STATE_H
