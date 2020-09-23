// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorMedium.h"

// Sets default values for this component's properties
UOpenDoorMedium::UOpenDoorMedium()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoorMedium::BeginPlay()
{
	Super::BeginPlay();

    FRotator CurrentRotation = GetOwner()->GetActorRotation();

    InitialYaw = CurrentRotation.Yaw;
    MaxYaw = CurrentRotation.Yaw + DoorOpeningAngle;

    Player = GetWorld()->GetFirstPlayerController()->GetPawn();

    DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	
}

void UOpenDoorMedium::OpenDoor(float DeltaTime)
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

void UOpenDoorMedium::CloseDoor(float DeltaTime)
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

static float GetTotalMassFromActors(const TArray<AActor *> &OverlappingActors)
{
    float TotalMass = 0.0f;
    TSubclassOf<UPrimitiveComponent> SubClassFilter;
    for(const AActor *Actor : OverlappingActors)
    {
        const UPrimitiveComponent *RootComponent = static_cast<UPrimitiveComponent *>(Actor->GetRootComponent());
        if (RootComponent)
        {
            const auto ActorMass = RootComponent->GetMass();
            TotalMass += ActorMass;
        }
    }

    return TotalMass;
}

// Called every frame
void UOpenDoorMedium::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    //Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && Player)
    {
        TArray<AActor *> OverlappingActors;
        TSubclassOf<AActor> SubClassFilter;
        PressurePlate->GetOverlappingActors(OverlappingActors, SubClassFilter);


        const float TotalMass = GetTotalMassFromActors(OverlappingActors);
        //UE_LOG(LogTemp, Warning, TEXT("Length of overlap is: %d : Mass is : %f"), OverlappingActors.Num(), TotalMass);
        if (OverlappingActors.Num() > 2 && TotalMass >= MinMassToOpenDoor)
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