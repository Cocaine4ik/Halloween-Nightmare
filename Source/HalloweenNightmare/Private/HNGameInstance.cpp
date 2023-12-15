// Halloween Nightmare. All Rights Reserved.


#include "HNGameInstance.h"

FName UHNGameInstance::GetUserName() const
{
    if (const auto HNUserNameDataAsset = Cast<UHNUserNameDataAsset>(UserNameDataAsset))
    {
        
        return HNUserNameDataAsset->GetUserName();
    }

    return FName("User");
}

void UHNGameInstance::SetUserName(const FName Name)
{
    if (const auto HNUserNameDataAsset = Cast<UHNUserNameDataAsset>(UserNameDataAsset))
    {
        HNUserNameDataAsset->SetUserName(Name);
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