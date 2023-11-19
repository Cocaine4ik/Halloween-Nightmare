// Halloween Nightmare. All Rights Reserved.


#include "Environment/HNCaveTile.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HNGameMode.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHNCaveTile::AHNCaveTile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    RootComponent = SceneComponent;

    CaveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CaveMesh"));
    CaveMesh->SetupAttachment(RootComponent);

    CaveTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CaveTriggerBox"));
    CaveTriggerBox->SetupAttachment(RootComponent);

    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    SpawnVolume->SetupAttachment(RootComponent);

    AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AtachPoint"));
    AttachPoint->SetupAttachment(RootComponent);

    LeftSideObstacles = AddObstacleMeshes(ObstaclesCountPerSide, FString("Left"));
    RightSideObstacles = AddObstacleMeshes(ObstaclesCountPerSide, FString("Right"));
    CenterObstacles = AddObstacleMeshes(ObstaclesCountPerSide, FString("Center"));

    SmallObstacles = AddObstacleMeshes(SmallObstaclesCount, FString("Small"));
}

void AHNCaveTile::RandomDestroyAllObstacles()
{
    if (!GetWorld()) return;

    const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
    const auto DestroyedObstaclesData = GameMode->GetDestroyedObstaclesData();
    
    const auto MinDestroyedObstaclesCount = DestroyedObstaclesData.MinObstaclesCount;
    const auto MaxDestroyedObstaclesCount = DestroyedObstaclesData.MaxObstaclesCount;
    const auto MinDestroyedSmallObstaclesCount = DestroyedObstaclesData.MinSmallObstaclesCount;
    const auto MaxDestroyedSmallObstaclesCount = DestroyedObstaclesData.MaxSmallObstaclesCount;
    
    RandomDestroyObstacles(LeftSideObstacles, MinDestroyedObstaclesCount, MaxDestroyedObstaclesCount);
    RandomDestroyObstacles(CenterObstacles, MinDestroyedObstaclesCount, MaxDestroyedObstaclesCount);
    RandomDestroyObstacles(RightSideObstacles, MinDestroyedObstaclesCount, MaxDestroyedObstaclesCount);

    RandomDestroyObstacles(SmallObstacles, MinDestroyedSmallObstaclesCount, MaxDestroyedSmallObstaclesCount);
}

void AHNCaveTile::DestroyObstacles(TArray<UStaticMeshComponent*> Obstacles)
{
    for (const auto Obstacle : Obstacles)
    {
        Obstacle->DestroyComponent();
    }
    Obstacles.Empty();
}

void AHNCaveTile::DestroyAllObstacles()
{
    DestroyObstacles(LeftSideObstacles);
    DestroyObstacles(CenterObstacles);
    DestroyObstacles(RightSideObstacles);
    DestroyObstacles(SmallObstacles);
}

TArray<UStaticMeshComponent*> AHNCaveTile::AddObstacleMeshes(int32 Count, const FString PrefixName)
{
    TArray<UStaticMeshComponent*> ObstacleMeshes;
    
    for (int32 i = 0; i < Count; i++)
    {
        const auto StringName = FString::Printf(TEXT("%s Obstacle %i"), *PrefixName, i);
        const auto Name = FName(*StringName);
        const auto ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(Name);
        ObstacleMesh->SetupAttachment(RootComponent);
        ObstacleMeshes.Add(ObstacleMesh);
    }
    return ObstacleMeshes;
}

void AHNCaveTile::RandomDestroyObstacles(TArray<UStaticMeshComponent*> Obstacles, const int32 MinCount, const int32 MaxCount)
{
    const int32 DestroyCount = FMath::RandRange(MinCount, MaxCount);
    
    for (int i = 0; i < DestroyCount; i++)
    {
        const int32 DestroyNum = FMath::RandRange(0, Obstacles.Num() - 1);

        Obstacles[DestroyNum]->DestroyComponent();
        Obstacles.RemoveAt(DestroyNum);
    }
}

void AHNCaveTile::SetRandomCaveTileAngle()
{
    const auto RandomPitchRotation = FMath::FRandRange(-10.0f, 10.0f);
    const auto RandomYawRotation = FMath::FRandRange(-10.0f, 10.0f);
    TArray<AActor*> AttachedActors;
    GetAttachedActors(AttachedActors);
    
    const auto InitialTileRotation = GetActorRotation();
    const auto NewTileRotation = FRotator(InitialTileRotation.Pitch + RandomPitchRotation,
        InitialTileRotation.Yaw + RandomYawRotation, InitialTileRotation.Roll);
    
    SetActorRotation(NewTileRotation);
}

bool AHNCaveTile::CalculateRandomSpawnLocation(FVector& SpawnLocation)
{
    if (!SpawnVolume) return false;

    SpawnVolume->UpdateBounds();
    const FBoxSphereBounds BoxBounds = SpawnVolume->CalcLocalBounds();

    // Generate random point in local space
    const FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxBounds.BoxExtent);

    // Transform local random point to world space
    const auto Location = UKismetMathLibrary::TransformLocation(SpawnVolume->GetComponentTransform(), RandomPoint);
    
    SpawnLocation = Location;

    return true;
}