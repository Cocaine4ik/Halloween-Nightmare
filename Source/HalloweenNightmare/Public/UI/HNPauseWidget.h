// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBasePauseWidget.h"
#include "HNPauseWidget.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API UHNPauseWidget : public UHNBasePauseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* ResumeTextButtonWidget;
    
    virtual void NativeOnInitialized() override;
    
private:
    
    UFUNCTION()
    void OnResume(); 
};