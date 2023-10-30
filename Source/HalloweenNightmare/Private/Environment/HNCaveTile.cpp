// Halloween Nightmare. All Rights Reserved.


#include "Environment/HNCaveTile.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

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

    AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AtachPoint"));
    AttachPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHNCaveTile::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AHNCaveTile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}