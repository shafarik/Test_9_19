// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(10.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SphereComponent->bReturnMaterialOnMove = true;
    SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	StaticMesh->AttachToComponent(SphereComponent, Rules);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 200.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    AActor* MyOwner=GetOwner();
    SphereComponent->IgnoreActorWhenMoving(MyOwner, true);
    SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld())
        return;

    MovementComponent->StopMovementImmediately();

    // make damage
    //FPointDamageEvent PointDamageEvent;
    //PointDamageEvent.HitInfo=Hit;
    //Hit.Actor->TakeDamage(DamageAmount, PointDamageEvent,GetController(),this);
    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, NormalImpulse, Hit, GetController(), this, UDamageType::StaticClass());
    Destroy();
}

AController* AProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

