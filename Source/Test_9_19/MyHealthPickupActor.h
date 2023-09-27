// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickupActor.h"
#include "MyHealthPickupActor.generated.h"

/**
 * 
 */
UCLASS()
class TEST_9_19_API AMyHealthPickupActor : public ABasePickupActor
{
	GENERATED_BODY()
	private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;

public:
	    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		int32 HealAmount=50.0f;
};
