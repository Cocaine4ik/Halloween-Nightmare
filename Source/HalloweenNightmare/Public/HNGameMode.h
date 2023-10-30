// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
    TArray<TSubclassOf<AHNCaveTile>> CaveTileClasses;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TSubclassOf<AHNCaveTile> StraightCaveTileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TSubclassOf<AHNCaveTile> RightCaveTileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TSubclassOf<AHNCaveTile> LeftCaveTileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TSubclassOf<AHNCaveTile> CurvedCaveTileClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    int32 TilesCount = 10;
    
public:
    int32 GetScore() const { return Score; }
    void AddScore(const int32 Value) { Score += Value; }

    AHNCaveTile* RandomSpawnCaveTile();
    virtual void BeginPlay() override;
    
private:
    AHNCaveTile* SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform);
    
    AHNCaveTile* PreviousCaveTile;
};