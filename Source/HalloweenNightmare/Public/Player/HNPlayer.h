// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HNPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AHNPlayerController;

UCLASS()
class HALLOWEENNIGHTMARE_API AHNPlayer : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AHNPlayer();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* JumpAction;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // To add mapping context
    virtual void BeginPlay() override;

public:
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    AHNPlayerController* GetPlayerController() const;
};