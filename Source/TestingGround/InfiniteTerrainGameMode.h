// Copyright NickyKendy

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


class UActorPool;
/**
 * inifinite generate terrain game mode
 */
UCLASS()
class TESTINGGROUND_API AInfiniteTerrainGameMode : public ATestingGroundGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bounds Pool")
	UActorPool* NavMeshBoundsVolumePool;

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
