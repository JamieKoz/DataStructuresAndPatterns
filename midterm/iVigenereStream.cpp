#include "Vigenere.h"
#include "iVigenereStream.h"
#include <fstream>
using namespace std;


iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) :
	fCipherProvider(aKeyword)
{
	fCipher = aCipher;

	if (!nullptr) 
	{
		fIStream.open(aFileName);
	}
}

iVigenereStream::~iVigenereStream()
{
	close();
}

void iVigenereStream::open(const char* aFileName)
{
	if (aFileName)
	{
		fIStream.open(aFileName, ofstream::binary);
	}
}

void iVigenereStream::close()
{
	fIStream.close();
}

void iVigenereStream::reset()
{
	fCipherProvider.reset();
	seekstart();
}

bool iVigenereStream::good() const
{
	return fIStream.good();
}

bool iVigenereStream::is_open() const
{
	return fIStream.is_open();
}

bool iVigenereStream::eof() const
{
	return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	char temp;
	if (fCipher.operator bool() && fIStream.get(temp))
	{
		aCharacter = fCipher(fCipherProvider, temp);
	}
	return *this;
}
