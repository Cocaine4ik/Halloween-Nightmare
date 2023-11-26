// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNCaveTile.h"
#include "GameFramework/GameModeBase.h"
#include "HNCoreTypes.h"
#include "HNGameMode.generated.h"

class AHNLifePickup;
class AHNCaveTile;
class AHNScorePickup;
class AHNBasePickup;
/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API AHNGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AHNGameMode();

protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
    int32 Score = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TSubclassOf<AHNCaveTile> DefaultCaveTileClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    int32 TilesCount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Environment")
    FDestroyedObstaclesData DestroyedObstaclesData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    TSubclassOf<AHNScorePickup> ScorePickupClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    TSubclassOf<AHNLifePickup> LifePickupClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    int32 PickupsPerTileCount = 8;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickups")
    int32 TargetTilesCountToSpawnLife = 5;
private:
    int32 CurrentTileCountToSpawnLife = 0;
public:
    int32 GetScore() const { return Score; }
    void AddScore(const int32 Value) { Score += Value; }
    FDestroyedObstaclesData GetDestroyedObstaclesData() const { return DestroyedObstaclesData; }
    AHNCaveTile* SpawnStartCaveTile();
    AHNCaveTile* SpawnCaveTileWithRandomAngle();
    void SpawnPickup(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile);
    void SpawnPickups(TSubclassOf<AHNBasePickup> PickupClass, AHNCaveTile* CaveTile, const int32 Count);
    virtual void BeginPlay() override;

    void GameOver();
private:
    AHNCaveTile* SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform);
    AHNCaveTile* PreviousCaveTile;
};