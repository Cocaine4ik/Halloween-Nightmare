// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNLevelsWidget.h"

#include "HNGameInstance.h"
#include "HNTextButtonWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHNLevelsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    DefaultLevelTextButton->GetButton()->OnClicked.AddDynamic(this, &UHNLevelsWidget::OnDefaultLevel);
    TextButtonWidgets.Add(DefaultLevelTextButton);

    HardLevelTextButton->GetButton()->OnClicked.AddDynamic(this, &UHNLevelsWidget::OnHardLevel);
    TextButtonWidgets.Add(HardLevelTextButton);

    NightmareLevelTextButton->GetButton()->OnClicked.AddDynamic(this, &UHNLevelsWidget::OnNightmareLevel);
    TextButtonWidgets.Add(NightmareLevelTextButton);

    for (const auto Widget : TextButtonWidgets)
    {
        const auto Button = Widget->GetButton();

        Button->OnHovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextHoverColor);
        Button->OnUnhovered.AddDynamic(Widget, &UHNTextButtonWidget::SetTextDefaultColor);
    }
}

void UHNLevelsWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation) return;
    if (!GetWorld()) return;

    const auto HNGameInstance = GetWorld()->GetGameInstance<UHNGameInstance>();

    if (!HNGameInstance || HNGameInstance->GetStartupLevelName().IsNone()) return;

    UGameplayStatics::OpenLevel(this, HNGameInstance->GetStartupLevelName());
}

void UHNLevelsWidget::OnDefaultLevel()
{
    SetLevel(EHNLevel::Default);
    PlayAnimation(HideAnimation);

}

void UHNLevelsWidget::OnHardLevel()
{
    SetLevel(EHNLevel::Hard);
    PlayAnimation(HideAnimation);

}

void UHNLevelsWidget::OnNightmareLevel()
{
    SetLevel(EHNLevel::Nightmare);
    PlayAnimation(HideAnimation);
}

void UHNLevelsWidget::SetLevel(EHNLevel Level)
{
    if (!GetWorld()) return;

    if (const auto GameInstance = GetWorld()->GetGameInstance<UHNGameInstance>())
    {
        GameInstance->SetLevel(Level);
    }
} 