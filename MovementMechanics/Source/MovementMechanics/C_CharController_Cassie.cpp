// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CharController_Cassie.h"

// Sets default values
AC_CharController_Cassie::AC_CharController_Cassie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 40));
}

// Called when the game starts or when spawned
void AC_CharController_Cassie::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_CharController_Cassie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_CharController_Cassie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Look Horizontal"), this, &AC_CharController_Cassie::LookHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Look Vertical"), this, &AC_CharController_Cassie::LookVertical);
	PlayerInputComponent->BindAxis(TEXT("Movement Forward"), this, &AC_CharController_Cassie::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Movement Sideway"), this, &AC_CharController_Cassie::MoveSideway);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
}
void AC_CharController_Cassie::LookHorizontal(float axis_value)
{
	if (axis_value)
	{
		this->AddActorLocalRotation(FRotator(0.0f, axis_value * rotation_multiplier_x , 0.0f));
	}
}
void AC_CharController_Cassie::LookVertical(float axis_value)
{
	if (axis_value)
	{
		float temp_rot = Camera->GetRelativeRotation().Pitch + axis_value * rotation_multiplier_y;
		if (temp_rot < 65 && temp_rot > -45)
		{
			Camera->AddLocalRotation(FRotator(axis_value * rotation_multiplier_y, 0, 0));
			//this->AddControllerPitchInput(axis_value * rotation_multiplier);
		}
		
	}
	
}
void AC_CharController_Cassie::MoveSideway(float axis_value)
{
	if (axis_value)
	{
		FVector movementVec = this->GetActorRightVector() * axis_value * character_speed * strafe_multiplier;
		this->AddMovementInput(movementVec);
	}
}
void AC_CharController_Cassie::MoveForward(float axis_value)
{
	if (axis_value)
	{
		FVector movementVec = this->GetActorForwardVector() * axis_value * character_speed;
		if (axis_value < 0)
		{
			movementVec *= back_multiplier;
		}
		this->AddMovementInput(movementVec);
	}
}

