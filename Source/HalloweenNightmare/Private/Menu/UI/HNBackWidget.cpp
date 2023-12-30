// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNBackWidget.h"
#include "HNTextButtonWidget.h"
#include "Components/Button.h"
#include "HNGameModeBase.h"

void UHNBackWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (BackTextButtonWidget)
    {
        BackTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNBackWidget::OnBack);
        BackTextButtonWidget->GetButton()->OnHovered.AddDynamic(BackTextButtonWidget, &UHNTextButtonWidget::SetTextHoverColor);
        BackTextButtonWidget->GetButton()->OnUnhovered.AddDynamic(BackTextButtonWidget, &UHNTextButtonWidget::SetTextDefaultColor);

    }
}

void UHNBackWidget::OnBack()
{
    if (!GetWorld()) return;

    if (const auto GameMode = Cast<AHNGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->SetGameState(EHNGameState::Menu);
    }
}