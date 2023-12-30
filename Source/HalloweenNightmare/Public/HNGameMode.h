// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNCaveTile.h"
#include "HNGameModeBase.h"
#include "HNGameMode.generated.h"

class UDataTable;
class AHNLifePickup;
class AHNCaveTile;
class AHNScorePickup;
class AHNBasePickup;



UCLASS()
class HALLOWEENNIGHTMARE_API AHNGameMode : public AHNGameModeBase
{
    GENERATED_BODY()

public:
    AHNGameMode();
    
protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
    int32 Score = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
    TSubclassOf<AHNCaveTile> DefaultCaveTileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Level")
    FHNLevelData LevelData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    TSubclassOf<AHNScorePickup> ScorePickupClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    TSubclassOf<AHNLifePickup> LifePickupClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    UDataTable* LevelsDataTable;
    
private:
    int32 CurrentTileCountToSpawnLife = 0;
    
public:
    int32 GetScore() const { return Score; }
    void AddScore(const int32 Value) { Score += Value; }
    
    FHNLevelData GetDestroyedObstaclesData() const { return LevelData; }
    AHNCaveTile* SpawnStartCaveTile();
    AHNCaveTile* SpawnCaveTileWithRandomAngle();
    
    AActor* SpawnPickup(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile);
    void SpawnPickups(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile, const int32 Count);
    
    virtual void BeginPlay() override;
    virtual void StartPlay() override;

    void GameOver();
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

    void SaveScore();
private:
    AHNCaveTile* SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform);
    AHNCaveTile* PreviousCaveTile;

    void LoadLevelData();
    FHNLevelData GetLevelData(FName LevelName) const;
};