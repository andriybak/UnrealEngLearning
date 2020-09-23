// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenDoorMedium.h"

#include "Components/ActorComponent.h"
#include "OpenDoorHard.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoorHard : public UOpenDoorMedium
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoorHard();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    //TODO: This class should combine idea of easy + medium and make it much harder to open door. maybe defining unique objects to overlap + min num of objects and their masS?
    UPROPERTY(EditAnywhere)
    int NumberOfUniqueObjects = 3;

    UPROPERTY(EditAnywhere)
    TArray<AActor *> ActorArrayToOpenDoor;
};
