// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoorEasy.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoor();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    void OpenDoor(float DeltaTime);
    void CloseDoor(float DeltaTime);

    bool SoundForOpenDoor = false;
    bool SoundForCloseDoor = true;

    AActor *Player = nullptr;

    UPROPERTY(EditAnywhere)
    UAudioComponent *DoorSound = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float MaxYaw = 90;

    float InitialYaw = 0;

    float LastDoorOpenTime = 0.0f;
    float DoorClosingDelay = 1.0f;

    float DoorOpeningAngle = 90;
    float DoorAngleOpeningStep = 1;
    float DoorAngleClosingStep = 0.75;
};
