// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
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
    UInputAction* MoveRightAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveUpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
    int32 LifeCount = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Invulnerability")
    float InvulnerabilityTime = 2.0f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Invulnerability")
    TArray<UMaterial*> DefaultMaterials;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Invulnerability")
    UMaterialInstance* TransparentMaterial;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Invulnerability")
    bool bIsInvulnerable = false;
    
private:
    FTimerHandle InvulnerabilityTimer;
    
    void MoveRight(const FInputActionValue& Value);
    void MoveUp(const FInputActionValue& Value);
    void MoveForward();
    void Look(const FInputActionValue& Value);
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // To add mapping context
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    void SetInvulnerabilityActive(bool bActive);
    void StartInvulnerabilityTimer();

    void InitializeDefaultMaterials();
    void SetDefaultMaterials();
    void SetTransparentMaterials();
public:

    int32 GetLifeCount() const { return LifeCount; }
    void AddLife(int32 Value);
    void SetMaxFlySpeed(int32 Value) { GetCharacterMovement()->MaxFlySpeed = Value; }
    
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    AHNPlayerController* GetPlayerController() const;

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};