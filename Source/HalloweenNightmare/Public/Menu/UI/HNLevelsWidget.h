// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBackWidget.h"
#include "HNCoreTypes.h"
#include "HNLevelsWidget.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API UHNLevelsWidget : public UHNBackWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* DefaultLevelTextButton;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* HardLevelTextButton;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* NightmareLevelTextButton;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HideAnimation;
    
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
private:
    TArray<UHNTextButtonWidget*> TextButtonWidgets;
    
    UFUNCTION()
    void OnDefaultLevel();

    UFUNCTION()
    void OnHardLevel();

    UFUNCTION()
    void OnNightmareLevel();

    void SetLevel(EHNLevel Level);
};