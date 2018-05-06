#include "FWordList.h"
#include "FBullCowGame.h"

FBullCowGame Bc;

void FWordList::loadWordsWithThreeLetters() {
	FString line;
	std::ifstream myfile ("D:\\Programming\\Unreal Development\\Section_02\\BullCowGames\\wordsThreeLetters.txt");

	if (myfile.is_open()) {
		int i = 0;
		while (i < 441) {
			getline(myfile, line);
			myfile >> line;
			WordSetUnfiltered[i] = line;
			i++;
		}
	}

	else std::cout << "Unable to open file. ";

	return;
}

void FWordList::loadWordsWithFourLetters() {
	FString line;
	std::ifstream myfile("D:\\Programming\\Unreal Development\\Section_02\\BullCowGames\\wordsFourLetters.txt");

	if (myfile.is_open()) {
		int i = 0;
		while (i < 173) {
			getline(myfile, line);
			myfile >> line;
			WordSetUnfiltered[i] = line;
			i++;
		}
	}

	else std::cout << "Unable to open file. ";

	return;
}

void FWordList::loadWordsWithFiveLetters() {
	FString line;
	std::ifstream myfile;
	myfile.open("D:\\Programming\\Unreal Development\\Section_02\\BullCowGames\\wordsFiveLetters.txt");

	if (myfile.is_open()) {
		int i = 0;
		while (i < 173) {
			getline(myfile, line);
			myfile >> line;
			WordSetUnfiltered[i] = line;
			i++;
		}
	}


	else std::cout << "Unable to open file. ";

	return;
}

void FWordList::loadWordsWithSevenLetters() {
	FString line;
	std::ifstream myfile("D:\\Programming\\Unreal Development\\Section_02\\BullCowGames\\wordsSevenLetters.txt");

	if (myfile.is_open()) {
		int i = 0;
		while (i < 173) {
			getline(myfile, line);
			myfile >> line;
			WordSetUnfiltered[i] = line;
			i++;
		}
	}

	else std::cout << "Unable to open file. ";

	return;
}

FString FWordList::ChooseHiddenWord()
{
	int RandomNumber;
	srand(time(0));

	RandomNumber = (rand() % WordSetFiltered.size());
	return WordSetFiltered[RandomNumber];
}

 void FWordList::LoadWords(FString UserAnswer) {
	 // clear maps with filtered words

	// greate word map from dictionary file
	if (UserAnswer == "3") {
		loadWordsWithThreeLetters();
		int i = 0;
		int j = 0;
		while (i < WordSetUnfiltered.size()) {
			if (Bc.IsIsogram(WordSetUnfiltered[i])) {
				WordSetFiltered.insert(std::pair<int, FString> (j, WordSetUnfiltered[i]));
				j++;
			}
			i++;
		}
	}
	
	else if (UserAnswer == "4") {
		loadWordsWithFourLetters();
		int i = 0;
		int j = 0;
		while (i < WordSetUnfiltered.size()) {
			if (Bc.IsIsogram(WordSetUnfiltered[i])) {
				WordSetFiltered.insert(std::pair<int, FString>(j, WordSetUnfiltered[i]));
				j++;
			}
			i++;
		}
	}

	else if (UserAnswer == "5") {
		loadWordsWithFiveLetters();
		int i = 0;
		int j = 0;
		while (i < WordSetUnfiltered.size()) {
			if (Bc.IsIsogram(WordSetUnfiltered[i])) {
				WordSetFiltered.insert(std::pair<int, FString>(j, WordSetUnfiltered[i]));
				j++;
			}
			i++;
		}
	}
	
	else {
		loadWordsWithSevenLetters();
		int i = 0;
		int j = 0;
		while (i < WordSetUnfiltered.size()) {
			if (Bc.IsIsogram(WordSetUnfiltered[i])) {
				WordSetFiltered.insert(std::pair<int, FString>(j, WordSetUnfiltered[i]));
				j++;
			}
			i++;
		}
	}

	return;
}
