// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "C_CharController_Cassie.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "BouncePad.generated.h"

UCLASS()
class MOVEMENTMECHANICS_API ABouncePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad();
	UPROPERTY(EditAnywhere, Category = "Launch");
		FVector launch_vector = FVector(0, 0, 0);
		UPROPERTY(EditAnywhere, Category = "Launch");
		float dash_launch_distance = 2000;
		UPROPERTY(EditAnywhere, Category = "Launch");
		float dash_launch_velocity = 100;
	UPROPERTY(EditAnywhere, Category = "Launch");
		bool dash_launch = true;
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "References")
		AC_CharController_Cassie* player = nullptr;
	void HandleInteractions();
	float launch_multiplier = 1.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
