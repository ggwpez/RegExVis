#include <string.h>
#include <math.h>
#include <bitset>

#include "bruteforce.h"

bruteforce::bruteforce() { wac = 0; };

state bruteforce::propagate(char* regex, char* base, size_t c)
{
    state start = state(vec3(), std::vector<state>());

#ifdef C_REG
    if (regcomp(&rx, regex, REG_EXTENDED))
    {
        throw "RegExp invalid!";
        return start;
    }
#else
    rx = std::regex(regex);
#endif

    size_t bsl = strlen(base);
    uint64_t wc = pow(c, bsl +1) -1;

    qDebug() << "got:" << wc << "words to analyse" << (wc > 100000 ? "- Im choking on it!" : "");
    propagate("", &start, "012", c);

    qDebug() << "got:" << wac << "words to analyse" << (wc > 100000 ? "- Im choking on it!" : "");

    return start;
}

//### optimize
void bruteforce::propagate(char* word, state* start, char* base, size_t c)
{
    if (c < 2) return;

    size_t wdl = strlen(word), bsl = strlen(base);
    char buffer[wdl +c +1] = { 0 };
    strcpy(buffer, word);
    uint64_t wc = pow(c, bsl +1) -1;                               //how many new combinations are there? (word count)

    for (uint64_t i = 0; i < wc; i++)
    {
        memset(buffer +wdl, 0, c +1);
        combine(i, base, buffer +wdl, c);

        if (
#ifdef C_REG
        !regexec(&rx, buffer, 0, NULL, 0)
#else
        std::regex_match(buffer, rx)
#endif
                )
        {
            state ns = state(get_pos(buffer), std::vector<state>());

            propagate(buffer, &ns, base, c-1);

            start->child.push_back(ns);
        }
    }

    wac += wc;
};

vec3 bruteforce::get_pos(char* word)
{
    vec3 ret;                                            //def to zero
    size_t l = strlen(word);

    for (size_t i = 0; i < l; i++)
       (*((int*)(&ret) +((word[i] -'0') % 3)))++;               //because I can

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



















