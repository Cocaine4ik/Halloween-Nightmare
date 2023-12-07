// Halloween Nightmare. All Rights Reserved.


#include "HNGameMode.h"

#include "HNScorePickup.h"
#include "HNLifePickup.h"
#include "Player/HNPlayer.h"
#include "Player/HNPlayerController.h"
#include "UI/HNGameHUD.h"
#include "Environment/HNCaveTile.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

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
        CurrentTileCountToSpawnLife++;
        if (CurrentTileCountToSpawnLife == TargetTilesCountToSpawnLife)
        {
            CurrentTileCountToSpawnLife = 0;
            SpawnPickup(LifePickupClass, CaveTile);
        }
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

    if (SpawnedTile)
    {
        // Spawn score pickups
        SpawnPickups(ScorePickupClass, SpawnedTile, PickupsPerTileCount);

        // Spawn life pickup
        CurrentTileCountToSpawnLife++;

        if (CurrentTileCountToSpawnLife == TargetTilesCountToSpawnLife)
        {
            CurrentTileCountToSpawnLife = 0;
            SpawnPickup(LifePickupClass, SpawnedTile);
        }
    }

    return SpawnedTile;
}

void AHNGameMode::SpawnPickup(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile)
{
    if (!GetWorld()) return;

    FVector Location;
    
    if (CaveTile->CalculateRandomSpawnLocation(Location))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        const auto Pickup = GetWorld()->SpawnActor<AHNBasePickup>(PickupClass, Location,
            FRotator(0.0f,0.0f,0.0f), SpawnParameters);
    }
}

void AHNGameMode::SpawnPickups(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile, const int32 Count)
{
    for (int i = 0; i < Count; i++)
    {
        SpawnPickup(PickupClass, CaveTile);
    }
}


void AHNGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnStartCaveTile();
    SpawnCaveTileWithRandomAngle();
    SpawnCaveTileWithRandomAngle();
}

void AHNGameMode::StartPlay()
{
    Super::StartPlay();
    SetGameState(EHNGameState::InProgress);
}

void AHNGameMode::GameOver()
{
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
}

bool AHNGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool bPauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (bPauseSet)
    {
        SetGameState(EHNGameState::Pause);
    }
    return bPauseSet;
}

bool AHNGameMode::ClearPause()
{
    const bool bPauseClear = Super::ClearPause();

    if (bPauseClear)
    {
        SetGameState(EHNGameState::InProgress);
    }
    
    return bPauseClear;
}

void AHNGameMode::RestartGame()
{
}

void AHNGameMode::SetGameState(EHNGameState State)
{
    if (GameState == State) return;

    GameState = State;
    OnGameStateChanged.Broadcast(State);

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange,
        FString::Printf(TEXT("State Changed")));
}
