// Fill out your copyright notice in the Description page of Project Settings.

#include "Croucher.h"

// Sets default values for this component's properties
UCroucher::UCroucher()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCroucher::CrouchOrStand()
{
    if(IsStanding)
    {
        IsStanding = false;
    }
    else
    {
        IsStanding = true;
    }  
}

// Called when the game starts
void UCroucher::BeginPlay()
{
	Super::BeginPlay();

    const auto World = GetWorld();
    if(World)
    {
        const auto FirstPlayerController = World->GetFirstPlayerController();
        if(FirstPlayerController)
        {
            Player = FirstPlayerController->GetPawn();
        }
    }

    if(Player)
    {
        StandHeight = Player->BaseEyeHeight;
        CrouchHeight = 0.5f * StandHeight;

        CrouchInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
        if(CrouchInputComponent)
        {
            CrouchInputComponent->BindAction("Crouch", IE_Released, this, &UCroucher::CrouchOrStand);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("CrouchInputComponent was not found."));
        }
    }
}

// Called every frame
void UCroucher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(Player)
    {
        float PlayerEyeHeigh = Player->BaseEyeHeight;
        //UE_LOG(LogTemp, Warning, TEXT("Start : %f"), PlayerEyeHeigh);
        if(IsStanding && std::abs(PlayerEyeHeigh - StandHeight) > FLT_EPSILON )
        {
            PlayerEyeHeigh = FMath::FInterpTo(PlayerEyeHeigh, StandHeight, DeltaTime, StandSitSpeed);
            Player->BaseEyeHeight = PlayerEyeHeigh;
        }
        else if(!IsStanding && std::abs(PlayerEyeHeigh - CrouchHeight) > FLT_EPSILON)
        {
            PlayerEyeHeigh = FMath::FInterpTo(PlayerEyeHeigh, CrouchHeight, DeltaTime, StandSitSpeed);
            Player->BaseEyeHeight = PlayerEyeHeigh;
        }
    }    
}
