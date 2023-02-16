// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Dash.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTMECHANICS_API UDash : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's
	UDash();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void PerformDash(FVector startingPoint, FVector direction);
	void PerformDash(FVector startingPoint, FVector direction, float magnitude);
	void PerformDash(FVector startingPoint, FVector direction, float magnitude, float velocity);
	bool CheckComplete( FVector current_pos);

	FVector endPoint;
	FVector travelDirection;
	bool dashing;
	float curr_dash_velocity = 50.f;

	UPROPERTY(EditAnywhere, Category = "Dash Details")
		ACharacter* owner;

	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float dash_distance;

	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float dash_velocity;

	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float proximity_treshold;
private:	
	
	
	
};
