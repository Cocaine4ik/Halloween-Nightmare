// Halloween Nightmare. All Rights Reserved.


#include "Menu/HNMenuPlayerController.h"

void AHNMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}