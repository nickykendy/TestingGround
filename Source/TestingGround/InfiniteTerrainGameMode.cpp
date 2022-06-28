// Copyright NickyKendy

#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<AActor>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(AActor* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found: %s"), *VolumeToAdd->GetName());
}