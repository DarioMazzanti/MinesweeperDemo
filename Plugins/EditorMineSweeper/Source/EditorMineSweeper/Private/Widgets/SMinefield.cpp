/* 
 * Author: Dario Mazzanti (darmaz@gmail.com), 2021
 */

#include "SMinefield.h"
//#include "Components/GridPanel.h"

SMinefield::SMinefield()
{
}

SMinefield::~SMinefield()
{
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMinefield::Construct(const FArguments& InArgs)
{	
	Width = InArgs._Width;
	Height = InArgs._Height;
	BombCount = InArgs._BombCount;

	// creating an empty uniform grid panel, which will contain the tiles defining the minefield
	ChildSlot
    [
		SAssignNew(TilesUniformGrid, SUniformGridPanel)
		.MinDesiredSlotHeight(20)
		.MinDesiredSlotWidth(20)
		
    ]
	.Padding(FSizeParam::SizeRule_Stretch);
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMinefield::SetupTiles(int InWidth, int InHeight, int InBombCount)
{
	Width = InWidth;
	Height = InHeight;
	BombCount = InBombCount;

	// compute the number of tiles, and subtract the bomb count: this will give us the number of safe tiles
	RemainingTilesToWin = (Width * Height) - BombCount;
	
	GameState = MineSweeper::GameState::Playing;

	// resetting the minefield
	TilesUniformGrid->ClearChildren();
	GameTiles.Empty();

	for(int x = 0; x < Width; x++)
	{
		// a column of our minefield, made of STile widgets
		TArray<TSharedPtr<STile>> NewColumn;

		// filling the column with new tiles
		for(int y = 0; y < Height; y++)
		{
			TSharedPtr<STile> NewTile;
			
			// create the tile, and add it as a slot to the minefield uniform grid
			TilesUniformGrid->AddSlot(x, y)
            [
                SAssignNew(NewTile, STile)
                .X(x)
                .Y(y)
            ];

			// set the owning minefield for the newly created tile
			NewTile->SetOwningMinefield(SharedThis(this));

			// add the new tile to the column
			NewColumn.Add(NewTile);
		}

		// ad the new column to the tiles matrix
		GameTiles.Add(NewColumn);
	}

	
	int CreatedBombs = 0;

	// randomly placing bombs throughout the minefield
	while(CreatedBombs < BombCount)
	{
		const int BombX = FMath::RandRange(0, Width - 1);
		const int BombY = FMath::RandRange(0, Height - 1);

		if(IsTileValid(BombX, BombY))
		{
			// this will avoid assigning a bomb twice to the same tile (X, Y), and should avoid an infinite while loop as well
			if(GetTile(BombX, BombY)->GetTileType() == MineSweeper::Safe)
			{
				GetTile(BombX, BombY)->SetTileType(MineSweeper::Bomb);
				CreatedBombs++;
			}
		}
	}

	// Note: this is not the most efficient solution, but scatters the bombs nicely.
	// For efficiency, we could randomly place the bombs in the nested for loops above, while building up the minefield, e.g. using FMath::RandBool(),
	// but the bombs distribution would be most likely concentrated at the top of the minefield
}

void SMinefield::OnTileClicked(MineSweeper::TileType InTileType)
{
	if(GameState == MineSweeper::GameState::Playing)
	{
		if(InTileType == MineSweeper::TileType::Safe)	
		{
			// the clicked tile is safe, so the player has to look for one tile less
			RemainingTilesToWin--;

			if(RemainingTilesToWin == 0)
				OnGameWon();
		}
		else
			OnGameLost();
	}
}

bool SMinefield::IsTileValid(int InX, int InY) const
{
	// check if the specified coordinates are within the acceptable range
	return (InX >= 0) && (InX < Width) &&
		(InY >= 0) && (InY < Height);
}

TSharedPtr<STile> SMinefield::GetTile(int InX, int InY)
{
	return GameTiles[InX][InY];
}

void SMinefield::TriggerAndDisableAllTiles()
{
	for (TArray<TSharedPtr<STile>> Row : GameTiles)
	{
		for (TSharedPtr<STile> Element : Row)
		{
			Element->Trigger();
			Element->DisableTile();
		}
	}
}

void SMinefield::FinishGame(MineSweeper::GameState InGameState)
{
	if(GameState == MineSweeper::GameState::Playing)
	{
		GameState = InGameState;
		
		TriggerAndDisableAllTiles();

		// display win/lose popup message
		if(InGameState == MineSweeper::Win)
			FMessageDialog::Open(EAppMsgType::Ok, MineSweeper::WinMessage);
		
		else if(InGameState == MineSweeper::Lose)
            FMessageDialog::Open(EAppMsgType::Ok, MineSweeper::LoseMessage);
	}
}

void SMinefield::OnGameLost()
{
	FinishGame(MineSweeper::Lose);
}

void SMinefield::OnGameWon()
{
	FinishGame(MineSweeper::Win);
}
