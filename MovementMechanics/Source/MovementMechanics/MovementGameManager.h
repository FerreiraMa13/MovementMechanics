#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZipwireSpline.h"
#include "MovementGameManager.generated.h"

UCLASS()
class MOVEMENTMECHANICS_API AMovementGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovementGameManager();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Zipline Details")
		TArray<AZipwireSpline*> Zipwires;
public:	
	virtual void Tick(float DeltaTime) override;
	bool CheckConnection();
	void PrintNumberZipwires();
	FVector GetZiplineHead();
	FVector GetZiplineDirection();
};
