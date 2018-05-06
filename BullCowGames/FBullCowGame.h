/* The game logic:
This game is a simple guess-the-word-game based on Mastermind
*/

#pragma once
#include <string>
#include "FWordList.h"

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Word_Length_Dont_Match,
	Wrong_Upper_Under_Case
};


class FBullCowGame {
public:
	FBullCowGame(); // constructor
	
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	bool IsIsogram(FString) const;
	EGuessStatus CheckGuessValidity(FString MyGuess) const;
	void SetHiddenWord(FString);
	

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsLowercase(FString) const;
};