// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HNCoreTypes.h"
#include "HNGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API AHNGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    FOnGameStateChangedSignature OnGameStateChanged;
    
    void SetGameState(EHNGameState State);
    EHNGameState GetGameState() const { return GameState; }

private:
    EHNGameState GameState = EHNGameState::WaitingToStart;
};