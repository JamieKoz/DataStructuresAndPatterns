#include "ofstream12.h"
#include <fstream>

using namespace std;

void ofstream12::init()
{
	for (size_t i = 0; i < fBufferSize; i++)	//loop through the buffer
	{
		fBuffer[i] = 0;							//sets everything to zeros
		fByteIndex = 0;
		fBitIndex = 7;
	}
}

void ofstream12::writeBit0()
{
	completeWriteBit();							// init has set everything to zeros, if it is a zero just move on
}

void ofstream12::writeBit1()
{
	fBuffer[fByteIndex] += 1 << fBitIndex;		// fBuffer[fByteIndex] gets the byte in the buffer
	completeWriteBit();							// += 1 << fBitIndex  will append 1 to the next bitIndex
}

void ofstream12::completeWriteBit()
{
	fBitIndex--; // if on the 3rd bit then goes to the 2nd
	if (fBitIndex < 0) //reached the end of the byte
	{
		fByteIndex++; //move to the next byte
		fBitIndex = 7; 

		if (fByteIndex == fBufferSize) // buffer is full and needs to be written out and then refreshed for more input
		{
			flush();
		}
	}
}

ofstream12::ofstream12(const char* aFileName, size_t aBufferSize)
{
	//set up the buffer
	fBufferSize = aBufferSize;
	fBuffer = new byte[fBufferSize];

	//clears the buffer and sets all zeros
	init();

	//open the file to be read
	open(aFileName);
}

ofstream12::~ofstream12()
{
	close();
	delete[] fBuffer;
}

void ofstream12::open(const char* aFileName)
{
	if (aFileName)
	{
		fOStream.open(aFileName, ofstream::binary);
	}
}

void ofstream12::close()
{
	flush();
	fOStream.close();
}

bool ofstream12::good() const
{
	return fOStream.good();
}

bool ofstream12::isOpen() const
{
	return fOStream.is_open();
}

void ofstream12::flush()
{
	fOStream.write((char*)fBuffer, fByteIndex + (fBitIndex & 7 ? 1 : 0)); // write out chars, if bit index consists of 7 return 1 else return 0
	init();
}

ofstream12& ofstream12::operator<<(size_t aValue)
{
	for (size_t i = 0; i < 12; i++) //write 12 bits
	{
		if (aValue & 0x01)
		{
			writeBit1();
		}
		else
		{
			writeBit0();
		}
		aValue >>= 1; //aValue = aValue / 2; 
		return *this;
	}
}
