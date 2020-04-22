#ifndef UTILSH
#define UTILSH

#include <random>
#include <ctime>

float randfloat()
{
    static default_random_engine e(time(0));
    static uniform_real_distribution <float> u(0, 1);
    return u(e);
}

#endif // UTILSH
