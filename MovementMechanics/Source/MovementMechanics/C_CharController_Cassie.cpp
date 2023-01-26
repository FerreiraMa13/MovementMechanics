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

	CollidingPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	CollidingPoint->AttachTo(GetRootComponent());
	CollidingPoint->SetRelativeLocation(FVector(100, 0, 0));
	CollidingPoint->OnComponentBeginOverlap.AddDynamic(this, &AC_CharController_Cassie::OnBeginOverlap);

	Capsule = FindComponentByClass<UCapsuleComponent>();
	Capsule->OnComponentHit.AddDynamic(this, &AC_CharController_Cassie::OnHit);
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
	if (timer > 0)
	{
		timer -= DeltaTime;
	}
	if (!input_active)
	{
		FVector current_location = GetActorLocation();
		switch (currentState)
		{
		case DEFAULT:
			break;
		case DASHING:
			SetActorLocation(current_location + travelDirection * dash_velocity * DeltaTime);
			if (abs(current_location.Distance(GetActorLocation(), startPoint)) > dash_distance || abs(current_location.Distance(current_location, GetActorLocation()) < 10.0f))
			{
				currentState = default;
				input_active = true;
				GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			}
			break;
		default:
			break;
		}
	}
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
	PlayerInputComponent->BindAction(TEXT("Ability1"), IE_Pressed, this, &AC_CharController_Cassie::ActivateDash);
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
	if (input_active)
	{
		if (axis_value)
		{
			FVector movementVec = this->GetActorRightVector() * axis_value * character_speed * strafe_multiplier;
			this->AddMovementInput(movementVec);
		}
	}
}
void AC_CharController_Cassie::MoveForward(float axis_value)
{
	if (input_active)
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
}
void AC_CharController_Cassie::ActivateDash()
{
	if (input_active && timer <= 0)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		auto location = GetActorLocation();
		startPoint = location;
		travelDirection = Camera->GetForwardVector();
		input_active = false;
		timer = max_timer;
		currentState = DASHING;
	}
}
void AC_CharController_Cassie::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit!"));
	if (DASHING)
	{
		currentState = default;
		input_active = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	}
}
void AC_CharController_Cassie::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit!"));
	if (DASHING)
	{
		currentState = default;
		input_active = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	}
}
void AC_CharController_Cassie::ForceJump()
{
	Jump();
}
void AC_CharController_Cassie::ForceJump(FVector direction)
{
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	auto location = GetActorLocation();
	startPoint = location;
	travelDirection = direction;
	input_active = false;
	timer = max_timer;
	currentState = DASHING;
}