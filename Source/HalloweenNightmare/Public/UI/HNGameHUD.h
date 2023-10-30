// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HNGameHUD.generated.h"

class UUserWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API AHNGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

public:

    virtual void BeginPlay() override;
};