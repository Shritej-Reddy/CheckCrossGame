#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FCheckCrossCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Wrong_Status,
	Cool,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FCheckCross
{
public:
	FCheckCross();
	int32 GameTry;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FCheckCrossCount ValidGuessSubmit(FString);


private:
	int32 MyCurrentTry;
	
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};