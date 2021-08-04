/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/


#include "SMineSweeperWidget.h"
#include "SlateBasics.h"

SMineSweeperWidget::SMineSweeperWidget()
{
}

SMineSweeperWidget::~SMineSweeperWidget()
{
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMineSweeperWidget::Construct(const FArguments& InArgs)
{
    Width = InArgs._Width;
    Height = InArgs._Height;
    BombsNumber = InArgs._BombsNumber;

    // creating the game widgets
    ChildSlot
    [
        SNew( SVerticalBox )
            + SVerticalBox::Slot()
            .VAlign( VAlign_Center )
            .HAlign( HAlign_Center )
            [
                SNew( SHorizontalBox )
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Center )
                        .AutoWidth()
                    [
                        SNew( STextBlock )
                            .AutoWrapText(true)
                            .Text( FText::FromString( "Desired width: " ) )
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Fill )
                        .AutoWidth()
                    [
                        SAssignNew(WidthTextBlock, SEditableTextBox)
                            .Text( FText::FromString(FString::FromInt(Width)) )
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Center )
                        .AutoWidth()
                    [
                        SNew( SSpacer )
                             .Size(FVector2D(5, 5))
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Center )
                        .AutoWidth()
                    [
                        SNew( STextBlock )
                            .AutoWrapText(true)
                            .Text( FText::FromString( "Desired height: " ) )
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Fill )
                        .AutoWidth()
                    [
                        SAssignNew(HeightTextBlock, SEditableTextBox)
                            .Text( FText::FromString(FString::FromInt(Height)))
                    ]
                    + SHorizontalBox::Slot()
                       .VAlign( VAlign_Center )
                       .HAlign( HAlign_Center )
                       .AutoWidth()
                    [
                       SNew( SSpacer )
                            .Size(FVector2D(10, 5))
                    ]
                ]
                
            + SVerticalBox::Slot()
            .VAlign( VAlign_Center )
            .HAlign( HAlign_Center )
            [
                SNew( SHorizontalBox )
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Center )
                        .AutoWidth()
                    [
                        SNew( STextBlock )
                            .AutoWrapText(true)
                            .Text( FText::FromString( "Desired bombs number " ) )
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Fill )
                        .AutoWidth()
                    [
                        SAssignNew(BombsTextBlock, SEditableTextBox)
                            .Text( FText::FromString(FString::FromInt(BombsNumber)) )
                    ]
                    + SHorizontalBox::Slot()
                        .VAlign( VAlign_Center )
                        .HAlign( HAlign_Center )
                        .AutoWidth()
                    [
                        SNew( SSpacer )
                             .Size(FVector2D(10, 5))
                    ]
            ]

            + SVerticalBox::Slot()
            .VAlign( VAlign_Center )
            .HAlign( HAlign_Center)
            .Padding(FSizeParam::SizeRule_Stretch)
            .AutoHeight()
            [
                SAssignNew(Minefield, SMinefield)
                    .Width(Width)
                    .Height(Height)
                    .BombCount(BombsNumber)
            ]

            + SVerticalBox::Slot()
            .VAlign( VAlign_Center )
            .HAlign( HAlign_Center )
            [
                SNew(SButton)
                 .VAlign(VAlign_Center)
                 .HAlign(HAlign_Center)
                 .Text(FText::FromString("Generate new minefield"))
                 .ToolTipText(FText::FromString("Click to generate a new minefield"))
                 .OnClicked(this, &SMineSweeperWidget::OnGenerateButtonClicked)
                 // assigns SMineSweeperWidget::OnGenerateButtonClicked() delegate to button OnClicked
            ]
            
            
    ]
    .VAlign( VAlign_Center )
    .HAlign( HAlign_Center )
    .Padding(FSizeParam::SizeRule_Auto);

    Minefield->SetupTiles(Width, Height, BombsNumber);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


FReply SMineSweeperWidget::OnGenerateButtonClicked()
{
    // WIDTH field, check if it is a number
    if(WidthTextBlock->GetText().IsNumeric())
    {
        // retrieve the actual number (todo: is there a nicer way?)
        const int NewWidth = FCString::Atoi(*WidthTextBlock->GetText().ToString());

        // if valid, let's store it
        if(NewWidth <= MINEFIELD_MAX_EDGE)
            Width = NewWidth;
    }

    // HEIGHT field, check if it is a number
    if(WidthTextBlock->GetText().IsNumeric())
    {
        // retrieve the actual number (todo: is there a nicer way?)
        const int NewHeight = FCString::Atoi(*HeightTextBlock->GetText().ToString());

        // if valid, let's store it
        if(NewHeight <= MINEFIELD_MAX_EDGE)
            Height = NewHeight;
    }

    // BOMBS field, check if it is a number
    if(BombsTextBlock->GetText().IsNumeric())
    {
        // retrieve the actual number (todo: is there a nicer way?)
        const int NewBombsNumber = FCString::Atoi(*BombsTextBlock->GetText().ToString());
        
        // if valid, let's store it (we are allowing the possibility of having 100% bombs!)
        if(NewBombsNumber <= Width*Height)
            BombsNumber = NewBombsNumber;
    }

    // refresh the text content for the three fields.
    WidthTextBlock->SetText(FText::FromString(FString::FromInt(Width)));
    HeightTextBlock->SetText(FText::FromString(FString::FromInt(Height)));
    BombsTextBlock->SetText(FText::FromString(FString::FromInt(BombsNumber)));

    // finally, generate a minefield, starting a new game
    Minefield->SetupTiles(Width, Height, BombsNumber);

    return FReply::Handled();    
}
