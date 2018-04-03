#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include "FCheckCross.h"

using FText = std::string;
using int32 = int;

void Introduction();
void PlayGame();
FText ValidGuessAccept();
bool RetryGame();
void PrintGameLog();
void wait(int seconds);

FCheckCross CCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		Introduction();
		PlayGame();
		bPlayAgain = RetryGame();
	}
	while (bPlayAgain);

	return 0;
}

void Introduction()
{
	std::cout << "Welcome to Checks And Crosses, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "               _______"<<std::endl;
	std::cout << "        /|	|\    /|" << std::endl;
	std::cout << " |\    / |    | \  / |" << std::endl;
	std::cout << " | \  /  |	|  \/  |" << std::endl;
	std::cout << " |  \/   |	|  /\  |" << std::endl;
	std::cout << " |       |    | /  \ |" << std::endl;
	std::cout << " |_______|	|/____\|" << std::endl;
	std::cout << "Can you guess the " << CCGame.GameTry+3;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	CCGame.Reset();
	int32 MaxTries = CCGame.GetMaxTries();
	
	while (!CCGame.IsGameWon() && CCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = ValidGuessAccept();
		
		FCheckCrossCount CheckCrossCount = CCGame.ValidGuessSubmit(Guess);

		std::cout << "Checks = " << CheckCrossCount.Bulls;
		std::cout << ". Crosses = " << CheckCrossCount.Cows << "\n\n";
	}

	PrintGameLog();
	return;
}

FText ValidGuessAccept()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Wrong_Status;
	do {
		int32 CurrentTry = CCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << CCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = CCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << CCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Cool);
	return Guess;
}

bool RetryGame()
{
	if (CCGame.GameTry == 4)
	{
		std::cout << "You've reached the end of this game"<<std::endl;
		std::cout << "Thank You For Playing";
		wait(5);
		return 0;
	}
	std::cout << "Do you want to play again with another hidden word of length : "<<(CCGame.GameTry)+4<<" (y/n)? ";
	FText Response = "";
	CCGame.GameTry++;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameLog()
{
	if (CCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}