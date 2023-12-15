// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBaseHUD.h"
#include "HNMenuHUD.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API AHNMenuHUD : public AHNBaseHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ScoresWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelsWidgetClass;
    
    
    virtual void BeginPlay() override;
};