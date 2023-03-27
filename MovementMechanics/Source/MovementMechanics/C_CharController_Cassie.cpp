// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CharController_Cassie.h"

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
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AC_CharController_Cassie::OnBeginOverlap);
	

	SlideCollision = FindComponentByClass<UBoxComponent>();
	/*SlideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/

	char_move = GetCharacterMovement();
	char_move->GravityScale = grav_current;
}
void AC_CharController_Cassie::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_CharController_Cassie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleTimers(DeltaTime);
	switch (currentState)
	{
	case DEFAULT:
		break;
	case DASHING:
		HandleDashForce(DeltaTime);
		break;
	case SLIDING:
		HandleSlideForce(DeltaTime);
		break;
	case PAD:
		HandleJumpad(DeltaTime);
		break;
	case ZIPLINING:
		HandleZipline(DeltaTime);
		break;
	default:
		break;
	}
}
void AC_CharController_Cassie::HandleTimers(float delta)
{
	if (dash_timer > 0)
	{
		dash_timer -= delta;
	}
	if (slide_timer > 0)
	{
		slide_timer -= delta;
	}
	if (grav_current != grav_start && char_move->IsMovingOnGround())
	{
		grav_current = grav_start;
		char_move->GravityScale = grav_current;
	}
}
void AC_CharController_Cassie::HandleDashForce(float delta)
{
	if (dash_timer <= 0 || char_move->IsMovingOnGround())
	{
		ResetState();
		ForceGrav();
	}
}
void AC_CharController_Cassie::HandleSlideForce(float delta)
{
	if (slide_timer <= 0)
	{
		ResetState();
		/*currentState = DEFAULT;
		input_active = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);*/
	}
}
void AC_CharController_Cassie::HandleJumpad(float delta)
{
	if (char_move->IsMovingOnGround())
	{
		ResetState();
		ForceGrav();
	}
}
void AC_CharController_Cassie::HandleZipline(float delta)
{
	if (attatched)
	{
		
		float tempMulti = 0;
		if (zipling_input.Y > 0)
		{
			tempMulti = 1;
		}
		else if (zipling_input.Y < 0)
		{
			tempMulti = -1;
		}
		if (CalculateAngleBetween(zipling_direction, Camera->GetForwardVector()) > 1.8f)
		{
			tempMulti *= -1;
		}
		char_move->AddForce(zipling_direction.GetSafeNormal() * PASSIVE_MULTIPLIER * tempMulti);
		if (game_manager->CheckEndConnections(this->GetActorLocation()))
		{
			ResetState();
		}
	}
}


void AC_CharController_Cassie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Look Horizontal"), this, &AC_CharController_Cassie::LookHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Look Vertical"), this, &AC_CharController_Cassie::LookVertical);
	PlayerInputComponent->BindAxis(TEXT("Movement Forward"), this, &AC_CharController_Cassie::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Movement Sideway"), this, &AC_CharController_Cassie::MoveSideway);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AC_CharController_Cassie::ActivateJump);
	PlayerInputComponent->BindAction(TEXT("Ability1"), IE_Pressed, this, &AC_CharController_Cassie::ActivateDash);
	PlayerInputComponent->BindAction(TEXT("Ability2"), IE_Pressed, this, &AC_CharController_Cassie::ActivateEngage);
	PlayerInputComponent->BindAction(TEXT("Slide"), IE_Pressed, this, &AC_CharController_Cassie::ActivateSlide);
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
		if (currentState != ZIPLINING)
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
		else
		{
			zipling_input.Y = axis_value;
		}
	}
}


void AC_CharController_Cassie::ResetState()
{
	currentState = DEFAULT;
	currentMovement = NONE;
	char_move->SetMovementMode(MOVE_Falling);
	input_active = true;
	Camera->SetRelativeLocation(FVector(0, 0, 40));
	this->GetMesh()->SetVisibility(true);
	/*Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);*/
}
void AC_CharController_Cassie::ForceGrav()
{
	grav_current = grav_max;
	char_move->GravityScale = grav_current;
}
void AC_CharController_Cassie::ActivateDash()
{
	if ( dash_timer <= 0)
	{
		/*GetCharacterMovement()->SetMovementMode(MOVE_Custom);
		currentMovement = DASH;
		auto location = GetActorLocation();
		startPoint = location;
		travelDirection = Camera->GetForwardVector();
		input_active = false;
		timer = max_timer;
		currentState = DASHING;*/

		char_move->SetMovementMode(MOVE_Flying);
		currentMovement = DASH;
		currentState = DASHING;
		startPoint = GetActorLocation();
		travelDirection = Camera->GetForwardVector();
		input_active = false;
		dash_timer = max_dash_timer;
		char_move->AddForce(travelDirection * dash_velocity * PASSIVE_MULTIPLIER);
		
		/*char_move->AddForce(travelDirection * dash_velocity * PASSIVE_MULTIPLIER);*/
	}
}
void AC_CharController_Cassie::ActivateSlide()
{
	if (input_active &&  slide_timer <= 0 &&  char_move->IsMovingOnGround())
	{
		DebugLog();
		char_move->SetMovementMode(MOVE_Flying);
		currentMovement = SLIDE;
		currentState = SLIDING;
		travelDirection = Camera->GetForwardVector();
		travelDirection.Z = 0;
		slide_timer = max_slide_timer;
		char_move->AddForce(travelDirection * slide_speed * PASSIVE_MULTIPLIER);
		Camera->SetRelativeLocation(FVector(0, 0, 0));
		this->GetMesh()->SetVisibility(false);
		/*Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
	}
	else if(input_active && slide_timer > 0)
	{
		ResetState();
		Jump();
	}
}
void AC_CharController_Cassie::ActivateJump()
{
	switch (currentState)
	{
	case(DASHING):
		break;
	case(SLIDING):
		
		ResetState();
		/*char_move->AddForce(FVector(0, 0, 10) * slide_speed * 1 / 2 * PASSIVE_MULTIPLIER);
		char_move->AddForce(Camera->GetForwardVector()* FVector(5,5,0) * -1 * 1 / 2 * slide_speed * PASSIVE_MULTIPLIER);*/
		Jump();
		break;
	case(ZIPLINING):
		ResetState();
		Jump();
		break;
	case (DEFAULT):
		Jump();
		break;
	}
}
void AC_CharController_Cassie::ActivateEngage()
{
	if (game_manager != nullptr)
	{
		if (!attatched)
		{
			FVector tempPos = this->GetActorLocation();
			if (game_manager->CheckConnection(tempPos))
			{
				char_move->SetMovementMode(MOVE_Flying);
				currentState = ZIPLINING;
				/*input_active = false;*/
				attatched = true;
				FVector tempRepo = game_manager->GetClosePoint(tempPos);
				tempRepo.Z += 120;
				this->SetActorLocation(tempRepo);
				FVector tempDirect = game_manager->GetZiplineDirection();
				zipling_direction = tempDirect;
				char_move->ClearAccumulatedForces();
				float tempMag = char_move->Velocity.Size();
				char_move->Velocity = tempDirect.GetSafeNormal() * tempMag;
			}
		}
		else
		{
			ResetState();
			attatched = false;
		}
	}
}


void AC_CharController_Cassie::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit!"));
}
void AC_CharController_Cassie::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit!"));
}
void AC_CharController_Cassie::ForceJump()
{
	Jump();
}
void AC_CharController_Cassie::ForceJump(FVector direction, float speed)
{
	/*GetCharacterMovement()->SetMovementMode(MOVE_Custom);
	
	currentMovement = JUMPAD;
	auto location = GetActorLocation();
	startPoint = location;
	input_active = false;
	travelDirection = direction;
	currentState = PAD;
	jumpad_distance = distance;
	jumpad_velocity = speed;*/
	/*currentMovement = JUMPAD;
	currentState = PAD;*/
	ResetState();
	auto location = GetActorLocation();
	startPoint = location;
	currentMovement = JUMPAD;
	currentState = PAD;
	dash_timer = max_dash_timer;
	travelDirection = direction;
	jumpad_velocity = speed;
	char_move->AddForce(travelDirection *  jumpad_velocity * PASSIVE_MULTIPLIER);
}
FVector AC_CharController_Cassie::GetRotation()
{
	return Camera->GetForwardVector();
}

float AC_CharController_Cassie::CalculateAngleBetween(FVector vectorA, FVector vectorB)
{
	vectorA = vectorA.GetSafeNormal();
	vectorB = vectorB.GetSafeNormal();

	float dot_product = FVector::DotProduct(vectorA, vectorB);
	dot_product = acos(dot_product);

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" x: %f"), dot_product));*/

	return dot_product;
}
void AC_CharController_Cassie::DebugLog()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DebugMessage"));
}