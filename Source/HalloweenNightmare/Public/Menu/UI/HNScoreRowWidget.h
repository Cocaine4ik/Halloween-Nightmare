// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNScoreRowWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API UHNScoreRowWidget : public UUserWidget
{
    GENERATED_BODY()
protected:
    UPROPERTY(meta=(BindWidget))
    UTextBlock* PlaceTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* UserNameTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ScoreTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* LevelNameTextBlock;
    
    UPROPERTY(meta=(BindWidget))
    UTextBlock* DateTimeTextBlock;
    
public:
    void SetPlace(const FText& Text);
    void SetUserName(const FText& Text);
    void SetScore(const FText& Text);
    void SetLevelName(const FText& Text);
    void SetDateTime(const FText& Text);
};