/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#pragma once

#include "CoreMinimal.h"

namespace MineSweeper
{
	// used to mark a game tile as safe or bomb
	enum TileType
	{
		Safe,
		Bomb
	};
}

class SMinefield;

/**
* A STile widget represents a single tile/cell of the minesweeper game
* It can be a safe tile, or a bomb tile.
*/

class EDITORMINESWEEPER_API STile : public SCompoundWidget
{
public:

	/**
	* Arguments are:
	*	- the tile type (safe or bomb)
	*	- XY coordinates of the tile within the minefield
	*/
	SLATE_BEGIN_ARGS(STile)
        : _TileType(MineSweeper::TileType::Safe)
        , _X(-1)
		, _Y(-1)
	{ }

	SLATE_ARGUMENT(MineSweeper::TileType, TileType)
    SLATE_ARGUMENT(int, X)
	SLATE_ARGUMENT(int, Y)
 
    SLATE_END_ARGS()
	
	STile();
	~STile();

	// Required
	void Construct(const FArguments& InArgs);


	/**
	* Returns the type of this tile.
	*
	* @return MineSweeper::TileType the type of this tile.
	*/
	MineSweeper::TileType GetTileType() const;


	/**
	* Sets the owning minefield for this tile
	*
	* @param InMinefield the minefield owning this tile.
	*/
	void SetOwningMinefield(TSharedPtr<SMinefield> InMinefield);

	/**
	* Sets the tile type for this tile
	*
	* @param InTileType tile type for this tile
	*/
	void SetTileType(MineSweeper::TileType InTileType);

	/**
	* Tries to trigger all the adjacent tiles.
	* It will also update this tile text to show the number of bombs surrounding it
	*/
	void TriggerAdjacentTiles() const;

	/**
	* Noticing this tile that it has been triggered by another tile, and not from the user
	*/
	bool TriggeredFromAnotherTile();

	/**
	* Disables the tile. Useful when the tile has been triggered, or the game is over.
	*/
	void DisableTile() const;

	/**
	* Triggers the tile.
	* This will disable the tile, and evaluate if the game has been won or lost.
	*/
	void Trigger();

private:

	/**
	* Called when the tile button has been clicked by the user.
	* It will trigger the tile, and try to trigger the adjacent ones.
	*/
	FReply OnClicked();

	/** The type of this tile */
	MineSweeper::TileType TileType = MineSweeper::TileType::Safe;

	/** X coordinate of this tile within its minefield*/
	int X = -1;
	
	/** Y coordinate of this tile within its minefield*/
	int Y = -1;

	/** flags if this tile has already been triggered or not*/
	bool bHasBeenTriggered = false;	

	/** A reference to this tile owning minefield. That would be the minefield which instantiated this tile*/
	TSharedPtr<SMinefield> OwningMinefield = nullptr;

	/** A reference to the button used to interact with this tile*/
	TSharedPtr<SButton> Button = nullptr;

	/** A reference to the text block used to show information about this tile to the user*/
	TSharedPtr<STextBlock> BombsCounterText = nullptr;


	
};

