
#include "EngineUtils.h"
#include "MovementGameManager.h"

AMovementGameManager::AMovementGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	for (TActorIterator<AZipwireSpline> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Zipwires.Add(*ActorItr);
	}
}

void AMovementGameManager::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMovementGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMovementGameManager::CheckConnection()
{
	return true;
}
void AMovementGameManager::PrintNumberZipwires()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" x: %f"), Zipwires.Num()));
}


