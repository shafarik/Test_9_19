// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "HealthComponent.h"

float UMyUserWidget::GetHealthPersent()
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)return 0.0f;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)return 0.0f;

    return HealthComponent->GetHealthPrecent();
}
