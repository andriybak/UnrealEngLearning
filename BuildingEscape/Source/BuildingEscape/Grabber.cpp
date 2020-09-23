#include "Grabber.h"

#include <utility>

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

std::pair<FVector, FVector> UGrabber::GetPlayerGrabStartAndEndPoints()
{
    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

    FVector LineStart = PlayerLocation;
    FVector LineEnd = PlayerLocation + PlayerRotation.GetNormalized().Vector() * PlayerReach;

    return std::make_pair(LineStart, LineEnd);
}

FHitResult UGrabber::GetHitResult(const FVector &StartPoint, const FVector &EndPoint)
{
    FHitResult PlayerHit;
    FCollisionQueryParams Params(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(PlayerHit, StartPoint, EndPoint, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Params);

    return PlayerHit;
}

void UGrabber::GrabOrRelease()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab was pressed."));

    if(IsGrabbed)
    {
        UE_LOG(LogTemp, Warning, TEXT("Grab was released."));
        PhysicsHandle->ReleaseComponent();
        IsGrabbed = false;
    }
    else
    {
        const auto PlayerLocationAndGrabEnd = GetPlayerGrabStartAndEndPoints();
        FHitResult PlayerHit = GetHitResult(PlayerLocationAndGrabEnd.first, PlayerLocationAndGrabEnd.second);

        UPrimitiveComponent *HitObject = PlayerHit.GetComponent();
        if(PlayerHit.GetActor())
        {
            PhysicsHandle->GrabComponentAtLocation(HitObject, NAME_None, PlayerLocationAndGrabEnd.second);
            IsGrabbed = true;

            FString ActorName = HitObject->GetName();
            UE_LOG(LogTemp, Warning, TEXT("Actor hit is: %s"), *ActorName);
        }
    }

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    GrabInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

    if(GrabInputComponent)
    {
        GrabInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabOrRelease);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GrabInputComponent was not found."));
    }
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetPlayerGrabStartAndEndPoints().second);
    }
}

