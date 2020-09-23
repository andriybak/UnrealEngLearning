// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorEasy.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();

    FRotator CurrentRotation = GetOwner()->GetActorRotation();

    InitialYaw = CurrentRotation.Yaw;
    MaxYaw = CurrentRotation.Yaw + DoorOpeningAngle;

    Player = GetWorld()->GetFirstPlayerController()->GetPawn();
    DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && Player)
    {
        TArray<AActor *> OverlappingActors;
        TSubclassOf<AActor> SubClassFilter;
        PressurePlate->GetOverlappingActors(OverlappingActors, SubClassFilter);
        //UE_LOG(LogTemp, Warning, TEXT("Length of overlap is: %d"), OverlappingActors.Num());

        if (OverlappingActors.Num() > 0)
        {
            OpenDoor(DeltaTime);
            LastDoorOpenTime = GetWorld()->GetTimeSeconds();
        }
        else
        {
            CloseDoor(DeltaTime);
        }
    }
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
    FRotator CurrentRotation = GetOwner()->GetActorRotation();
    if (CurrentRotation.Yaw < MaxYaw)
    {
        if (!SoundForOpenDoor)
        {
            if (DoorSound)
            {
                DoorSound->Play();
                SoundForOpenDoor = true;
                SoundForCloseDoor = false;
            }
        }

        CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, MaxYaw, DeltaTime, DoorAngleOpeningStep);
        GetOwner()->SetActorRotation(CurrentRotation);
    }
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
    FRotator CurrentRotation = GetOwner()->GetActorRotation();
    if (CurrentRotation.Yaw > InitialYaw)
    {
        if (!SoundForCloseDoor)
        {
            if (DoorSound)
            {
                DoorSound->Play();
                SoundForCloseDoor = true;
                SoundForOpenDoor = false;
            }
        }

        CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, InitialYaw, DeltaTime, DoorAngleClosingStep);
        GetOwner()->SetActorRotation(CurrentRotation);
    }
}
