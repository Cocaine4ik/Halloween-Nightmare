// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HNCoreTypes.h"
#include "InputActionValue.h"
#include "HNPlayerController.generated.h"

class UInputAction;

UCLASS()
class HALLOWEENNIGHTMARE_API AHNPlayerController : public APlayerController
{
    GENERATED_BODY()

    virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* PauseGameAction;

    virtual void BeginPlay() override;
    
private:
    bool bIsPaused = false;
    
    void OnPauseGame(const FInputActionValue& Value);
    void OnGameStateChanged(EHNGameState State);
};