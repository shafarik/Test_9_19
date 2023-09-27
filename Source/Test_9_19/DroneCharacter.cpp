// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"
#include "HealthComponent.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComponent");
	ShootComponent=CreateDefaultSubobject<USceneComponent>("ShootComponent");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComopnent");
}

// Called when the game starts or when spawned
void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ADroneCharacter::OnDeath);
	HealthComponent->OnHealthChenged.AddUObject(this, &ADroneCharacter::OnHealthChanged);

}
void ADroneCharacter::OnDeath()
{
	SetLifeSpan(3.0f);
	UE_LOG(LogTemp, Display, TEXT("Player is dead"));
}

void ADroneCharacter::DecreaseAmmo()
{
	if(Bullets==0)return;
	Bullets--;
	UE_LOG(LogTemp, Display, TEXT("Amount of bullets: %i"),Bullets);
}

void ADroneCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	 UE_LOG(LogTemp, Display, TEXT("Health Was Changed"));
}

void ADroneCharacter::MoveForward(float Amount)
{
	if (Amount == 0)
		return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ADroneCharacter::MoveRight(float Amount)
{
	if (Amount == 0)
		return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ADroneCharacter::MoveUp(float Amount)
{
	if (Amount != 0.f)
	{
		AddMovementInput(FVector::UpVector, Amount);
	}
}

void ADroneCharacter::Fire()
{
	if(!GetWorld())return;
	if(Bullets<=0)return;
	FVector Direction = GetActorForwardVector();
	FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation() + (GetActorForwardVector() * 100));

	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	DecreaseAmmo();
}

// Called every frame
void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADroneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADroneCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADroneCharacter::MoveUp);
	PlayerInputComponent->BindAxis("LookUp", this, &ADroneCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ADroneCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &ADroneCharacter::Fire);
}

