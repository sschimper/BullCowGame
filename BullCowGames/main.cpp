/* This is the console executable that makes use 
of the BullCowClass. This acts as the view in an MVC
pattern, and is responsible for all user int32eraction.
For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

#include "FWordList.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FString SetDifficulty();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary(bool b);
bool AskToPlayAgain();

FBullCowGame BCGame;
FWordList Words;

int main() {
	
	do {
		//intro
		PrintIntro();

		// select difficulty, load words from file and set hidden word
		FString Answer = SetDifficulty();
		Words.LoadWords(Answer);
		FString Word = Words.ChooseHiddenWord();
		BCGame.SetHiddenWord(Word);

		// play the actual game
		PlayGame();

		PrintGameSummary(BCGame.IsGameWon());
	} while (AskToPlayAgain() == true);


	return 0;
}

void PrintIntro() {
	// introduce the game   
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "                           #####                              " << std::endl;
	std::cout << "                         #### _\_                             " << std::endl;
	std::cout << "                        ##=-[.].]   :::                       " << std::endl;
	std::cout << "                        #(    _\   `'_:                       " << std::endl;
	std::cout << "                         #  \__|    | |                       " << std::endl;
	std::cout << "                          \___/     | |                       " << std::endl;
	std::cout << "                        .'   `-----'  |						" << std::endl;
	std::cout << "                       ( )     ,------'						" << std::endl;
	std::cout << "                       | |     |          _     _				" << std::endl;
	std::cout << "                       | |     |         ((_____))			" << std::endl;
	std::cout << "                       | |     |          [o   o]             " << std::endl;
	std::cout << "                       |_|==o=={         / \   /				" << std::endl;
	std::cout << "                       :..     |        /  (o o)				" << std::endl;
	std::cout << "           .------------'''  Y---------'     U				" << std::endl;
	std::cout << "          |               |  |              /					" << std::endl;
	std::cout << "         |                |  |             |					" << std::endl;
	std::cout << "        :|                }  )            |					" << std::endl;
	std::cout << "       : |       _        |  |           |					" << std::endl;
	std::cout << "      :  |      / \       |__|_          |					" << std::endl;
	std::cout << "     :   |     /   \      [____)         |					" << std::endl;
	std::cout << "   :     |   /\___/\______________\   |  |					" << std::endl;
	std::cout << "  #      |  /  uuu                 |  |  |					" << std::endl;
	std::cout << "         | |   | |                 |  |  |					" << std::endl;
	std::cout << "         | |   | |                 | || |					    " << std::endl;
	std::cout << "         | |   | |                 | || |						" << std::endl;
	std::cout << "         |\\   |\\                 |\\|\\ dp					" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Welcome to Bulls 'n' Cows, a fun word game!" << std::endl;
	std::cout << std::endl;

	return;
}

FString SetDifficulty() {
	std::cout << "Please select difficutly: " << std::endl;
	std::cout << "For a SUPER EASY GAME (Word with three letters) select '3' on your keyboard!" << std::endl;
	std::cout << "For an EASY GAME (Word with four letters) select '4' on your keyboard!" << std::endl;
	std::cout << "For a MEDIUM GAME (Word with five letters) select '5' on your keyboard!" << std::endl;
	std::cout << "For a HARD GAME (Word with seven letters) select '7' on your keyboard!" << std::endl;
	std::cout << std::endl;

	FText UserAnswer = "";
	do {
		std::getline(std::cin, UserAnswer);
		if ((UserAnswer != "3") && (UserAnswer != "4") && (UserAnswer != "5") && (UserAnswer != "7")) {
			std::cout << " Please enter one of the following numbers: '3,4,5,7' " << std::endl;
		}
	} while ((UserAnswer != "3") && (UserAnswer != "4") && (UserAnswer != "5") && (UserAnswer != "7"));
	

	std::cout << std::endl;
	return UserAnswer;
}


void PlayGame() {
	BCGame.Reset();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	int32 MaxTries = BCGame.GetMaxTries();
	
	while ((!BCGame.IsGameWon()) && (BCGame.GetCurrentTry() <= MaxTries)) {
		FText Guess = GetValidGuess();

		// submit valid guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	return;
}

FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout <<". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Word_Length_Dont_Match:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n" << std::endl;
			break;
		case EGuessStatus::Wrong_Upper_Under_Case:
			std::cout << "Please enter the word in UNDERCASE letters!\n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter the word without repeating letters! \n" << std::endl;
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGameSummary(bool b) {
	if (b == true) {
		std::cout << "YOU WON! Good job!" << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << "You idiot!" << std::endl;
		std::cout << "The word I was looking for is '" << BCGame.GetHiddenWord() << "'." << std::endl;
		std::cout << "YOU LOST! Better luck next time, buddy!" << std::endl;
		std::cout << std::endl;
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you wanna play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response[0] == 'Y' || Response[0] == 'y') {
		return true;
	}
	else if (Response[0] == 'N' || Response[0] == 'n') {
		return false;
	}
	else {
		return false;
	}	
}