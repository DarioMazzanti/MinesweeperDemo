/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#include "STile.h"
#include "SMinefield.h"
#include "SlateBasics.h"

STile::STile()
{
}

STile::~STile()
{
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STile::Construct(const FArguments& InArgs)
{
	// storing arguments
	TileType = InArgs._TileType;
	X = InArgs._X;
	Y = InArgs._Y;

	// creating the actual widget
	ChildSlot
	[
   		SAssignNew(Button, SButton)
			.ToolTipText(FText::FromString("Is this a bomb?"))
			.OnClicked(this, &STile::OnClicked)// assigns STile::OnClicked delegate to button OnClicked
			[
				SAssignNew(BombsCounterText, STextBlock)
					.MinDesiredWidth(20)
					.Text(FText::FromString("?"))
            ]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

MineSweeper::TileType STile::GetTileType() const
{
	return TileType;
}

void STile::SetOwningMinefield(TSharedPtr<SMinefield> InMinefield)
{
	OwningMinefield = InMinefield;
}

void STile::SetTileType(MineSweeper::TileType InTileType)
{
	TileType = InTileType;
}

void STile::TriggerAdjacentTiles() const
{
	// keeps track of the number of surrounding bombs
	int SurroundingBombsNum = 0;

	// cycle through all surrounding tiles, including self
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		{
			// if tile is not self and valid, let's try to trigger it
			if( !(i == 0 && j==0) )
				if (OwningMinefield->IsTileValid (X+i, Y+j))
				{
					// get a reference to the tile, in order to trigger it
					const TSharedPtr<STile> CurrentTile = OwningMinefield->GetTile(X+i, Y+j);

					// returns true if CurrentTile is a bomb
					const bool bIsBomb = CurrentTile->TriggeredFromAnotherTile(); 
					
					if(bIsBomb)
						SurroundingBombsNum++;
				}
		}

	// display the number of surrounding bombs on the tile interface
	BombsCounterText->SetText(FText::FromString(FString::FromInt(SurroundingBombsNum)));
}

// returns true if this tile is a bomb
bool STile::TriggeredFromAnotherTile()
{
	// if the tile is a bomb, we don't trigger it
	if(TileType == MineSweeper::Bomb)	
		return true;
	
	// triggering the tile
	Trigger();

	return false;
}

void STile::DisableTile() const
{
	Button->SetEnabled(false);
}

void STile::Trigger()
{
	if(!bHasBeenTriggered)
	{
		bHasBeenTriggered = true;

		// give a red tint to the tile, if the tile is a bomb
		if(TileType == MineSweeper::TileType::Bomb)			
			Button->SetBorderBackgroundColor(FLinearColor::Red);

		DisableTile();		
	
		if(OwningMinefield.IsValid())		
			OwningMinefield->OnTileClicked(TileType);			
	}
}

FReply STile::OnClicked()
{
	Trigger();
	TriggerAdjacentTiles();
	
	return FReply::Handled();
}
