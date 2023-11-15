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
class AHNObstacle;

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
    UBoxComponent* SpawnVolume;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UArrowComponent* AttachPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
    TArray<UStaticMeshComponent*> LeftSideObstacles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
    TArray<UStaticMeshComponent*> CenterObstacles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
    TArray<UStaticMeshComponent*> RightSideObstacles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
    TArray<UStaticMeshComponent*> SmallObstacles;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Obstacles")
    int32 ObstaclesCountPerSide = 5;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Obstacles")
    int32 SmallObstaclesCount = 10;

private:
    TArray<UStaticMeshComponent*> AddObstacleMeshes(int32 Count, const FString PrefixName);
    void RandomDestroyObstacles(TArray<UStaticMeshComponent*> Obstacles, const int32 MinCount, const int32 MaxCount);
    void DestroyObstacles(TArray<UStaticMeshComponent*> Obstacles);
public:
    // Sets default values for this actor's properties
    AHNCaveTile();
    void RandomDestroyAllObstacles();
    void DestroyAllObstacles();
    void SetRandomCaveTileAngle();

public:
    FORCEINLINE const FTransform& GetAttachTransform() const { return AttachPoint->GetComponentTransform(); }
};

