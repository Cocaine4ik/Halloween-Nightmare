// Halloween Nightmare. All Rights Reserved.


#include "Player/HNPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"
#include "HNGameMode.h"

void AHNPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &AHNPlayerController::OnPauseGame);
    }
}

void AHNPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnGameStateChanged.AddUObject(this, &AHNPlayerController::OnGameStateChanged);
        }
    }
}

void AHNPlayerController::OnPauseGame(const FInputActionValue& Value)
{
    if (!GetWorld()) return;

    if (const auto GameMode = GetWorld()->GetAuthGameMode())
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
            FString::Printf(TEXT("On Pause")));
        
        bIsPaused ? GameMode->ClearPause() : GameMode->SetPause(this);
    }
}

void AHNPlayerController::OnGameStateChanged(EHNGameState State)
{
    if (State == EHNGameState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
        bIsPaused = false;
    }
    else
    {
        SetInputMode(FInputModeGameAndUI());
        bShowMouseCursor = true;

        if (State == EHNGameState::Pause)
        {
            bIsPaused = true;
        }
    }
}