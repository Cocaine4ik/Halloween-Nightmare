// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNMenuWidget.h"

#include "HNGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/HNTextButtonWidget.h"

void UHNMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (NewGameTextButtonWidget)
    {
        NewGameTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNMenuWidget::OnNewGame);
        TextButtonWidgets.Add(NewGameTextButtonWidget);
    }

    if (ScoresTextButtonWidget)
    {
        ScoresTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNMenuWidget::OnShowScores);
        TextButtonWidgets.Add(ScoresTextButtonWidget);
    }

    if (QuitTextButtonWidget)
    {
        QuitTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNMenuWidget::OnQuitGame);
        TextButtonWidgets.Add(QuitTextButtonWidget);
    }

    for (const auto Widget : TextButtonWidgets)
    {
        const auto Button = Widget->GetButton();
        Button->OnHovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextHoverColor);
        Button->OnUnhovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextDefaultColor);
    }
}

void UHNMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation) return;
    if (!GetWorld()) return;

    const auto HNGameInstance = GetWorld()->GetGameInstance<UHNGameInstance>();

    if (!HNGameInstance || HNGameInstance->GetStartupLevelName().IsNone()) return;

    UGameplayStatics::OpenLevel(this, HNGameInstance->GetStartupLevelName());
}

void UHNMenuWidget::OnNewGame()
{
    PlayAnimation(HideAnimation);
}

void UHNMenuWidget::OnShowScores()
{
}

void UHNMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}