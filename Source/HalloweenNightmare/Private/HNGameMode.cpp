// Halloween Nightmare. All Rights Reserved.


#include "HNGameMode.h"
#include "Player/HNPlayer.h"
#include "Player/HNPlayerController.h"
#include "UI/HNGameHUD.h"
#include "Environment/HNCaveTile.h"
#include "Kismet/GameplayStatics.h"

AHNGameMode::AHNGameMode()
{
    DefaultPawnClass = AHNPlayer::StaticClass();
    PlayerControllerClass = AHNPlayerController::StaticClass();
    HUDClass = AHNGameHUD::StaticClass();
}

AHNCaveTile* AHNGameMode::SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform)
{

    if (!GetWorld()) return nullptr;

    const auto Player = Cast<AHNPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!Player) return nullptr;
    
    AHNCaveTile* CaveTile = GetWorld()->SpawnActorDeferred<AHNCaveTile>(CaveTileClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

    UGameplayStatics::FinishSpawningActor(CaveTile, AttachPointTransform);
    
    if (CaveTile)
    {
        PreviousCaveTile = CaveTile;
    }
    
    return CaveTile;
}

AHNCaveTile* AHNGameMode::RandomSpawnCaveTile()
{
    const auto RandomTileClassNum = FMath::RandRange(0, CaveTileClasses.Num() - 1);
    
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
        FString::Printf(TEXT("PreviousCaveTile name: %s"), *PreviousCaveTile->GetName()));
    
    
    return SpawnCaveTile(CaveTileClasses[RandomTileClassNum], PreviousCaveTile->GetAttachTransform());
}

void AHNGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnCaveTile(StraightCaveTileClass, FTransform::Identity);
}