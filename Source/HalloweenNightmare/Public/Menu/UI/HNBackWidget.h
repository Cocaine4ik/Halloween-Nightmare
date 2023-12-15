// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNBackWidget.generated.h"


class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNBackWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* BackTextButtonWidget;

    virtual void NativeOnInitialized() override;
private:
    UFUNCTION()
    void OnBack();
};