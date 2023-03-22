
#include "EngineUtils.h"
#include "MovementGameManager.h"

AMovementGameManager::AMovementGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	Zipwires.SetNum(12);
}

void AMovementGameManager::BeginPlay()
{
	Super::BeginPlay();
}

void AMovementGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMovementGameManager::CheckConnection(FVector position)
{
	FVector tempPos = Zipwires[0]->GetClosestPoint(position);
	FVector tempDis = tempPos - position;
	float tempMag = tempDis.Size();
	return (tempMag <= disThreshold);
}
void AMovementGameManager::PrintNumberZipwires()
{
	/*for each (AZipwireSpline* wire in Zipwires)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" x: %f"), wire->GetDistanceTo(this)));
	}*/
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" x: %f"), Zipwires.Num()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetDebugName(Zipwires[0]));
}
FVector AMovementGameManager::GetZiplineHead()
{
	return Zipwires[0]->GetActorLocation();
}
FVector AMovementGameManager::GetZiplineDirection()
{
	return Zipwires[0]->GetPositionAtProgression(1) - Zipwires[0]->GetPositionAtProgression(0);
}
FVector AMovementGameManager::GetZiplineTangent(float progression)
{
	return Zipwires[0]->GetTangentAtProgression(progression);
}
FVector AMovementGameManager::GetClosePoint(FVector position)
{
	return (Zipwires[0]->GetClosestPoint(position));
}


