// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNPauseWidget.generated.h"

class UTextBlock;
class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNPauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* ResumeTextButtonWidget;
    
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* MainMenuTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* RestartTextButtonWidget;
    
    virtual void NativeOnInitialized() override;
    
private:
    TArray<UHNTextButtonWidget*> TextButtonWidgets;
    
    UFUNCTION()
    void OnResume(); 

    UFUNCTION()
    void OnMainMenu();

    UFUNCTION()
    void OnRestart();
};