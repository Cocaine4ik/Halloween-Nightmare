// Halloween Nightmare. All Rights Reserved.


#include "HNGameInstance.h"

#include "HNSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UHNGameInstance::Init()
{
    Super::Init();

    OnSaveUserName.AddUObject(this, &UHNGameInstance::SaveUserName);
    OnSaveScores.AddUObject(this, &UHNGameInstance::SaveScores);

    // Load username from save file if it possible
    if (const auto SaveGame = LoadGame())
    {
        UserName = SaveGame->GetUserName();
    }
}

FName UHNGameInstance::GetLevelName() const
{
    FName Name("Default");
    
    switch (CurrentLevel)
    {
        case EHNLevel::Hard: Name = "Hard"; break;
        case EHNLevel::Nightmare: Name = "Nightmare"; break;
    }
    return Name;
}

void UHNGameInstance::CreateSaveFile()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple,
FString::Printf(TEXT("CreateSaveFile")));
    
    if (UHNSaveGame* HNSaveGame = Cast<UHNSaveGame>(UGameplayStatics::CreateSaveGameObject(UHNSaveGame::StaticClass())))
    {
        UGameplayStatics::SaveGameToSlot(HNSaveGame, "Slot1", 0);
    }
    
}

void UHNGameInstance::SaveUserName(FName Name)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple,
FString::Printf(TEXT("SaveUserName")));
    
    if (UHNSaveGame* HNSaveGame = LoadGame())
    {
        HNSaveGame->SetUserName(Name);
        SaveGame(HNSaveGame);
    }
    else
    {
        CreateSaveFile();
        SaveUserName(Name);
    }
}

void UHNGameInstance::SaveScores(const FHNScoresData& ScoresData)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple,
FString::Printf(TEXT("SaveScores")));
    
    if (UHNSaveGame* HNSaveGame = LoadGame())
    {
        HNSaveGame->AddScoresData(ScoresData);
        SaveGame(HNSaveGame);
    }
    else
    {
        CreateSaveFile();
        SaveScores(ScoresData);
    }
}

void UHNGameInstance::SaveGame(UHNSaveGame* SaveGame)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple,
FString::Printf(TEXT("SaveGame")));
    
    UGameplayStatics::SaveGameToSlot(SaveGame, "Slot1", 0);
}

UHNSaveGame* UHNGameInstance::LoadGame() const
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple,
FString::Printf(TEXT("LoadGame")));
    
    return Cast<UHNSaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
}