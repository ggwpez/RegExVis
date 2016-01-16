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
    std::vector<point3f>* calc_lines(std::vector<point3f> *v);

    void attack_children_vectors(state *v);

    vec3 pos;
    std::vector<state> child;
};

#endif // STATE_H
