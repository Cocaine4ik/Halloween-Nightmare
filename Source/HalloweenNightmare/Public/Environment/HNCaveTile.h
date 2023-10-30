// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "HNCaveTile.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum EHNCaveType : uint8
{
    CT_Straight = 0     UMETA(DisplayName = "Straight"),
    CT_Right = 1        UMETA(DisplayName = "Right"),
    CT_Left = 2         UMETA(DisplayName = "Left"),
    CT_Curved = 3       UMETA(DisplayName = "Curved"),
};

UCLASS()
class HALLOWEENNIGHTMARE_API AHNCaveTile : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* CaveMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* CaveTriggerBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UArrowComponent* AttachPoint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
    TEnumAsByte<EHNCaveType> CaveTypeEnum = EHNCaveType::CT_Straight;

public:
    // Sets default values for this actor's properties
    AHNCaveTile();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    FORCEINLINE const FTransform& GetAttachTransform() const { return AttachPoint->GetComponentTransform(); }
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    TEnumAsByte<EHNCaveType> GetCaveType() const { return CaveTypeEnum; }
};