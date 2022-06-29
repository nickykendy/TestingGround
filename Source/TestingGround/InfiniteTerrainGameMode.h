// Copyright NickyKendy

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


/**
 * inifinite generate terrain game mode
 */
UCLASS()
class TESTINGGROUND_API AInfiniteTerrainGameMode : public ATestingGroundGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);

};
