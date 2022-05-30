
#include "Polygon.h"
#include <stdexcept>


Polygon::Polygon() : fNumberOfVertices(0)
{
	
}

size_t Polygon::getNumberOfVertices() const
{
	return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const
{
	if (aIndex < fNumberOfVertices) 
	{
	return fVertices[aIndex];
	}
	throw std::out_of_range::out_of_range("Illegal index value.");
}

void Polygon::readData(std::istream& aIStream) //inputs 2D vector from the input stream
{
	// while loop

	while (aIStream >> fVertices[fNumberOfVertices])
	{
		fNumberOfVertices++;
	}
}

float Polygon::getPerimeter() const
{
	float Result = 0.0f;
	if (fNumberOfVertices > 2)
	{
		for (size_t i = 1; i < fNumberOfVertices; i++)
		{
			Result += (fVertices[i] - fVertices[i - 1]).length();
		}
	}
	return Result;
	//for (size_t i = 0; i < fNumberOfVertices; i++)
	//{

	//	if(i % fNumberOfVertices)

	//	auto vertex1 = fVertices[i];
	//	auto vertext2 = fVertices[i % fNumberOfVertices];

	//	auto segment = (vertex1.getX() - vertext2.getX()) + (vertext2.getY() - vertext2.getY());

	//	Result += segment;

	//	int segment = v[i] + 1 - v[i];
		//you will need to use the modulus operator for the next vertex to guarantee that the value of i is in the
		//interval[0, fNumberOfVertices).
	//}%
	//return 0.0f;
}

Polygon Polygon::scale(float aScalar) const
{
	Polygon Result = *this;
	for (size_t i = 0; i < Result.fNumberOfVertices; i++)
	{
		Result.fVertices[i] = fVertices[i] * aScalar;
		//Result.fVertices->operator*(aScalar);
	}

	return Result;
}
