// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HNBasePickup.generated.h"

class USphereComponent;
class AHNPlayer;
UCLASS()
class HALLOWEENNIGHTMARE_API AHNBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHNBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* SceneComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
    float MinRotationYawSpeed = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
    float MaxRotationYawSpeed = 0.5f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lift")
    float MaxLiftOffset = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lift")
    float LiftSpeed = 0.1f;

    AHNPlayer* Player;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void Invoke();

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    float RotationYaw;
    FVector InitialLocation;
    bool LiftUp = true;
    void GenerateRandomRotationYaw();
    void SetActorInitialLocation() { InitialLocation = GetActorLocation(); }
    void LiftActor();
};