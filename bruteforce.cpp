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
    char* base = "012";
    size_t bsl = strlen(base), wdl = strlen(word);
    size_t bfl = (log(c) / log(bsl)) +wdl +1;           //get length of the number in the desired base plus the prefix length
    char buffer[bfl];

    //int wc = pow(bsl, c);                                //how many words could be in the language?

    strcpy(buffer, word);
    for (int i = 0; i < bsl; i++)                       //combine the actual state with all possible new ways
    {
        memset(buffer +wdl, 0, bfl -wdl);               //MARK IT ZERO
        buffer[wdl] = base[i];

        if (std::regex_match(buffer, rx))               //new combination get?
        {
            start->child.push_back(state(get_pos(buffer), std::vector<state>()));
            propagate(buffer, start, c-1);
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

void bruteforce::combine(int i, char* base, char* buffer)
{
    size_t base_l = strlen(base);
    if (!base_l) return;

    int o = 0;

    buffer[0] = '0';
    while (i)
    {
        buffer[o++] = base[i % base_l];
        i /= base_l;
    }
};



















