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

//#define ADD_DIST(v, e) if(std::find(v->begin(), v->end(), e) == v->end()) \
  //  v->push_back(e);
//#define ADD_DIST(v, e) v->push_back(e);

std::vector<point3f>* state::calc_lines(std::vector<point3f>* v)
{
    for (state c : this->child)
    {
        point3f p1 = point3f(this->pos, 0,0,0,0);
        point3f p2 = point3f(c.pos, 0,0,0,0);

        auto it = std::find(v->begin(), v->end(), p1);
        if (it != v->end() &&
            it. != p2)
        {
            v->push_back(p1);
            v->push_back(p2);
        }

        c.calc_lines(v);
    }

    return v;
};
