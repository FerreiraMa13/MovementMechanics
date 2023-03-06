// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Dash.h"
#include "C_CharController_Cassie.generated.h"

UENUM()
enum PlayerAbilityStates
{
	DEFAULT = 0,
	DASHING = 1,
	SLIDING = 2,
	PAD = 3,
};

UENUM()
enum CustomMovement
{
	NONE = 0,
	DASH = 1,
	SLIDE = 2,
	JUMPAD = 3,
};

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
	bool input_active = true;
	float timer = 0.0f;
	float slide_timer = 0.0f;
	float jumpad_velocity = 60.0f;
	float jumpad_distance = 120.0f;
	
	UPROPERTY(EditAnywhere, Category = "Dash Details")
		TEnumAsByte<PlayerAbilityStates> currentState = DEFAULT;
	UPROPERTY(EditAnywhere, Category = "Movement States")
		TEnumAsByte<CustomMovement> currentMovement = NONE;
	UPROPERTY(EditAnywhere, Category = "Dash Details")
		FVector startPoint;
	UPROPERTY()
		UCharacterMovementComponent* char_move;
	FVector travelDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LookHorizontal(float axis_value);
	void LookVertical(float axis_value);
	void MoveSideway(float axis_value);
	void MoveForward(float axis_value);
	void JumpCheck();
	void ActivateDash();
	void ActivateSlide();
	void HandleDash(float delta);
	void HandleSlide(float delta);
	void HandleJumpad(float delta);
	void HandleTimers(float delta);

	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Components")
		UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* CollidingPoint;
	UPROPERTY(EditAnywhere, Category = "General")
		float PASSIVE_MULTIPLIER = 1000;

	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float dash_distance = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float dash_velocity = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float proximity_treshold = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Dash Details")
		float max_timer = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Slide Details")
		float max_slide_timer = 3.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ForceJump();
	void ForceJump(FVector direction, float distance, float speed);
	FVector GetRotation();
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
