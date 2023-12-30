// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNGameModeBase.h"
#include "HNMenuGameMode.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API AHNMenuGameMode : public AHNGameModeBase
{
    GENERATED_BODY()

public:
    AHNMenuGameMode();

    virtual void StartPlay() override;
};