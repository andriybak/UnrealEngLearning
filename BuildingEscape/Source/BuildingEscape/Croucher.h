// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"

#include "Croucher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UCroucher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCroucher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

    void CrouchOrStand();

    //Indicates if current attached actor is standing full height, otherwise crouched.
    bool IsStanding = true;

    UInputComponent *CrouchInputComponent = nullptr;
    APawn *Player = nullptr;

    float CrouchHeight = 50.0f;
    float StandHeight = 100.0f;

    float StandSitSpeed = 3.0f;
};
