
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
	currentWire = GetClosestWire(position);
	FVector tempPos = Zipwires[currentWire]->GetClosestPoint(position);
	FVector tempDis = tempPos - position;
	float tempMag = tempDis.Size();
	return (tempMag <= disThreshold);
}
int AMovementGameManager::GetClosestWire(FVector position)
{
	int closest_index = 0;
	float closest_distance = 999999999;
	FVector current_point;
	FVector distance_vector;
	int independent_index = 0;
	for (int index = 0; index < Zipwires.Num(); index++)
	{
		if (Zipwires[index])
		{
			current_point = Zipwires[index]->GetClosestPoint(position);
			distance_vector = current_point - position;
			if (distance_vector.Size() < closest_distance)
			{
				closest_index = independent_index;
				closest_distance = distance_vector.Size();
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %i: %f"), independent_index, closest_distance));
			independent_index++;
		}
	}
	
	return closest_index;
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
	return Zipwires[currentWire]->GetActorLocation();
}
FVector AMovementGameManager::GetZiplineDirection()
{
	return Zipwires[currentWire]->GetPositionAtProgression(1) - Zipwires[currentWire]->GetPositionAtProgression(0);
}
FVector AMovementGameManager::GetZiplineTangent(float progression)
{
	return Zipwires[currentWire]->GetTangentAtProgression(progression);
}
FVector AMovementGameManager::GetClosePoint(FVector position)
{
	return (Zipwires[currentWire]->GetClosestPoint(position));
}
bool AMovementGameManager::CheckEndConnections(FVector position)
{
	FVector ClosestPoint = Zipwires[currentWire]->GetClosestPoint(position);
	FVector StartPoint = Zipwires[currentWire]->GetPositionAtProgression(0);
	FVector EndPoint = Zipwires[currentWire]->GetPositionAtProgression(1);
	if ((ClosestPoint - StartPoint).Size() < 100 || (ClosestPoint-EndPoint).Size() < 100)
	{
		return true;
	}
	return false;
}


