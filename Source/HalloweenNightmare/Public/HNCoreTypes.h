// Halloween Nightmare. All Rights Reserved.

#pragma once
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "HNCoreTypes.generated.h"

// Delegates

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EHNGameState);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveUserNameSignature, FName);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveScoresSignature, const FHNScoresData& ScoresData);

// Enums

UENUM(BlueprintType)
enum class EHNGameState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver,
    Menu,
    Scores,
    Levels
};

UENUM(BlueprintType)
enum class EHNLevel : uint8
{
    Default = 0,
    Hard,
    Nightmare
};

// Structs

USTRUCT(BlueprintType)
struct FHNLevelData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Level")
    int32 MinDestroyObstaclesCount = 2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Level")
    int32 MaxDestroyObstaclesCount = 4;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Level")
    int32 MinDestroySmallObstaclesCount = 3;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Level")
    int32 MaxDestroySmallObstaclesCount = 6;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickups")
    int32 PickupsPerTileCount = 8;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickups")
    int32 TargetTilesCountToSpawnLife = 5;
};

USTRUCT(BlueprintType)
struct FHNScoresData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    FName UserName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    FName LevelName;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    int32 Score;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    FDateTime DateTime;
};

// Data Assets

UCLASS()
class HALLOWEENNIGHTMARE_API UHNUserNameDataAsset : public UDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    FName UserName = "User";

public:
    FORCEINLINE FName GetUserName() const { return UserName; } 
    FORCEINLINE void SetUserName(const FName Name) { UserName = Name; }
};