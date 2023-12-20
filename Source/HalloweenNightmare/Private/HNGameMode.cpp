// Halloween Nightmare. All Rights Reserved.


#include "HNGameMode.h"
#include "HNScorePickup.h"
#include "HNLifePickup.h"
#include "Player/HNPlayer.h"
#include "Player/HNPlayerController.h"
#include "UI/HNGameHUD.h"
#include "Levels/HNCaveTile.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "HNGameInstance.h"
#include "HNSaveGame.h"
#include "Engine/DataTable.h"

AHNGameMode::AHNGameMode()
{
    DefaultPawnClass = AHNPlayer::StaticClass();
    PlayerControllerClass = AHNPlayerController::StaticClass();
    HUDClass = AHNGameHUD::StaticClass();
}

void AHNGameMode::SaveScore()
{
    if (!GetWorld())
    {
        return;
    }

    if (const auto HNGameInstance = GetWorld()->GetGameInstance<UHNGameInstance>())
    {
        const FName UserName = HNGameInstance->GetUserName();
        const FDateTime CurrentDateTime(FDateTime::Now());
        const FName LevelName = HNGameInstance->GetLevelName();

        FHNScoresData ScoresData;

        ScoresData.Score = Score;
        ScoresData.UserName = UserName;
        ScoresData.LevelName = LevelName;
        ScoresData.DateTime = CurrentDateTime;

        HNGameInstance->OnSaveScores.Broadcast(ScoresData);
    }
}

AHNCaveTile* AHNGameMode::SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform)
{

    if (!GetWorld())
    {
        return nullptr;
    }

    const auto Player = Cast<AHNPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!Player)
    {
        return nullptr;
    }

    AHNCaveTile* CaveTile = GetWorld()->SpawnActorDeferred<AHNCaveTile>(CaveTileClass, FTransform::Identity, nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

    UGameplayStatics::FinishSpawningActor(CaveTile, AttachPointTransform);

    if (CaveTile)
    {
        PreviousCaveTile = CaveTile;
        CurrentTileCountToSpawnLife++;
        if (CurrentTileCountToSpawnLife == LevelData.TargetTilesCountToSpawnLife)
        {
            CurrentTileCountToSpawnLife = 0;
            const auto Pickup = SpawnPickup(LifePickupClass, CaveTile);
            CaveTile->AddPickup(Pickup);
        }
    }

    return CaveTile;
}

void AHNGameMode::LoadLevelData()
{
    if (!GetWorld())
    {
        return;
    }

    if (const auto GameInstance = GetWorld()->GetGameInstance<UHNGameInstance>())
    {
        const EHNLevel Level = GameInstance->GetLevel();

        switch (Level)
        {
            case EHNLevel::Hard: LevelData = GetLevelData(FName("Hard"));
                break;
            case EHNLevel::Nightmare: LevelData = GetLevelData(FName("Nightmare"));
                break;

            default: LevelData = GetLevelData(FName("Default"));
                break;
        }
    }
}

FHNLevelData AHNGameMode::GetLevelData(FName LevelName) const
{
    if (!LevelsDataTable)
    {
        return LevelData;
    }

    if (const auto Data = LevelsDataTable->FindRow<FHNLevelData>(LevelName, ""))
    {
        return *Data;
    }

    return LevelData;
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
        SpawnPickups(ScorePickupClass, SpawnedTile, LevelData.PickupsPerTileCount);

        // Spawn life pickup
        CurrentTileCountToSpawnLife++;

        if (CurrentTileCountToSpawnLife == LevelData.TargetTilesCountToSpawnLife)
        {
            CurrentTileCountToSpawnLife = 0;
            SpawnPickup(LifePickupClass, SpawnedTile);
        }
    }

    return SpawnedTile;
}

AActor* AHNGameMode::SpawnPickup(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile)
{
    if (!GetWorld())
    {
        return nullptr;
    }

    FVector Location;

    if (CaveTile->CalculateRandomSpawnLocation(Location))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        const auto Pickup = GetWorld()->SpawnActor<AHNBasePickup>(PickupClass, Location,
            FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);

        return Pickup;
    }

    return nullptr;
}

void AHNGameMode::SpawnPickups(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile, const int32 Count)
{
    for (int i = 0; i < Count; i++)
    {
        const auto Pickup = SpawnPickup(PickupClass, CaveTile);
        CaveTile->AddPickup(Pickup);
    }
}


void AHNGameMode::BeginPlay()
{
    Super::BeginPlay();

    LoadLevelData();

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
    SetGameState(EHNGameState::GameOver);

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