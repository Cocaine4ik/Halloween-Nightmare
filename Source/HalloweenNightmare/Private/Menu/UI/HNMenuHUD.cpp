// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AHNMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {

        if (const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass))
        {
            MenuWidget->AddToViewport();
        }
    }
}