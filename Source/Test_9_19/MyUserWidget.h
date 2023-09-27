// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_9_19_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
		public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPersent();
};
