#include "BernsteinBasisPolynomial.h"
BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN)
{
}

double BernsteinBasisPolynomial::operator()(double aX) const
{
	double cube = (1 - aX) * (1 - aX) * (1 - aX);
	double xSquared = aX * aX;
	return (10 * xSquared) * cube;
}
