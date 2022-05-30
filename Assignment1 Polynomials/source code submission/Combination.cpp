#include "Combination.h"
Combination::Combination(size_t aN, size_t aK)
{
	fN = aN;
	fK = aK;
}

size_t Combination::getN() const
{
	return this->fN;
}

size_t Combination::getK() const
{
	return this->fK;
}

unsigned long long Combination::operator()() const
{
    int result = 1;
    size_t lK = fK;

    if (lK > fN - lK)
    {
        lK = fN - lK;
    }
    for (int i = 0; i < lK; ++i)
    {
        result *= (fN - i);
        result /= (i + 1);
    }

    return result;
}
