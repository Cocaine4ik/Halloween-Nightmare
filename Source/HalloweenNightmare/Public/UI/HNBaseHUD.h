// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HNCoreTypes.h"
#include "HNBaseHUD.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API AHNBaseHUD : public AHUD
{
    GENERATED_BODY()

public:

    virtual void BeginPlay() override;

protected:
    
    UPROPERTY()
    TMap<EHNGameState, UUserWidget*> GameWidgets;
private:
    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
    
    void OnGameStateChanged(EHNGameState State);
};