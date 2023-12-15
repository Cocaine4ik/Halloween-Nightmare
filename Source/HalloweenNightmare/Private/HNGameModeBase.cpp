// Halloween Nightmare. All Rights Reserved.


#include "HNGameModeBase.h"

void AHNGameModeBase::SetGameState(EHNGameState State)
{
    if (GameState == State) return;

    GameState = State;
    OnGameStateChanged.Broadcast(State);

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange,
        FString::Printf(TEXT("State Changed")));
}