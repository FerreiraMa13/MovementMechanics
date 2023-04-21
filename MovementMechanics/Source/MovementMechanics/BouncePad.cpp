// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->AttachTo(GetRootComponent());
	BoxComponent->SetRelativeLocation(FVector(0, 0, 50));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABouncePad::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bounce!"));
		if (player != nullptr)
		{
				if (launch_vector == FVector(0, 0, 0))
				{
					player->ForceJump();
				}
				else
				{
					if (dash_launch)
					{
					HandleInteractions();
					}
					FVector temp_rotation = player->GetRotation();
					temp_rotation.Normalize();
					
					FVector tempUp = FVector(0, 0, 0);
					if (launch_vector.X != 0)
					{
						tempUp += GetActorForwardVector() * launch_vector.X;
					}
					if (launch_vector.Y != 0)
					{
						tempUp += GetActorRightVector() * launch_vector.Y;
					}
					if (launch_vector.Z != 0)
					{
						tempUp += GetActorUpVector() * launch_vector.Z;
					}
					player->ForceJump(tempUp * launch_multiplier, dash_launch_velocity );
				}
			
		}
}
void ABouncePad::HandleInteractions()
{
	switch (player->currentState)
	{
	case SLIDING:
		launch_multiplier = 1.2f;
		break;
	default:
		launch_multiplier = 1.0f;
		break;
	}
}

