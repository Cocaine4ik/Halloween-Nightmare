// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API UHNPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetScoreText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetLifeCountText() const;
    
private:
    int32 GetLifeCount() const;
    int32 GetScore() const;
};