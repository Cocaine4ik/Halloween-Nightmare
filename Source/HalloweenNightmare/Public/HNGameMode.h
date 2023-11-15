// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HNCoreTypes.h"
#include "HNGameMode.generated.h"

class AHNCaveTile;
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
    
public:
    int32 GetScore() const { return Score; }
    void AddScore(const int32 Value) { Score += Value; }
    FDestroyedObstaclesData GetDestroyedObstaclesData() const { return DestroyedObstaclesData; }
    AHNCaveTile* SpawnStartCaveTile();
    AHNCaveTile* SpawnCaveTileWithRandomAngle();

    virtual void BeginPlay() override;
    
private:
    AHNCaveTile* SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform);
    AHNCaveTile* PreviousCaveTile;
};