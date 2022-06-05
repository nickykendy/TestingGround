// Copyrights NickyKendy

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Patrols")
		TArray<AActor*> PatrolPoints;

public:
	TArray<AActor*> GetPatrolPoints() const;
};
