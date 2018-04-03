#pragma once
#include <string>

using FString = std::string;

struct FCheckCrossCount
{
	int Bulls = 0;
	int Cows = 0;
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
	int GameTry;
	FString MyHiddenWord;
	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FCheckCrossCount ValidGuessSubmit(FString);
	friend std::ostream& operator<<(std::ostream& ps, FCheckCross D);
	bool RetryGame(FCheckCross);
private:
	int MyCurrentTry;
	
	
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};