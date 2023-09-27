// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemyCharacter.generated.h"

class UHealthComponent;
class UBehaviorTree;
class AProjectile;

UCLASS()
class TEST_9_19_API AMyEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

		AMyEnemyCharacter(const FObjectInitializer& ObjInit);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AProjectile> ProjectileClass;



	virtual void BeginPlay() override;
	void OnDeath();
	void OnHealthChanged(float Health, float HealthDelta);

	UFUNCTION(BlueprintCallable)
		void Fire();
};
