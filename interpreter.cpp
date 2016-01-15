#include "interpreter.h"

#include <stdint.h>
//#define ADD_DIST(v, e) if(std::find(v.begin(), v.end(), e) == v.end()) \
  //  v.push_back(e);
#define ADD_DIST(v, e) v.push_back(e);

interpreter::interpreter()
{
    lines = new std::vector<vec3>;
};

interpreter::~interpreter()
{
    delete lines;
};

state interpreter::propagate(ast* ast, size_t c)
{
    state start = state(vec3(0,0,0), std::vector<state>());
    propagate(ast, &start, c);

    return start;
};

state interpreter::propagate(ast* tree, state* start, size_t c)
{
    if (!c) return *start;

    propagate_state(tree, start, c);

    for (size_t i = 0; i < start->child.size(); i++)
        state new_child = propagate(tree, &start->child[i], c-1);

    return *start;
};

state* interpreter::propagate_state(ast* tree, state* start, size_t cycles)
{
    if (!tree)
        throw "internal error";

    if (tree->id == astid::string)
    {
        vec3 to_add = start->pos;

        for (size_t i = 0; tree->str[i]; i++)
        {
            char c = (tree->str[i] - '0') % 3;

            if (c == 0)
                to_add.x++;
            else if (c == 1)
                to_add.y++;
            else if (c == 2)
                to_add.z++;
        }

        state new_state = state(to_add, std::vector<state>());
        start->child.push_back(new_state);

        return start;
    }
    else if (tree->id == astid::op_or)
    {
        propagate_state(tree->v1, start, cycles);
        propagate_state(tree->v2, start, cycles);

        return start;
    }
    else if (tree->id == astid::op_plus)
    {
        state ns = state(start->pos, std::vector<state>());
        propagate(tree->v1, &ns, cycles);

        ns.attack_children_vectors(start);

        return start;
    }
    else if (tree->id == astid::op_star)
    {
        //propagate(ast->v1, start, c);
        propagate_state(tree->v1, start, cycles);
        start->child.push_back(state(start->pos, std::vector<state>()));

        return start;
    }
    else if (tree->id == astid::op_concat)
    {
        state new_start = state(start->pos, std::vector<state>());

        propagate_state(tree->v1, &new_start, cycles);

        for (state ns : new_start.child)
        {
            propagate_state(tree->v2, &ns, cycles);

            //start->child.push_back(ns);
            for (state cns : ns.child)
                start->child.push_back(cns);
        }

        return start;
    }
    else return nullptr;
};


























