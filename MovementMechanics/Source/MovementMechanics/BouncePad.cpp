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
			if (dash_launch)
			{

				if (launch_vector == FVector(0, 0, 0))
				{
					player->ForceJump();
				}
				else
				{
					FVector temp_multiplier = HandleInteractions();
					FVector temp_rotation = player->GetRotation();
					temp_rotation.Normalize();
					launch_vector.X = temp_rotation.X;
					launch_vector.Y = temp_rotation.Y;
					player->ForceJump(launch_vector * temp_multiplier, 200, 70);
				}
			}
		}
}
FVector ABouncePad::HandleInteractions()
{
	switch (player->currentState)
	{
	case SLIDING:
		return FVector(1, 1, 2);
		break;
	default:
		return FVector(1, 1, 1);
		break;
	}
}

