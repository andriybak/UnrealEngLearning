// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreTimer.h"
#include "Components/TextRenderComponent.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

#include "fstream"

// Sets default values for this component's properties
UHighScoreTimer::UHighScoreTimer()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

static TArray<float> GetSavedHighScores(const FString &SaveFileName)
{
    TArray<float> Result = {9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f};
    TArray<FString> StringValues;

    const FString PathToSaveFile = FPaths::AutomationDir();
    FString FileNamePath = PathToSaveFile + SaveFileName;
    UE_LOG(LogTemp, Warning, TEXT("Save path: %s"), *FileNamePath);

    if (FPaths::FileExists(FileNamePath))
    {
        FFileHelper::LoadANSITextFileToStrings(*FileNamePath, NULL, StringValues);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save file."));
    }

    for (int ii = 0; ii < Result.Num() && ii < StringValues.Num(); ii++)
    {
        Result[ii] = FCString::Atof(*StringValues[ii]);
    }

    Result.Sort();

    return Result;
}

static void WriteToHighScoresFile(const TArray<float> &Scores, const FString &SaveFileName)
{
    const FString PathToSaveFile = FPaths::AutomationDir();
    FString SaveFilePath = PathToSaveFile + SaveFileName;

    TArray<FString> StringScores;
    for (const auto Score : Scores)
    {
        StringScores.Add(FString::Printf(TEXT("%.2f"), Score));
    }

    FFileHelper::SaveStringArrayToFile(StringScores, *SaveFilePath);
}

static TArray<float> RecordHighScores(
    const TArray<float> &Scores,
    const float StartTimeSeconds,
    const float FinishTimeSeconds,
    const FString &SaveFileName)
{
    TArray<float> Result = Scores;
    const float GameTime = FinishTimeSeconds - StartTimeSeconds;
    Result.Add(GameTime);

    UE_LOG(LogTemp, Warning, TEXT("%.2f ____ %.2f"), StartTimeSeconds, FinishTimeSeconds);

    Result.Sort();
    Result.RemoveAt(Result.Num() - 1);

    WriteToHighScoresFile(Result, SaveFileName);

    return Result;
}

void UHighScoreTimer::UpdateScoresText()
{
    FString TotalScoreString = FString("");

    if (BestScoresTextRender)
    {
        auto TextComponent = BestScoresTextRender->GetTextRender();
        if (TextComponent)
        {
            for (int ii = 0; ii < SortedScores.Num(); ii++)
            {
                const float Score = SortedScores[ii];
                TotalScoreString = TotalScoreString + FString::Printf(TEXT("%d : %.2f\n"), ii + 1, Score);
                UE_LOG(LogTemp, Warning, TEXT("%s"), *TotalScoreString);
            }
        }

        TextComponent->SetText(TotalScoreString);
    }
}

// Called when the game starts
void UHighScoreTimer::BeginPlay()
{
    Super::BeginPlay();

    GameOver = false;
    StartTimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    Player = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (BestScoresTextRender)
    {
        auto TextComponent = BestScoresTextRender->GetTextRender();

        FString TotalScoreString = TEXT("1: 0\n2: 0\n3: 0\n4: 0 \n5: 0");
        SortedScores = GetSavedHighScores(SaveFileName);

        if (SortedScores.Num() > 0)
        {
            TotalScoreString = FString("");
            for (int ii = 0; ii < SortedScores.Num(); ii++)
            {
                const float Score = SortedScores[ii];
                TotalScoreString = TotalScoreString + FString::Printf(TEXT("%d : %.2f\n"), ii + 1, Score);
                UE_LOG(LogTemp, Warning, TEXT("%s"), *TotalScoreString);
            }
        }

        TextComponent->SetText(FText::FromString(TotalScoreString));
    }
}

// Called every frame
void UHighScoreTimer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TSubclassOf<AActor> SubClass;
    TArray<AActor *> OverlappingActors;
    EndGameTriggerPlate->GetOverlappingActors(OverlappingActors, SubClass);
    if (OverlappingActors.Num() > 0)
    {
        for (const auto Actor : OverlappingActors)
        {
            if (Actor->GetName() == Player->GetName() && !GameOver)
            {
                GameOver = true;
                UE_LOG(LogTemp, Warning, TEXT("Actor finished level! Do updates in system."));
                EndTimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
                SortedScores = RecordHighScores(SortedScores, StartTimeSeconds, EndTimeSeconds, SaveFileName);
                UpdateScoresText(); //maybe make it pure static?
            }
        }
    }
}
