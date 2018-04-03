#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <Windows.h>
#include "FCheckCross.h"
using namespace std;

using FText = std::string;

void PlayGame();
FText ValidGuessAccept();
void PrintGameLog();
void wait(int seconds);

FCheckCross CCGame;

class Dummy
{
public:
	virtual void Introduction() = 0;
};

class Dummy1:public Dummy
{
	public:
	void Introduction()
	{
		std::cout << "Welcome to Checks And Crosses, a fun word game.\n";
		std::cout << std::endl;

		std::string wave;
		std::string::iterator point;
		char letter;
		int length, time, i = 0, j = 0;

		length = 8;
		time = 50;
		letter = '^';
		while (j <= length) {
			wave += letter;
			j++;
		}

		for (i = 0; i<13; i++) {
			point = wave.begin() + wave.size() - 1;
			wave.erase(point);
			Sleep(time);
			std::cout << wave << std::endl;
			if (wave.size() == 1) {
				for (i = 0;; i++) {
					Sleep(125);
					wave += letter;
					std::cout << wave << std::endl;
					if (wave.size() == length) {
						break;
					}
				}
			}
		}
		cout << "^" << endl;


		std::cout << "Can you guess the " << CCGame.GameTry + 3;
		std::cout << " letter isogram I'm thinking of?\n";
		std::cout << std::endl;
		return;
	}
};

void PlayGame()
{
	CCGame.Reset();
	int MaxTries = CCGame.GetMaxTries();
	
	while (!CCGame.IsGameWon() && CCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = ValidGuessAccept();
		std::ifstream in("file1");
		std::ofstream out("file1", ios::out | ios::app);
		if (!in | !out) {
			cout << "file error:cannot open file\n";
		}
		FText Guess1;
		Guess1 = Guess+"\t";
		out << Guess1;
		FCheckCrossCount CheckCrossCount = CCGame.ValidGuessSubmit(Guess);

	    
		std::cout << "Checks = " << CheckCrossCount.Bulls;
		int Bulls1 = CheckCrossCount.Bulls;
		out << Bulls1;
		std::cout << ". Crosses = " << CheckCrossCount.Cows << "\n\n";
		int Cows1 = CheckCrossCount.Cows;
		out << "\t";
		out << Cows1<<endl;
		in.close();
		out.close();
	}

	PrintGameLog();
	return;
}

FText ValidGuessAccept()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Wrong_Status;
	do {
		int CurrentTry = CCGame.GetCurrentTry();
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

bool FCheckCross::RetryGame(FCheckCross D)
{
	if (CCGame.GameTry == 4)
	{
		std::cout << "You've reached the end of this game"<<std::endl;
		std::cout << "Thank You For Playing";
		wait(5);
		return 0;
	}
	std::cout << "You've Completed The Game In " << CCGame.MyCurrentTry-1<<std::endl;
	std::cout << "Do you want to play again with another hidden word of length : "<<(CCGame.GameTry)+4<<" (y/n)? ";
	FText Response = "";
	CCGame.GameTry++;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameLog()
{
	char c;
	if (CCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	ifstream in("file1");
	ofstream out("file1", ios::out | ios::app);
	in.seekg(0, ios::beg);
	cout << "\n";
	while (in.get(c))
		cout << c;
	cout << "\n";
	in.clear();
	out.clear();
	in.close();
	out.close();
}

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

ostream& operator<<(ostream& ps, FCheckCross DCCD)
{
	ps <<DCCD.GameTry+1<<endl;
	return ps;
}

int main()
{
	FCheckCross D;
	Dummy1 D1;
	bool bPlayAgain = false;
	do {
		D1.Introduction();
		PlayGame();
		bPlayAgain = D.RetryGame(D);
	} while (bPlayAgain);

	return 0;
}