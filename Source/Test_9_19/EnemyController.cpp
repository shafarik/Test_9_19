// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "MyEnemyCharacter.h"
#include "MyAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyController::AEnemyController()
{
    MyAIPerceptionComponent = CreateDefaultSubobject<UMyAIPerceptionComponent>("MyAIPerseptionComponent");
    SetPerceptionComponent(*MyAIPerceptionComponent);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<AMyEnemyCharacter>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void AEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusedActor();

    SetFocus(AimActor);
}

AActor* AEnemyController::GetFocusedActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FokusOnKeyName));
}

FVector AEnemyController::GetPlayerLocation()
{
    const auto AimActor = MyAIPerceptionComponent->GetPlayerCharacter();
    if (AimActor)
    {
        FVector AimVector = AimActor->GetActorLocation();
        //  UE_LOG(LogTemp, Display, TEXT("%f,%f,%f"), AimVector.X, AimVector.Y, AimVector.Z);
        return AimVector;
    }
    return FVector::ZeroVector;
}
