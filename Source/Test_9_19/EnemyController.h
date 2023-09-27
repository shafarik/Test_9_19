// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UMyAIPerceptionComponent;
UCLASS()
class TEST_9_19_API AEnemyController : public AAIController
{
	GENERATED_BODY()
		
	    public:
    AEnemyController();
        FVector GetPlayerLocation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UMyAIPerceptionComponent* MyAIPerceptionComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FokusOnKeyName = "PlayerActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor* GetFocusedActor()const;
};
