// Halloween Nightmare. All Rights Reserved.


#include "UI/HNBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "HNGameMode.h"

void AHNBaseHUD::BeginPlay()
{
    Super::BeginPlay();

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AHNGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChanged.AddUObject(this, &AHNBaseHUD::OnGameStateChanged);
        }
    }
}

void AHNBaseHUD::OnGameStateChanged(EHNGameState State)
{
    // hide current widget if it exists
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    // set current widget match the state
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    // make current widget visible
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}