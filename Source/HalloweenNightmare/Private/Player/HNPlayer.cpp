// Halloween Nightmare. All Rights Reserved.


#include "Player/HNPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/HNPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HNGameMode.h"

// Sets default values
AHNPlayer::AHNPlayer()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    // Rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = true;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = false;            // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;

    // Increase breaking factor
    GetCharacterMovement()->BrakingFrictionFactor = 20.0f;
    
    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxFlySpeed = 800.0f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;       // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    
    // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    
    SetActorTickEnabled(true);
}

// Called when the game starts or when spawned
void AHNPlayer::BeginPlay()
{
    Super::BeginPlay();

    //Add Input Mapping Context
    if (const AHNPlayerController* PlayerController = GetPlayerController())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHNPlayer::OnCollision);
}

void AHNPlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    MoveForward();
}

AHNPlayerController* AHNPlayer::GetPlayerController() const
{
    if (!Controller) return nullptr;

    return Cast<AHNPlayerController>(Controller);
    
}

void AHNPlayer::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    // if (OverlappedComponent->GetName() != "Cave Trigger Box") return;
    
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Collision"));

    const auto GameMod = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
    GameMod->RandomSpawnCaveTile();
}

void AHNPlayer::MoveRight(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    AddMovementInput(GetActorRightVector(), InputValue);
}

void AHNPlayer::MoveUp(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    AddMovementInput(GetActorUpVector(), InputValue);
}

void AHNPlayer::MoveForward()
{
   AddMovementInput(GetActorForwardVector(), 1.0f);
}

void AHNPlayer::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (GetPlayerController() != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

// Called to bind functionality to input
void AHNPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AHNPlayer::MoveRight);
        EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &AHNPlayer::MoveUp);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHNPlayer::Look);
    }
}