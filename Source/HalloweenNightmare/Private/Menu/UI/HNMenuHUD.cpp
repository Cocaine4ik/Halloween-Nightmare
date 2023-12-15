// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AHNMenuHUD::BeginPlay()
{
    GameWidgets.Add(EHNGameState::Menu, CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass));
    GameWidgets.Add(EHNGameState::Scores, CreateWidget<UUserWidget>(GetWorld(), ScoresWidgetClass));
    GameWidgets.Add(EHNGameState::Levels, CreateWidget<UUserWidget>(GetWorld(), LevelsWidgetClass));
    
    Super::BeginPlay();
}