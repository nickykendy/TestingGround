// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool CastSphere(FVector Location, float Radius);

public:
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** place some objects */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn);
};