// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyCharacter.h"
#include "EnemyController.h"
#include "MyAIPerceptionComponent.h"
#include "BrainComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DroneCharacter.h"
#include "Projectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"

// Sets default values
AMyEnemyCharacter::AMyEnemyCharacter(const FObjectInitializer& ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyController::StaticClass();
    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComopnent");
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void AMyEnemyCharacter::Fire()
{
    if (!GetWorld())return;
    const auto MyController = Cast<AEnemyController>(Controller);
    if(!MyController)return;
    
    FVector Direction = (MyController->GetPlayerLocation() - (GetActorLocation() + (GetActorForwardVector() * 100))).GetSafeNormal();
    FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation()+(GetActorForwardVector()*100));

    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}

// Called when the game starts or when spawned
void AMyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AMyEnemyCharacter::OnDeath);
    HealthComponent->OnHealthChenged.AddUObject(this, &AMyEnemyCharacter::OnHealthChanged);
}

void AMyEnemyCharacter::OnDeath()
{
    const auto MyController = Cast<AEnemyController>(Controller);
    if (MyController && MyController->BrainComponent)
    {
        MyController->BrainComponent->Cleanup();
    }
    SetLifeSpan(0.1f);
}

void AMyEnemyCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    UE_LOG(LogTemp, Display, TEXT("Health Was Changed"));
}

