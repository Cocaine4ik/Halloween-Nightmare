// Halloween Nightmare. All Rights Reserved.


#include "UI/HNPauseWidget.h"

#include "HNTextButtonWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void UHNPauseWidget::NativeOnInitialized()
{
    if (ResumeTextButtonWidget)
    {
        ResumeTextButtonWidget->GetButton()->OnClicked.AddDynamic(this, &UHNPauseWidget::OnResume);
        TextButtonWidgets.Add(ResumeTextButtonWidget);
    }
    
    Super::NativeOnInitialized();
}

void UHNPauseWidget::OnResume()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
