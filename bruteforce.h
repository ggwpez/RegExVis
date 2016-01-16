#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <regex.h>
#include <regex>

#include "vec3.h"
#include "ast.h"
#include "state.h"

#define C_REG 1

class bruteforce
{
public:
    bruteforce();

    state propagate(char* regex, char *base, size_t c);
    void propagate(char *word, state* start, char *base, size_t c);
    void combine(uint64_t i, char *base, char *buffer, size_t l);
    vec3 get_pos(char* word);

private:
#ifdef C_REG
    regex_t rx;
#else
    std::regex rx;
#endif
    uint64_t wac;       //words analysed count, for debug purposes only
};

#endif // BRUTEFORCE_H
