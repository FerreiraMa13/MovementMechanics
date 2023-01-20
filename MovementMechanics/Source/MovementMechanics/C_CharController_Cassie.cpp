// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CharController_Cassie.h"

// Sets default values
AC_CharController_Cassie::AC_CharController_Cassie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
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

    PlayerInputComponent->BindAxis(TEXT("Look Horizontal"),this,&AFirstPersonPlayerCharacter::LookHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Look Vertical"),this,&AFirstPersonPlayerCharacter::LookVertical);
	PlayerInputComponent->BindAxis(TEXT("Movement Forward"),this,&AFirstPersonPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Movement Sideway"),this,&AFirstPersonPlayerCharacter::MoveSideway);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacter::Jump);

void AC_CharController_Cassie::LookHorizontal(float axis_value)
{
	this->AddControllerYawInput(axis_value);
}
void AC_CharController_Cassie::LookVertical(float axis_value)
{
	this->AddControllerPitchInput(axis_value);
}
void AC_CharController_Cassie::MoveSideway(float axis_value)
{
	this->AddMovementInput(this->GetActorForwardVector() * axis_value)
}
void AC_CharController_Cassie::MoveForward(float axis_value)
{
	if (axis_value > 0)
	{
		(this->GetActorRightVector() * axis_value * character_speed);
	}
	this->AddMovementInput();
}

