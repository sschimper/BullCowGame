/* The game logic:
This game is a simple guess-the-word-game based on Mastermind
*/

#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FWordList ThisWords;

FBullCowGame::FBullCowGame() {
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }




int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLenghtToMaxTries{ {3,10}, {4,10}, {5,15}, {7,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {

	bGameIsWon = false;

	MyCurrentTry = 1;
	return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString MyGuess) const {
	if (!IsIsogram(MyGuess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(MyGuess)) {
		return EGuessStatus::Wrong_Upper_Under_Case;
	}
	else if (MyGuess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Word_Length_Dont_Match;
	}
	else {
		return EGuessStatus::OK;
	}
}

void FBullCowGame::SetHiddenWord(FString Answer) {
	MyHiddenWord = Answer;
//	std::cout << "The hidden word: " << MyHiddenWord << std::endl;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString MyGuess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	IsIsogram(MyGuess);

	// loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();

	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the hidden word
		for (int32 j = 0; j < WordLength; ++j) {
			// find cows
			if (MyGuess[i] == MyHiddenWord[j]) {
				// make sure cows get not identified as bulls
				if (!(MyGuess[i] == MyHiddenWord[i])) {
					BullCowCount.Cows++;
				}			
			}
		}
		// find bulls
		if (MyGuess[i] == MyHiddenWord[i]) {
			BullCowCount.Bulls++;
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (char Letter : Word) {
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {
			return false; // NOT an isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}


