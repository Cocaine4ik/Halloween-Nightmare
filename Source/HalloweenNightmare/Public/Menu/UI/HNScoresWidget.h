// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBackWidget.h"
#include "HNCoreTypes.h"
#include "HNScoresWidget.generated.h"

class UVerticalBox;
class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNScoresWidget : public UHNBackWidget
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* ScoresBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ScoreRowWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    int32 ScoreTableRowsNum = 10;
    
    virtual void NativeOnInitialized() override;

private:
    void OnGameStateChanged(EHNGameState State);
    
    void UpdateScoresTable();
};