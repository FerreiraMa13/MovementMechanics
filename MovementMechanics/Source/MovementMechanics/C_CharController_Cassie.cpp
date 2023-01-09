// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CharController_Cassie.h"

// Sets default values
AC_CharController_Cassie::AC_CharController_Cassie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

