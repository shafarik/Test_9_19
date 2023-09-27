// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHealthPickupActor.h"
#include "DroneCharacter.h"
#include "HealthComponent.h"

bool AMyHealthPickupActor::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogTemp, Display, TEXT("Health restored"));
    const auto Player = Cast<ADroneCharacter>(PlayerPawn);
    if (!Player)
        return false;
    const auto Component = PlayerPawn->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)
        return false;

    HealthComponent->PickupHeal(HealAmount);
    return true;
}
