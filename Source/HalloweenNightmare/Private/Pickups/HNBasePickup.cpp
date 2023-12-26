// Halloween Nightmare. All Rights Reserved.


#include "Pickups/HNBasePickup.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HNPlayer.h"
#include "Sound/SoundCue.h"

AHNBasePickup::AHNBasePickup()
{
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    MeshComponent->SetupAttachment(RootComponent);
    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    CollisionComponent->SetupAttachment(RootComponent);
    
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHNBasePickup::BeginPlay()
{
    Super::BeginPlay();

    GenerateRandomRotationYaw();
    SetActorInitialLocation();
}

void AHNBasePickup::Invoke()
{
}

void AHNBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    Player = Cast<AHNPlayer>(OtherActor);
    if (Player)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnTakenSound, GetActorLocation());
        
        Invoke();
        Player = nullptr;
        Destroy();
    }

}

void AHNBasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);
    
        Destroy();
}

// Called every frame
void AHNBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RotateYawActor();
    LiftActor();
}

void AHNBasePickup::GenerateRandomRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    const auto Speed = FMath::FRandRange(MinRotationYawSpeed, MaxRotationYawSpeed);
    
    RotationYaw = Direction * Speed;
}

void AHNBasePickup::RotateYawActor()
{
    if (!bHaveRotation) return;
    
    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void AHNBasePickup::LiftActor()
{
    if (!bHaveLift) return;
    
    const float CurrentActorLocationZ = GetActorLocation().Z;


    if (LiftUp)
    {
        SetActorLocation(FVector(InitialLocation.X, InitialLocation.Y, CurrentActorLocationZ + LiftSpeed));
        if (CurrentActorLocationZ >= InitialLocation.Z + MaxLiftOffset)
        {
            LiftUp = false;
        }
    }
    else if (!LiftUp)
    {
        SetActorLocation(FVector(InitialLocation.X, InitialLocation.Y, CurrentActorLocationZ - LiftSpeed));
        if (CurrentActorLocationZ <= InitialLocation.Z)
        {
            LiftUp = true;
        }
    }
}
