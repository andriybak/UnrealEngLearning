// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorEasy.h"

#include "Components/ActorComponent.h"
#include "OpenDoorMedium.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorMedium : public UOpenDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorMedium();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    AActor *Player = nullptr;

private:

    void OpenDoor(float DeltaTime);
    void CloseDoor(float DeltaTime);

    bool SoundForOpenDoor = false;
    bool SoundForCloseDoor = true;

    UPROPERTY(EditAnywhere)
    float MinMassToOpenDoor = 50.0f;

    float InitialYaw = 0;

    float LastDoorOpenTime = 0.0f;
    float DoorClosingDelay = 1.0f;

    float DoorOpeningAngle = 90;
    float DoorAngleOpeningStep = 1;
    float DoorAngleClosingStep = 1;
};
