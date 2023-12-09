// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNMenuWidget.generated.h"

class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* NewGameTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* ScoresTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* QuitTextButtonWidget;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HideAnimation;
    
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    TArray<UHNTextButtonWidget*> TextButtonWidgets;

    UFUNCTION()
    void OnNewGame();

    UFUNCTION()
    void OnShowScores();

    UFUNCTION()
    void OnQuitGame();
};