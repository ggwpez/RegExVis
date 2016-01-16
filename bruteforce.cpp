#include <string.h>
#include <math.h>
#include <bitset>

#include "bruteforce.h"

bruteforce::bruteforce(char* regex)
{
    rx = std::regex(regex);
};

//### optimize
state* bruteforce::propagate(char* word, state* start, size_t c)
{
    if (!c) return start;

    char* base = "012";
    size_t wdl = strlen(word), bsl = strlen(base);
    char buffer[wdl +c +1] = { 0 };
    strcpy(buffer, word);
    int wc = pow(c, bsl +1) -1;                               //how many new combinations are there? (word count)

    for (int i = 0; i < wc; i++)
    {
        memset(buffer +wdl, 0, c +1);
        combine(i, base, buffer +wdl, c);

        if (std::regex_match(buffer, rx))
        {
            state ns = state(get_pos(buffer), std::vector<state>());
            propagate(buffer, &ns, c-1);

            start->child.push_back(ns);
        }
    }

    return start;
};

vec3 bruteforce::get_pos(char* word)
{
    vec3 ret;                                            //def to zero
    size_t l = strlen(word);

    for (size_t i = 0; i < l; i++)
       (*((int*)(&ret) +((word[i] -'0') % 3)))++;               //because I can

    return ret;
};

void bruteforce::combine(int i, char* base, char* buffer, size_t l)
{
    size_t base_l = strlen(base);
    if (!base_l) return;

    int o = 0;

    while (o < l)
    {
        buffer[o++] = base[i % base_l];
        i /= base_l;
    }
};



















