


#include "ZipwireSpline.h"

// Sets default values
AZipwireSpline::AZipwireSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WireSpline = CreateDefaultSubobject<USplineComponent>("Wire Spline");
	if (WireSpline)
	{
		SetRootComponent(WireSpline);
	}
}
void AZipwireSpline::OnConstruction(const FTransform& Transform)
{
	if (Mesh)
	{
		for (int splinePoint = 0; splinePoint < (WireSpline->GetNumberOfSplinePoints() - 1); splinePoint++)
		{
			USplineMeshComponent* tempSplineMeshComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

			tempSplineMeshComp->SetStaticMesh(Mesh);
			tempSplineMeshComp->SetMobility(EComponentMobility::Movable);
			tempSplineMeshComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			tempSplineMeshComp->RegisterComponentWithWorld(GetWorld());
			tempSplineMeshComp->AttachToComponent(WireSpline, FAttachmentTransformRules::KeepRelativeTransform);

			const FVector tempMeshStartingPoint = WireSpline->GetLocationAtSplinePoint(splinePoint, ESplineCoordinateSpace::Local);
			const FVector tempMeshStartTangent = WireSpline->GetTangentAtSplinePoint(splinePoint, ESplineCoordinateSpace::Local);
			const FVector tempMeshEndingPoint = WireSpline->GetLocationAtSplinePoint(splinePoint + 1, ESplineCoordinateSpace::Local);
			const FVector tempMeshEndTangent = WireSpline->GetTangentAtSplinePoint(splinePoint + 1, ESplineCoordinateSpace::Local);

			tempSplineMeshComp->SetStartAndEnd(tempMeshStartingPoint, tempMeshStartTangent, tempMeshEndingPoint, tempMeshEndTangent, true);
			tempSplineMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			if (ForwardAxis)
			{
				tempSplineMeshComp->SetForwardAxis(ForwardAxis);
			}
		}
	}
}
// Called when the game starts or when spawned
void AZipwireSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZipwireSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

