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


void state::attack_children_vectors(state* v)
{
    for (state c : this->child)
    {
        v->child.push_back(state(c.pos, std::vector<state>()));

        c.attack_children_vectors(v);
    }
};

std::vector<point3f>* state::calc_lines(std::vector<point3f>* v)
{
    for (state c : this->child)
    {
        v->push_back(point3f(this->pos, 0,0,0,0));
        v->push_back(point3f(c.pos, 0,0,0,0));

        c.calc_lines(v);
    }

    return v;
};
