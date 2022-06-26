// Copyright NickyKendy

#include "../Character/Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	FPMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn Gun
	UWorld* const World = GetWorld();
	if (World != nullptr && FPMesh != nullptr && GunClass != nullptr) {
		const FVector SpawnLocation = FPMesh->GetSocketLocation(FName("GripPoint"));
		const FRotator SpawnRotation = FPMesh->GetSocketRotation(FName("GripPoint"));
		Gun = World->SpawnActor<AGun>(GunClass, SpawnLocation, SpawnRotation);
		Gun->SetAnimInstance(true, FPMesh->GetAnimInstance());
		Gun->SetAnimInstance(false, GetMesh()->GetAnimInstance());
		if (IsPlayerControlled())
		{
			Gun->AttachToComponent(FPMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
		}
		else
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
		}
	}

	if (InputComponent != nullptr) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	if (!ensure(Gun)) return;
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
}

// Fire a weapon
void AMannequin::PullTrigger()
{
	if (!ensure(Gun)) return;
	Gun->OnFire();
}