// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "C_CharController_Cassie.generated.h"


UCLASS()
class MOVEMENTMECHANICS_API AC_CharController_Cassie : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AC_CharController_Cassie();

	float character_speed = 1.0f;
	float strafe_multiplier = 0.8f;
	float back_multiplier = 0.6f;
	float rotation_multiplier_x = 2.0f;
	float rotation_multiplier_y = 1.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LookHorizontal(float axis_value);
	void LookVertical(float axis_value);
	void MoveSideway(float axis_value);
	void MoveForward(float axis_value);

	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
