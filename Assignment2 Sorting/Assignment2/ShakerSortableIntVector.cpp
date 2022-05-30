
#include "SortableIntVector.h"
#include "ShakerSortableIntVector.h"

using namespace std;



ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : SortableIntVector::SortableIntVector(aArrayOfIntegers, aNumberOfElements)
{}


void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
    int start = 0;
    int end = size() - 1;
    while (start < end)
    {
        for (int i = start; i < end; ++i)
        {
            if (aOrderFunction(get(i), get(i + 1)))		// if the comparable returns true
            {
                swap(i, i + 1);			//swap the values
            }
        }
        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (aOrderFunction(get(i), get(i + 1)))		// if the comparable returns true
            {
                swap(i, i + 1);			//swap the values
            }
        }
        ++start;
    }
}

