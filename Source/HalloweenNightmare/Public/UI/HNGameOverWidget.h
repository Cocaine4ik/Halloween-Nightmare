// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBasePauseWidget.h"
#include "HNGameOverWidget.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API UHNGameOverWidget : public UHNBasePauseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetScoreText() const;

private:
    int32 GetScore() const;
};