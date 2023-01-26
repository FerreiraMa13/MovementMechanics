// Fill out your copyright notice in the Description page of Project Settings.
#include "Dash.h"

// Sets default values for this component's properties
UDash::UDash()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDash::BeginPlay()
{
	Super::BeginPlay();
	//owner = Cast<AActor>(GetOwner());
}


// Called every frame
void UDash::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (dashing)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error Message: Dash"));
		FVector current_location = owner->GetActorLocation();
		float distance = endPoint.Distance(current_location, endPoint);
		if (distance > proximity_treshold)
		{
			
			if (owner != nullptr)
			{
				
				owner->SetActorLocation(current_location + travelDirection * dash_velocity * DeltaTime);
			}
			
		}
		else
		{
			dashing = false;
		}
	}
}
void UDash::PerformDash(FVector startingPoint, FVector direction)
{
	endPoint = startingPoint + direction * dash_distance;
	travelDirection = direction;
	dashing = true;
}

bool UDash::CheckComplete(FVector current_pos)
{
	float distance = endPoint.Distance(current_pos, endPoint);
	return distance <= proximity_treshold;
}
