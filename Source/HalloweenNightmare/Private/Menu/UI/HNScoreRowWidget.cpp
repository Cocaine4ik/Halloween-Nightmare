// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNScoreRowWidget.h"
#include "Components/TextBlock.h"

void UHNScoreRowWidget::SetPlace(const FText& Text)
{
    if (!PlaceTextBlock) return;

    PlaceTextBlock->SetText(Text);
}

void UHNScoreRowWidget::SetUserName(const FText& Text)
{
    if (!UserNameTextBlock) return;

    UserNameTextBlock->SetText(Text);
}

void UHNScoreRowWidget::SetScore(const FText& Text)
{
    if (!ScoreTextBlock) return;

    ScoreTextBlock->SetText(Text);
}

void UHNScoreRowWidget::SetLevelName(const FText& Text)
{
    if (!LevelNameTextBlock) return;

    LevelNameTextBlock->SetText(Text);
}

void UHNScoreRowWidget::SetDateTime(const FText& Text)
{
    if (!DateTimeTextBlock) return;

    DateTimeTextBlock->SetText(Text);
}