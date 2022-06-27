// Fill out your copyright notice in the Description page of Project Settings.


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
	
	CastSphere(GetActorLocation() + FVector(0, 0, 0), 300.0);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return;

	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	int NumToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	
	for (size_t i = 0; i < NumToSpawn; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* Spawned = World->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	UWorld* const World = GetWorld();
	if (!ensure(World)) return false;

	FHitResult OutHit;
	bool HasHit = World->SweepSingleByChannel(
		OutHit,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(
		World, 
		Location, 
		Radius, 
		Radius, 
		FQuat::Identity, 
		ResultColor, 
		true, 
		-1.f, 
		0U, 
		5.f
	);

	return HasHit;
}