
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
	MeshConstruction();
}
void AZipwireSpline::MeshConstruction()
{
	if (Mesh)
	{
		for (int splinePoint = 0; splinePoint < (WireSpline->GetNumberOfSplinePoints() - 1); splinePoint++)
		{
			USplineMeshComponent* tempSplineMeshComp = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			//UBoxComponent* tempBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));

			tempSplineMeshComp->SetStaticMesh(Mesh);
			tempSplineMeshComp->SetMobility(EComponentMobility::Movable);
			tempSplineMeshComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			tempSplineMeshComp->RegisterComponentWithWorld(GetWorld());
			tempSplineMeshComp->AttachToComponent(WireSpline, FAttachmentTransformRules::KeepRelativeTransform);
			/*tempBoxComp->AttachToComponent(WireSpline, FAttachmentTransformRules::KeepRelativeTransform);*/

			const FVector tempMeshStartingPoint = WireSpline->GetLocationAtSplinePoint(splinePoint, ESplineCoordinateSpace::Local);
			const FVector tempMeshStartTangent = WireSpline->GetTangentAtSplinePoint(splinePoint, ESplineCoordinateSpace::Local);
			const FVector tempMeshEndingPoint = WireSpline->GetLocationAtSplinePoint(splinePoint + 1, ESplineCoordinateSpace::Local);
			const FVector tempMeshEndTangent = WireSpline->GetTangentAtSplinePoint(splinePoint + 1, ESplineCoordinateSpace::Local);

			tempSplineMeshComp->SetStartAndEnd(tempMeshStartingPoint, tempMeshStartTangent, tempMeshEndingPoint, tempMeshEndTangent, true);
			/*tempBoxComp->SetBoxExtent(tempMeshEndingPoint - tempMeshStartingPoint);*/
			/*tempBoxComp->SetCollisionProfileName("Trigger");*/
			tempSplineMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			if (ForwardAxis)
			{
				tempSplineMeshComp->SetForwardAxis(ForwardAxis);
			}

			/*tempBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AZipwireSpline::OnBeginOverlap);*/
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
FVector AZipwireSpline::GetPositionAtProgression(float progression)
{
	return WireSpline->GetLocationAtTime(progression, ESplineCoordinateSpace::World);
}
void AZipwireSpline::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player != nullptr)
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			player->DebugLog();
		}
	}
}

