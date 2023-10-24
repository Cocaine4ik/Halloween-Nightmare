// Halloween Nightmare. All Rights Reserved.


#include "HMGameMode.h"
#include "Player/HNPlayer.h"
#include "Player/HNPlayerController.h"

AHMGameMode::AHMGameMode()
{
    DefaultPawnClass = AHNPlayer::StaticClass();
    PlayerControllerClass = AHNPlayerController::StaticClass();
}