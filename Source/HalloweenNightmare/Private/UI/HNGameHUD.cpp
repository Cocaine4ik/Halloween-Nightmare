// Halloween Nightmare. All Rights Reserved.


#include "UI/HNGameHUD.h"
#include "Blueprint/UserWidget.h"

void AHNGameHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    PlayerHUDWidget->AddToViewport();
    PlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
}