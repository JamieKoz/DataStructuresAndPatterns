#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) :
	fIStream(aIStream),
	fCurrentChar(0),
	fEOF(false)
{
	fIStream.seekstart();
	
	aIStream >> fCurrentChar;
}

char VigenereForwardIterator::operator*() const
{
	return this->fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
	VigenereForwardIterator result = *this;
	fIStream >> fCurrentChar;
	if (fIStream.eof()) {
		fEOF = true;
	}
	return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
	VigenereForwardIterator result = *this;
	if (fEOF == false) 
	{
		++(*this);
	}
	return result;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
	return fCurrentChar == aOther.fCurrentChar && fEOF == aOther.fEOF;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
	return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
	VigenereForwardIterator result = *this;
	result.fIStream.reset();
	return result;
}

VigenereForwardIterator VigenereForwardIterator::end() const
{
	VigenereForwardIterator Result = *this;
	Result.fEOF = true;
	return Result;
}
