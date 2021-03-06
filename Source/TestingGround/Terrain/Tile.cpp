// Copyright NickyKendy

#include "../Terrain/Tile.h"
#include "DrawDebugHelpers.h"
#include "../ActorPool.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
	NavOffset = FVector(4000, 0, 0);
}

void ATile::SetPool(UActorPool* PoolToSet)
{
	Pool = PoolToSet;
	PlaceNavMesh();
}

void ATile::PlaceNavMesh()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!ensure(NavMeshBoundsVolume)) return;

	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() - NavOffset);
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	NavSys->Build();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!ensure(Pool)) return;
	if (!ensure(NavMeshBoundsVolume)) return;

	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnParam SpawnParam)
{
	int NumToSpawn = FMath::RandRange(SpawnParam.MinSpawn, SpawnParam.MaxSpawn);
	for (size_t i = 0; i < NumToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::FRandRange(SpawnParam.MinScale, SpawnParam.MaxScale);
		bool HasFound = FindEmptyLocation(SpawnPosition.Location, SpawnParam.Radius * SpawnPosition.Scale);
		if (HasFound)
		{
			SpawnPosition.Rotation = FMath::FRandRange(-180.f, 180.f);
			PlaceActorAtLocation(ToSpawn, SpawnPosition);
		}
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnParam SpawnParam)
{
	RandomlyPlaceActors(ToSpawn, SpawnParam);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnParam SpawnParam)
{
	RandomlyPlaceActors(ToSpawn, SpawnParam);
}

void ATile::PlaceActorAtLocation(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return;

	AActor* Spawned = World->SpawnActor<AActor>(ToSpawn);
	if (!ensure(Spawned)) return;

	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceActorAtLocation(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return;

	FRotator Rotation = FRotator(0, SpawnPosition.Rotation, 0);
	APawn* Spawned = World->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location, Rotation);
	if (!ensure(Spawned)) return;

	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}

bool ATile::FindEmptyLocation(FVector& OutLoc, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);
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

