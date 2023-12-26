// Halloween Nightmare. All Rights Reserved.


#include "UI/HNTextButtonWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"

void UHNTextButtonWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    DefaultTextColor = TextBlock->GetColorAndOpacity();
}

void UHNTextButtonWidget::SetTextHoverColor()
{
    SetTextColor(HoverColor);
}

void UHNTextButtonWidget::SetTextDefaultColor()
{
    SetTextColor(DefaultTextColor);
}

void UHNTextButtonWidget::SetTextColor(FSlateColor Color)
{
    TextBlock->SetColorAndOpacity(Color);
}