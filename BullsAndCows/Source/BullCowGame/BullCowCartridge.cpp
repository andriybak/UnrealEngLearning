// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

FString ChosenWord = "";
FString HiddenString = "";
int32 PlayerLives = 0;

TArray<FString> Words = { TEXT("abc"), TEXT("abcd"), TEXT("abcde") };

static bool IsIsogram(FString word)
{
    for(int ii = 0; ii < word.Len(); ii++)
    {
        auto copy = word;
        copy.RemoveAt(ii);
        int32 pos = 0;
        if(copy.FindChar(word[ii], pos))
        {
            return false;
        }
    }

    return true;
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    ClearScreen();
    ChosenWord = TEXT("cake");
    HiddenString = TEXT("****");
    PlayerLives = ChosenWord.Len();

    PrintLine(TEXT("Welcome to Bull Cow game!"));
    PrintLine(FString::Printf(TEXT("Guess %i letter word"), ChosenWord.Len()));
    PrintLine(HiddenString);
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("GAME OVER!"));
    ClearScreen();
    BeginPlay();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(Input.IsEmpty() || Input.Len() != 1)
    {
        PlayerLives -= 1;
        if(PlayerLives == 0)
        {
            EndGame();
        }
        else
        {
            PrintLine(FString::Printf(TEXT("Whong input! The input should be only 1 letter from the word! Try again! %i lives left"), PlayerLives));
        }
    }
    else
    {
        if(ChosenWord.Contains(Input))
        {
            PrintLine(TEXT("Good job! 1 Letter guessed! YOU WON!"));
        }
        else
        {
            PlayerLives -= 1;
            if(PlayerLives == 0)
            {
                EndGame();
            }
            else
            {
                PrintLine(TEXT("Whong input! The input should be only 1 letter from the word! Try again! %i lives left"), PlayerLives);
            }
        }        
    }
}