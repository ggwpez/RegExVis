#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <regex>

#include "vec3.h"
#include "ast.h"
#include "state.h"

class bruteforce
{
public:
    bruteforce(char *regex);

    state *propagate(char *word, state* start, size_t c);
    void combine(int i, char *base, char *buffer, size_t l);
    vec3 get_pos(char* word);

private:
    std::regex rx;
};

#endif // BRUTEFORCE_H
