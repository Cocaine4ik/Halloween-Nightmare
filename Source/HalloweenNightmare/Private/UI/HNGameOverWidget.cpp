// Halloween Nightmare. All Rights Reserved.

#include "UI/HNGameOverWidget.h"
#include "HNGameMode.h"

FString UHNGameOverWidget::GetScoreText() const
{
    const auto Score = GetScore();

    if (Score / 10) return FString::Printf(TEXT("%i"), Score);
    
    return FString::Printf(TEXT("0%i"), Score);
}

int32 UHNGameOverWidget::GetScore() const
{
    if (!GetWorld()) return 0;
    const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return 0;

    return GameMode->GetScore();
}