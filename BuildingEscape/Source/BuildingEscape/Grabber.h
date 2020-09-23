// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    void GrabOrRelease();

    FHitResult GetHitResult(const FVector &StartPoint, const FVector &EndPoint);
    std::pair<FVector, FVector> GetPlayerGrabStartAndEndPoints();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    bool IsGrabbed = false;
    float PlayerReach = 100.0f;

    UPhysicsHandleComponent *PhysicsHandle = nullptr;

    UInputComponent *GrabInputComponent = nullptr;
};
