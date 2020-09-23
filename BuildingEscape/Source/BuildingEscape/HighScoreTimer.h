// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"

#include "HighScoreTimer.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UHighScoreTimer : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHighScoreTimer();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

    void UpdateScoresText();

    float StartTimeSeconds = 0.0f;
    float EndTimeSeconds = 0.0f;

    TArray<float> SortedScores = { 9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f };

    UPROPERTY(EditAnywhere)
    ATextRenderActor *BestScoresTextRender = nullptr;

    UPROPERTY(EditAnywhere)
    AActor *EndGameTriggerPlate = nullptr;

    AActor *Player = nullptr;

    const FString SaveFileName = "BuildingEscapeHighScores.scores";

    bool GameOver = false;
};
