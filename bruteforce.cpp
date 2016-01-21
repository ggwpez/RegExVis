#include <string.h>
#include <math.h>
#include <bitset>

#include "bruteforce.h"

bruteforce::bruteforce() { };

state bruteforce::propagate(char* regex, char* base, size_t c)
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

    size_t bsl = strlen(base);
    uint64_t wc = pow(bsl, c) /2;
    qDebug() << "analysed: " << wc << "words" << (wc > 2000000 ? "- Im choking on it!" : "");

    propagate("", &start, "012", c);

    return start;
}

//### optimize
void bruteforce::propagate(char* word, state* start, char* base, size_t c)
{
    if (c < 1) return;

    size_t wdl = strlen(word), bsl = strlen(base);
    char buffer[wdl +2] = { 0 };
    strcpy(buffer, word);

    for (size_t i = 0; i < bsl; i++)
    {
        buffer[wdl] = base[i];
        //qDebug() << "from:" << word << "to:" << buffer;

        if (std::regex_match(buffer, rx))
        {
            state ns = state(get_pos(buffer), std::vector<state>());

            propagate(buffer, &ns, base, c -1);

            start->child.push_back(ns);
        }
        else
        {
            state ns = state(get_pos(buffer), std::vector<state>());

            propagate(buffer, start, base, c -1);

            //start->child.push_back(ns);
            ns.attach_children_vectors(start);
        }
    }
};

vec3 bruteforce::get_pos(char* word)
{
    vec3 ret;                                                   //def to zero
    size_t l = strlen(word);

    for (size_t i = 0; i < l; i++)
       (*((GLint*)(&ret) +(word[i] % 3)))++;                    // -'0' not needed, because '0' % 3 == 0

    return ret;
};

void bruteforce::combine(uint64_t i, char* base, char* buffer, size_t l)
{
    size_t base_l = strlen(base);
    if (!base_l) return;

    uint64_t o = 0;

    while (o < l)
    {
        buffer[o++] = base[i % base_l];
        i /= base_l;
    }
};



















