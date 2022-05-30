
// COS30008, Tutorial 2, 2022

#include "Polygon.h"

#include <stdexcept>

using namespace std;


float Polygon::getSignedArea() const
{
	double leftSum = 0.0;
	double rightSum = 0.0;

	for (int i = 0; i < fNumberOfVertices; ++i) {
		int j = (i + 1) % fNumberOfVertices;
		leftSum += fVertices[i].getX() * fVertices[j].getY();
		rightSum += fVertices[j].getX() * fVertices[i].getY();
	}

	return 0.5 * abs(leftSum - rightSum);
}
