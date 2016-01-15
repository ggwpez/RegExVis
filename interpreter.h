#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "vec3.h"
#include "state.h"
#include "ast.h"

#include <vector>
#include <QGLWidget>


class interpreter
{
public:
    interpreter();
    ~interpreter();

    state propagate(ast* ast, size_t c);
    state propagate(ast* tree, state *start, size_t c);
    state* propagate_state(ast* tree, state* start, size_t cycles);
    void propagate_string(ast* ast, state* start, state* states);
    std::vector<vec3>* lines;
};

#endif // INTERPRETER_H
