// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneCharacter.generated.h"

class UPawnMovementComponent;
class USphereComponent;
class USceneComponent;
class AProjectile;
class UHealthComponent;

UCLASS()
class TEST_9_19_API ADroneCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADroneCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets = 10;

	int32 GetAmmoData() const
	{
		return Bullets;
	}

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void MoveUp(float Amount);
	void Fire();
	void OnDeath();
	void DecreaseAmmo();
	void OnHealthChanged(float Health, float HealthDelta);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetAmmoData(int32 NewAmmoData)
	{
		Bullets += NewAmmoData;
	}

};
