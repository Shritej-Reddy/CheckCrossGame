#pragma once

#include "FCheckCross.h"
#include <map>
using namespace std;

#define TMap std::map
using int32 = int;

FCheckCross::FCheckCross() { Reset(); }

int32 FCheckCross::GetCurrentTry() const { return MyCurrentTry; }
int32 FCheckCross::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FCheckCross::IsGameWon() const { return bGameIsWon; }

int32 FCheckCross::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,6}, {4,9}, {5,15}, {6,19}, {7,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FCheckCross::Reset()
{
	if (GameTry == 0)
	{
		const FString HIDDEN_WORD = "mix";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (GameTry == 1)
	{
		const FString HIDDEN_WORD = "lazy";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (GameTry == 2)
	{
		const FString HIDDEN_WORD = "plane";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (GameTry == 3)
	{
		const FString HIDDEN_WORD = "action";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (GameTry == 4)
	{
		const FString HIDDEN_WORD = "mezquit";
		MyHiddenWord = HIDDEN_WORD;
	}
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FCheckCross::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::Cool;
	}
}


FCheckCrossCount FCheckCross::ValidGuessSubmit(FString Guess)
{
	MyCurrentTry++;
	FCheckCrossCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FCheckCross::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else { 
			LetterSeen[Letter] = true;
		}	
	}

	return true;
}

bool FCheckCross::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
