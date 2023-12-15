// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HNBaseHUD.h"
#include "HNGameHUD.generated.h"

class UUserWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API AHNGameHUD : public AHNBaseHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

public:
    virtual void BeginPlay() override;
};