// Halloween Nightmare. All Rights Reserved.

#pragma once
#include "HNCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FDestroyedObstaclesData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Environment")
    int32 MinObstaclesCount = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Environment")
    int32 MaxObstaclesCount = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Environment")
    int32 MinSmallObstaclesCount = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Environment")
    int32 MaxSmallObstaclesCount = 6;
    
};

UENUM(BlueprintType)
enum class EHNGameState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GaveOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EHNGameState);