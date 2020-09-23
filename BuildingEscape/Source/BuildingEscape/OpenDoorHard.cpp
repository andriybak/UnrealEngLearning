// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorHard.h"

// Sets default values for this component's properties
UOpenDoorHard::UOpenDoorHard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorHard::BeginPlay()
{
	Super::BeginPlay();
    if(Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("There is player"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player was not set in here"));
    }	
}


// Called every frame
void UOpenDoorHard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
