// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAmmoPickupActor.h"
#include "DroneCharacter.h"

bool AMyAmmoPickupActor::GivePickupTo(APawn* PlayerPawn)
{
    ADroneCharacter* Player = Cast<ADroneCharacter>(PlayerPawn);
    if (!Player)return false;
    Player->SetAmmoData(AmmoAmount);
    return true;
}
