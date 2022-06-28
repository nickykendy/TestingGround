// Copyright NickyKendy

#include "../Terrain/Tile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandScale = FMath::FRandRange(MinScale, MaxScale);
		bool HasFound = FindEmptyLocation(SpawnPoint, Radius * RandScale);
		if (HasFound)
		{
			float RandRot = FMath::FRandRange(-180.f, 180.f);
			PlaceActorAtLocation(ToSpawn, SpawnPoint, RandRot, RandScale);
		}
	}
}

bool ATile::FindEmptyLocation(FVector& OutLoc, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector Point = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(Point, Radius))
		{
			OutLoc = Point;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActorAtLocation(TSubclassOf<AActor> ToSpawn, FVector Point, float Rotation, float Scale)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return;

	AActor* Spawned = World->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(Point);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return false;

	FHitResult OutHit;
	FVector GlobalLoc = ActorToWorld().TransformPosition(Location);
	bool HasHit = World->SweepSingleByChannel(
		OutHit,
		GlobalLoc,
		GlobalLoc,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);

	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(
	//	World, 
	//	Location, 
	//	Radius, 
	//	Radius, 
	//	FQuat::Identity, 
	//	ResultColor, 
	//	true, 
	//	-1.f, 
	//	0U, 
	//	5.f
	//);

	return !HasHit;
}