// Fill out your copyright notice in the Description page of Project Settings.

#include "GuessWordCartridge.h"

TArray<FString> WordList =
	{ TEXT("hey"), TEXT("sup"), TEXT("hello"), TEXT("fox"), TEXT("cow"), TEXT("wolf"), TEXT("animal") };

FString SelectedWord = "";
FString CurrentGuess = "";
int32 PlayerLives = 0;

static FString InitializePlayerWord(const FString &Word)
{
	FString Hidden = "";
	for(const auto &Letter : Word)
	{
		Hidden.Append("*");
	}

	return Hidden;
}

void UGuessWordCartridge::InitializeGame()
{
	const auto MaxNum = WordList.Num();
	const auto WordIndex = FMath::FRandRange(0, MaxNum - 1);

	SelectedWord = WordList[WordIndex];
	PlayerLives = SelectedWord.Len();

	CurrentGuess = InitializePlayerWord(SelectedWord);

	PrintLine(FString::Printf(TEXT("Guess the word of %d letters! %s"), PlayerLives, *SelectedWord));
	PrintLine(FString::Printf(TEXT("You have %d lives!"), PlayerLives));
	PrintLine(TEXT("Enter 1 letter at a time for a guess!"));
}

// Called when the game starts
void UGuessWordCartridge::BeginPlay()
{
	Super::BeginPlay();

	ClearScreen();
	InitializeGame();
}

static bool IsCorrectLetter(const FString &Word, const FString &Letter)
{
	return Word.Contains(Letter);
}

static FString AddLetterToGuess(const FString &Word, const FString &CurrentGuess, const FString &Letter)
{
	FString Hidden = CurrentGuess;
	const auto Char = Letter.ToLower()[0];
	for(int ii = 0; ii < Word.Len(); ii++)
	{
		if(Char == Word[ii])
		{
			Hidden[ii] = Char;
		}
	}

	return Hidden;
}

void UGuessWordCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if(Input.Len() == 1)
	{
		const bool bIsCorrent = IsCorrectLetter(SelectedWord, Input);
		if(bIsCorrent)
		{
			CurrentGuess = AddLetterToGuess(SelectedWord, CurrentGuess, Input);
			PrintLine(FString::Printf(TEXT("Good Job!, lives left: %d"), PlayerLives));
		}
		else
		{
			PrintLine(FString::Printf(TEXT("Wrong amount of letters, lives left: %d"), --PlayerLives));
		}

		PrintLine(FString::Printf(TEXT("Current word: %s"), *CurrentGuess));	
	}
	else
	{
		PrintLine(FString::Printf(TEXT("Wrong amount of letters, lives left: %d"), --PlayerLives));
	}

	if(CurrentGuess.Equals(SelectedWord))
	{
		ClearScreen();
		PrintLine(TEXT("CONGRATS! YOU WON! WOOOO"));
		InitializeGame();
	}

	if(PlayerLives == 0)
	{
		ClearScreen();
		PrintLine(TEXT("Game Over!"));
		InitializeGame();
	}
}
