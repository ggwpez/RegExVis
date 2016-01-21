#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <regex.h>
#include <regex>

#include "vec3.h"
#include "ast.h"
#include "state.h"

#define C_REG 0

class bruteforce
{
public:
    bruteforce();

    state propagate(char* regex, char* sigma, size_t c);
    u_int64_t propagate(char* word, state* start, char *sigma, size_t c);
    void combine(uint64_t i, char* sigma, char* buffer, size_t l);
    vec3 get_pos(char* word);

private:
#if C_REG
    regex_t rx;
#else
    std::regex rx;
#endif
    u_int64_t wc = 0;
};

#endif // BRUTEFORCE_H
