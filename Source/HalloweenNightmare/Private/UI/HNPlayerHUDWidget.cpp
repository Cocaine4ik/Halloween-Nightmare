// Halloween Nightmare. All Rights Reserved.


#include "UI/HNPlayerHUDWidget.h"
#include "Player/HNPlayer.h"
#include "HNGameMode.h"

FString UHNPlayerHUDWidget::GetScoreText() const
{
    const auto Score = GetScore();

    if (Score / 10) return FString::Printf(TEXT("/%i"), Score);
    
    return FString::Printf(TEXT("/0%i"), Score);
}

FString UHNPlayerHUDWidget::GetLifeCountText() const
{
    const auto LifeCount = GetLifeCount();
    
    if (LifeCount / 10) return FString::Printf(TEXT("/%i"), LifeCount);

    return FString::Printf(TEXT("/0%i"), LifeCount);
}

int32 UHNPlayerHUDWidget::GetLifeCount() const
{
    const auto Player = Cast<AHNPlayer>(GetOwningPlayer()->GetPawn());
    if (!Player) return 0;

    return Player->GetLifeCount();
}

int32 UHNPlayerHUDWidget::GetScore() const
{
    if (!GetWorld()) return 0;
    const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return 0;

    return GameMode->GetScore();
}