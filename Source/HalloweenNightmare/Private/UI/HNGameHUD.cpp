// Halloween Nightmare. All Rights Reserved.


#include "UI/HNGameHUD.h"
#include "Blueprint/UserWidget.h"

void AHNGameHUD::BeginPlay()
{
    GameWidgets.Add(EHNGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EHNGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EHNGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    Super::BeginPlay();
}
