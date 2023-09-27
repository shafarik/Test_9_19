// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TEST_9_19_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:

    UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Weapon")
		USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Weapon")
		UProjectileMovementComponent* MovementComponent;

		    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float LifeSeconds = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void SetShotDirection(const FVector& Direction)
	{
		ShotDirection = Direction;
	}

private:
	FVector ShotDirection;
	AController* GetController() const;

	    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                         UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
