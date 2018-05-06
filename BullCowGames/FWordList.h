/* Three arrays containing English words for the game */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

using FString = std::string;
#define TMap std::map
using int32 = int;

class FWordList {
public:
	void loadWordsWithThreeLetters();
	void loadWordsWithFourLetters();
	void loadWordsWithFiveLetters();
	void loadWordsWithSevenLetters();

	void LoadWords(FString);

	FString ChooseHiddenWord();

	TMap<int32, FString> WordSetUnfiltered;
	TMap<int32, FString> WordSetFiltered;

	FString MyHiddenWord;
};
