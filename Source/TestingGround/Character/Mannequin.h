// Copyright NickyKendy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class AGun;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class TESTINGGROUND_API AMannequin : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Child Actor Gun Ref */
	AGun* Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPCamera;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPMesh;

public:
	// Sets default values for this character's properties
	AMannequin();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when unpossessed
	virtual void UnPossessed() override;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector GunOffset;

	/** The Gun Class ready to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AGun> GunClass;

	/** Fire method */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PullTrigger();
};
