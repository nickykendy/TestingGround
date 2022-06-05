// Copyrights NickyKendy


#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRouteComponent>();

	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolRouteComp->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: PatrolPoints are missing!"), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	//UE_LOG(LogTemp, Warning, TEXT("waypoint index: %i"), Index);

	return EBTNodeResult::Succeeded;
}