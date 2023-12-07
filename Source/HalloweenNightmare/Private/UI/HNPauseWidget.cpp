// Halloween Nightmare. All Rights Reserved.


#include "UI/HNPauseWidget.h"

#include "HNTextButtonWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void UHNPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ResumeTextButtonWidget)
    {
        ResumeTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNPauseWidget::OnResume);
        TextButtonWidgets.Add(ResumeTextButtonWidget);
    }

    if (MainMenuTextButtonWidget)
    {
        MainMenuTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNPauseWidget::OnMainMenu);
        TextButtonWidgets.Add(MainMenuTextButtonWidget);
    }

    if (RestartTextButtonWidget)
    {
        RestartTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNPauseWidget::OnRestart);
        TextButtonWidgets.Add(RestartTextButtonWidget);
    }

    for (const auto Widget : TextButtonWidgets)
    {
        const auto Button = Widget->GetButton();
        Button->OnHovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextHoverColor);
        Button->OnUnhovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextDefaultColor);
    }
}

void UHNPauseWidget::OnResume()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void UHNPauseWidget::OnMainMenu()
{
}

void UHNPauseWidget::OnRestart()
{
}
