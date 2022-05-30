
#include "SortableIntVector.h"

using namespace std;

SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : IntVector::IntVector(aArrayOfIntegers, aNumberOfElements)
{}

void SortableIntVector::sort(Comparable aOrderFunction)
{
	for (size_t i = 0; i < size() - 1; i++)			//loop through size of the array -1
	{
		for (size_t j = 0; j < size() - i - 1; j++)	//inner loop 
		{
			if (aOrderFunction(get(j), get(j + 1)))		// if the comparable returns true
			{
				swap(j, j + 1);			//swap the values
			}
		}
	}
}





