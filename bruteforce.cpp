#include <string.h>
#include <math.h>
#include <bitset>

#include "bruteforce.h"

bruteforce::bruteforce() { };

state bruteforce::propagate(char* regex, char* sigma, size_t c)
{
    state start = state(vec3(), std::vector<state>());

#if C_REG
    if (regcomp(&rx, regex, REG_EXTENDED))
    {
        throw "RegExp invalid!";
        return start;
    }
#else
    rx = std::regex(regex);
#endif

    size_t bsl = strlen(sigma);
   // uint64_t wc = pow(bsl, c) /2;                       // (|Σ| ^l) /2
    uint64_t in_l = propagate("", &start, "012", c);

    qDebug().nospace() << wc << '/' << in_l << " analyzed w/w in l (" << (!in_l ? 0 : (in_l *100.f) /wc) << ")% "
                       << (wc > 2000000 ? "- Im choking on it!" : "");

    return start;
}

//### optimize
u_int64_t bruteforce::propagate(char* word, state* start, char* sigma, size_t c)
{
    if (c < 1) return 0;

    u_int64_t ret = 0;
    size_t wdl = strlen(word), bsl = strlen(sigma);
    char buffer[wdl +2] = { 0 };
    char* b_tmp = buffer;
    strcpy(buffer, word);
wc++;
    for (size_t i = 0; i < bsl; i++)
    {
        buffer[wdl] = sigma[i];

        if (std::regex_match(buffer, rx))
        {
            state ns = state(get_pos(buffer), std::vector<state>());

            ret += propagate(buffer, &ns, sigma, c -1) +1;
            start->child.push_back(ns);
        }
        else
        {
            //state ns = state(get_pos(buffer), std::vector<state>());

            ret += propagate(buffer, start, sigma, c -1);
            //ns.attach_children_vectors(start);
        }
    }

    return ret;
};

vec3 bruteforce::get_pos(char* word)
{
    vec3 ret;                                                   //def to zero
    size_t l = strlen(word);

    for (size_t i = 0; i < l; i++)
       (*((GLint*)(&ret) +(word[i] % 3)))++;                    // -'0' not needed, because '0' % 3 == 0

    return ret;
};

void bruteforce::combine(uint64_t i, char* sigma, char* buffer, size_t l)
{
    size_t base_l = strlen(sigma);
    if (!base_l) return;

    uint64_t o = 0;

    while (o < l)
    {
        buffer[o++] = sigma[i % base_l];
        i /= base_l;
    }
};



















