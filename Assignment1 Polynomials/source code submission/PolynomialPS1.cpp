// COS30008, Tutorial 3, 2022

#include "Polynomial.h"
#include <cmath>
using namespace std;


double Polynomial::operator()(double aX) const
{
    double x = 0.0;
    for (int i = 0; i <= fDegree; i++)
    {
        x += fCoeffs[i] * pow(aX, i);
    }
    return x;
}
// derivative is broken
Polynomial Polynomial::getDerivative() const
{
    //Polynomial Result;

 //   Result.fDegree = Result.fDegree - 1;

   // return Result;
    Polynomial Result;
    Result.fDegree = fDegree - 1;
    for (int i = 1; i <= fDegree; i++)
    {
        Result.fCoeffs[i - 1] = fCoeffs[i] * 1;
    }
    return Result;
}

Polynomial Polynomial::getIndefiniteIntegral() const
{
    Polynomial Result;

    Result.fDegree = Result.fDegree + 1;
    for (int i = 0; i <= Result.fDegree; i++)
    {
        Result.fCoeffs[i+1] = fCoeffs[i] / fCoeffs[i+1];
    }


    return Result;
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const
{
    double result = 0.0;
    Polynomial Poly = getIndefiniteIntegral();
    for (int i= 0; i <= Poly.fDegree; i++)
    {
        result += Poly.fCoeffs[i] * pow(aXHigh, i);
        result -= Poly.fCoeffs[i] * pow(aXLow, i);
    }
    return result;
}


    // working out, can be ignored
	//Polynomial IndefIntegral = getIndefiniteIntegral();
	////this->getIndefiniteIntegral() - Result(aXHigh).getIndefiniteIntegral();
	//return 0.0f;
 //   double widthOfRectangle = (aXHigh - aXLow) / fDegree; 
 //   double area = 0.0;
 //   double heightOfRectangle = 0;
 //   
 //   for (int i = 0; i < fDegree; ++i)
 //   {
 //       heightOfRectangle = IndefIntegral(aXLow + (i + 0.5) * widthOfRectangle) * IndefIntegral(aXLow + (i + 0.5) * widthOfRectangle);
 //       area += heightOfRectangle * widthOfRectangle;  // find the area of the rectangle and add it to the previous area. Effectively summing up the area under the curve.
 //   }



