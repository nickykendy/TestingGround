// Copyright NickyKendy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"
#include "Tile.generated.h"


class UActorPool;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

USTRUCT(BlueprintType)
struct FSpawnParam
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Prop")
	int MinSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Prop")
	int MaxSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Prop")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Prop")
	float MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Prop")
	float MaxScale;

	FSpawnParam()
	{
		MinSpawn = 1;
		MaxSpawn = 1;
		Radius = 500.f;
		MinScale = 1.f;
		MaxScale = 1.f;
	}
};

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Tile")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Tile")
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Tile")
	FVector NavOffset;

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLoc, float Radius);

	void PlaceActorAtLocation(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActorAtLocation(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceNavMesh();

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnParam SpawnParam);

public:
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnParam SpawnParam);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnParam SpawnParam);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* PoolToSet);
};
