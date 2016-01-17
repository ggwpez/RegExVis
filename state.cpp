#include "state.h"

state::state()
{
    throw "Pls no def c_tor!";
};

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
    //if (this->ZZ)
    for (state c : this->child)
    {
        v->child.push_back(state(c.pos, std::vector<state>()));

        c.attach_children_vectors(v);
    }
};

std::vector<point3f>* state::calc_lines(std::vector<point3f>* v)
{
    for (state c : this->child)
    {
        point3f p1 = point3f(this->pos, 0,0,0,0);
        point3f p2 = point3f(c.pos, 0,0,0,0);

        /*std::vector<point3f>::iterator it = std::find(v->begin(), v->end(), p1);
        if (p1 != p2 && (it == v->end() || ((it - v->begin()) & 1) ||
            *(++it) != p2))
        {*/
            v->push_back(p1);
            v->push_back(p2);
        //}

        c.calc_lines(v);
    }

    return v;
};
