#include "KeyProvider.h"
using namespace std;

KeyProvider::KeyProvider(const std::string& aKeyword) :
	fSize(aKeyword.length()),
	fIndex(0)
{
	initialize(aKeyword);
}

KeyProvider::~KeyProvider()
{
	delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword)
{
	delete[] fKeyword;

	fSize = aKeyword.length();
	fKeyword = new char[fSize];

	for (size_t i = 0; i < fSize; i++)
	{
		this->fKeyword[i] = toupper(aKeyword.at(i));
	}

	fIndex = 0;
}

char KeyProvider::operator*() const
{
	return fKeyword[fIndex];
}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
	fKeyword[fIndex] = toupper(aKeyCharacter);
	if (++fIndex == fSize) 
	{
		fIndex = 0;
	}
	return (*this);
}


