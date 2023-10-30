// Halloween Nightmare. All Rights Reserved.


#include "HNGameMode.h"
#include "Player/HNPlayer.h"
#include "Player/HNPlayerController.h"
#include "UI/HNGameHUD.h"
#include "Environment/HNCaveTile.h"

AHNGameMode::AHNGameMode()
{
    DefaultPawnClass = AHNPlayer::StaticClass();
    PlayerControllerClass = AHNPlayerController::StaticClass();
    HUDClass = AHNGameHUD::StaticClass();
}

AHNCaveTile* AHNGameMode::SpawnCaveTile(TSubclassOf<AHNCaveTile> CaveTileClass, FTransform AttachPointTransform)
{

    if (!GetWorld()) return nullptr;

    AHNCaveTile* CaveTile = GetWorld()->SpawnActor<AHNCaveTile>(CaveTileClass, AttachPointTransform);
/*
    GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Blue,
  FString::Printf(TEXT("AttachPointTransform Location: %s"), *AttachPointTransform.GetLocation().ToString()));
    
    GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Blue,
      FString::Printf(TEXT("Initial Location: %s"), *CaveTile->GetActorLocation().ToString()));
    
    const auto NewLocation = FVector(CaveTile->GetActorLocation().X, CaveTile->GetActorLocation().Y, 0.0f);

    GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Blue,
    FString::Printf(TEXT("Fixed Location: %s"), *NewLocation.ToString()));
    
    CaveTile->SetActorTransform(AttachPointTransform);
    */
    if (CaveTile)
    {
        PreviousCaveTile = CaveTile;
    }
    
    return CaveTile;
}

AHNCaveTile* AHNGameMode::RandomSpawnCaveTile()
{
    const auto RandomTileClassNum = FMath::RandRange(0, CaveTileClasses.Num() - 1);
    
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
        FString::Printf(TEXT("PreviousCaveTile name: %s"), *PreviousCaveTile->GetName()));

    
    return SpawnCaveTile(CaveTileClasses[RandomTileClassNum], PreviousCaveTile->GetAttachTransform());
}

void AHNGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnCaveTile(StraightCaveTileClass, FTransform(FVector(0,0,0)));
}