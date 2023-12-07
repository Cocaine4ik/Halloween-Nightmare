// Halloween Nightmare. All Rights Reserved.


#include "UI/HNGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "HNGameMode.h"
void AHNGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameWidgets.Add(EHNGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EHNGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChanged.AddUObject(this, &AHNGameHUD::OnGameStateChanged);
        }
    }
}

void AHNGameHUD::OnGameStateChanged(EHNGameState State)
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