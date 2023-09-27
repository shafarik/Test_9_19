// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIPerceptionComponent.h"
#include "EnemyController.h"
#include "DroneCharacter.h"
#include "MyEnemyCharacter.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* UMyAIPerceptionComponent::GetPlayerCharacter()
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0)
            return nullptr;
    }

    const auto Controller = Cast<AEnemyController>(GetOwner());
    if (!Controller)
        return nullptr;
    //  const auto aicharacter=  Controller->GetOwner();
    // aicharacter->GetActorLocation();
    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    AActor* Character = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto PlayerActor = Cast<ADroneCharacter>(PercieveActor);
        if (!PlayerActor)
        {
            continue;
        }
        else

        {
            Character = PlayerActor;
        }
    }
    return Character;
}
FVector UMyAIPerceptionComponent::GetPlayerLocation()
{
    if (!GetPlayerCharacter())
    {
        //   UE_LOG(LogTemp, Display, TEXT("PlayerCharacter is not valid"));
        return FVector::ZeroVector;
    }
    return GetPlayerCharacter()->GetActorLocation();
}

