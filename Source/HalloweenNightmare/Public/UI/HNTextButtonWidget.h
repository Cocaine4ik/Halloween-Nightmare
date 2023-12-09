// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h"
#include "HNTextButtonWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNTextButtonWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* Button;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Style")
    FSlateColor HoverColor;

    virtual void NativeOnInitialized() override;

public:
    UFUNCTION()
    void SetTextHoverColor();
    UFUNCTION()
    void SetTextDefaultColor();

    UButton* GetButton() const {return Button; }
private:
    FSlateColor DefaultTextColor;

    void SetTextColor(FSlateColor Color);
};