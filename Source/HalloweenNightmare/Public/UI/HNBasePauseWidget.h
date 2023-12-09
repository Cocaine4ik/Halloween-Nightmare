// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNCoreTypes.h"
#include "HNBasePauseWidget.generated.h"

class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNBasePauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* RestartTextButtonWidget;
    
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* MainMenuTextButtonWidget;

    TArray<UHNTextButtonWidget*> TextButtonWidgets;
    
    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void OnRestart();

    UFUNCTION()
    void OnMainMenu();
};