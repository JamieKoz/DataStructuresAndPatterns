
// COS30008, Midterm, Problem 2, 2022

#include "Vigenere.h"

using namespace std;

void Vigenere::initializeTable()
{
	for ( char row = 0; row < CHARACTERS; row++ )
	{
		char lChar = 'B' + row;

		for ( char column = 0; column < CHARACTERS; column++ )
		{
            if ( lChar > 'Z' )
                lChar = 'A';

            fMappingTable[row][column] = lChar++;
		}
	}
}

Vigenere::Vigenere(const std::string& aKeyword) :
	fKeyword(aKeyword),
	fKeywordProvider(aKeyword)
{
	fMappingTable[CHARACTERS][CHARACTERS];
	initializeTable();
}

std::string Vigenere::getCurrentKeyword()
{
	string result;
	for (size_t i = 0; i < fKeyword.length(); i++)
	{
		char temp = *fKeywordProvider;
		fKeywordProvider << temp;
		result += fKeyword[i];
	}
	return result;
}

void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter)
{

	if (!isalpha(aCharacter)) {
		return aCharacter;
	}

	char rawKey = *fKeywordProvider;
	char key = toupper(rawKey) - 'A' + 1;
	char lCharacter = toupper(aCharacter) - 'A' - 1;
	char result = fMappingTable[key][lCharacter];
	fKeywordProvider << aCharacter;

	if (isupper(aCharacter)) {
		return toupper(result);
	}
	return tolower(result);
}

char Vigenere::decode(char aCharacter)
{
	if (!isalpha(aCharacter)) {
		return aCharacter;
	}

	char rawKey = *fKeywordProvider;
	char key = toupper(rawKey) - 'A';
	char encodedChar = toupper(aCharacter);

	char result;
	for (size_t i = 0; i < CHARACTERS; i++) {

		char columnChar = fMappingTable[key][i];
		
		if (encodedChar == columnChar) {
			result = i + 'A';
			break;
		}	
	}
	fKeywordProvider << result;

	if (isupper(aCharacter)) {
		return toupper(result);
	}
	return tolower(result);
}
