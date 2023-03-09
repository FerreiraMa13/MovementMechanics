#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "ZipwireSpline.generated.h"


UCLASS()
class MOVEMENTMECHANICS_API AZipwireSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZipwireSpline();
	void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Spline Details")
		USplineComponent* WireSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Details")
		UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Details")
		TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;
};
