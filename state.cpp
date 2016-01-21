#include "state.h"

#define DEEP_DRAW 1

state::state(vec3 Pos, std::vector<state> Child)
{
    pos = Pos;
    child = Child;
};

u_int64_t state::size()
{
    u_int64_t ret = 1;

    for (state s : this->child)
        ret += s.size();

    return ret;
}

void state::attach_children_vectors(state* v)
{
    for (state c : this->child)
    {
        v->child.push_back(state(c.pos, std::vector<state>()));

        c.attach_children_vectors(v);
    }
};

std::vector<point3f>* state::calc_lines(point3f start, std::vector<point3f>* v)
{
    for (state c : this->child)
    {
        point3f p1;
        point3f p2 = point3f(c.pos, 0,0,0,0);

#if !DEEP_DRAW
        p1 = point3f(this->pos);
#else
        p1 = start;
#endif

        v->push_back(p1);
        v->push_back(p2);

        c.calc_lines(point3f(this->pos), v);
    }

    return v;
};
