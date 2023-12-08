// Halloween Nightmare. All Rights Reserved.


#include "UI/HNBasePauseWidget.h"
#include "HNTextButtonWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHNBasePauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (MainMenuTextButtonWidget)
    {
        MainMenuTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNBasePauseWidget::OnMainMenu);
        TextButtonWidgets.Add(MainMenuTextButtonWidget);
    }

    if (RestartTextButtonWidget)
    {
        RestartTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNBasePauseWidget::OnRestart);
        TextButtonWidgets.Add(RestartTextButtonWidget);
    }
    
    for (const auto Widget : TextButtonWidgets)
    {
        const auto Button = Widget->GetButton();
        Button->OnHovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextHoverColor);
        Button->OnUnhovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextDefaultColor);
    }
}

void UHNBasePauseWidget::OnRestart()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void UHNBasePauseWidget::OnMainMenu()
{
}