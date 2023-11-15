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

AHNCaveTile* AHNGameMode::SpawnStartCaveTile()
{
    const auto SpawnedTile = SpawnCaveTile(DefaultCaveTileClass, FTransform::Identity);
    SpawnedTile->DestroyAllObstacles();

    return SpawnedTile;
}

AHNCaveTile* AHNGameMode::SpawnCaveTileWithRandomAngle()
{
    const auto SpawnedTile = SpawnCaveTile(DefaultCaveTileClass, PreviousCaveTile->GetAttachTransform());

    SpawnedTile->RandomDestroyAllObstacles();
    SpawnedTile->SetRandomCaveTileAngle();
    
    return SpawnedTile;
}


void AHNGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnStartCaveTile();
    SpawnCaveTileWithRandomAngle();
    SpawnCaveTileWithRandomAngle();
}