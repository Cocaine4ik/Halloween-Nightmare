// Halloween Nightmare. All Rights Reserved.


#include "Menu/HNMenuGameMode.h"
#include "Menu/HNMenuPlayerController.h"
#include "Menu/UI/HNMenuHUD.h"

AHNMenuGameMode::AHNMenuGameMode()
{
    PlayerControllerClass = AHNMenuPlayerController::StaticClass();
    HUDClass = AHNMenuHUD::StaticClass();
}

void AHNMenuGameMode::StartPlay()
{
    Super::StartPlay();
    SetGameState(EHNGameState::Menu);
}