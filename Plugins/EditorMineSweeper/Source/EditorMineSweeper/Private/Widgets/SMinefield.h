/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#pragma once

#include "CoreMinimal.h"
#include "STile.h"

#include "Widgets/Layout/SGridPanel.h"
#include "SlateBasics.h"


namespace MineSweeper
{
	enum GameState
	{
		Playing,
        Win,
		Lose
    };

	static const FText WinMessage = FText::FromString(TEXT("You Won! Click Ok to play again."));
	static const FText LoseMessage = FText::FromString(TEXT("You Lost! Click Ok to play again."));
}

/**
* A SMinefield represents the mine sweeper game field.
* The SMinefield widget instantiates a grid of STile widgets, representing the game cells (safe or bomb)
*/
class EDITORMINESWEEPER_API SMinefield : public SCompoundWidget
{
public:

	/**
	* Arguments are:
	*	- width and height of the minefield
	*	- number of desired bombs
	*/
	SLATE_BEGIN_ARGS(SMinefield)
        : _Width(3)
        , _Height(4)
		, _BombCount(3)
	{ }

	SLATE_ARGUMENT(int, Width)
    SLATE_ARGUMENT(int, Height)
	SLATE_ARGUMENT(int, BombCount)
 
    SLATE_END_ARGS()
	
	SMinefield();
	~SMinefield();


	// Required
	void Construct(const FArguments& InArgs);

	
	/**
	* Creates a new minefield. It basically starts a new game.
	*
	* @param InWidth the minefield width.
	* @param InHeight the minefield height.
	* @param InBombCount the number of bombs to place throughout the minefield.
	*/
	void SetupTiles(int InWidth, int InHeight, int InBombCount);

	/**
	* Trigger this function when a tile of the specified type has been clicked.
	* It will evaluate if the game has been won.
	*
	* @param InTileType the number of bombs to place throughout the minefield.
	*/
	void OnTileClicked(MineSweeper::TileType InTileType);

	/**
	* Evaluates if the specified tile is valid or not
	*
	* @param InX the tile X coordinate
	* @param InY the tile Y coordinate
	*
	* @return bool if the tile is valid or not
	*/
	bool IsTileValid(int InX, int InY) const;


	/**
	* Returns the specified tile.
	* Check if the tile is valid before using the IsTileValid method
	*
	* @param InX the tile X coordinate
	* @param InY the tile Y coordinate
	*
	* @return TSharedPtr<STile> the tile reference
	*/
	TSharedPtr<STile> GetTile(int InX, int InY);

	/**
	* Disables the entire game field
	*/
	void TriggerAndDisableAllTiles();

	/**
	* Cleans up the game and shows a popup telling the user if they won or lost
	*/
	void FinishGame(MineSweeper::GameState InGameState);


	/**
	* Called when the game has been lost
	*/
	void OnGameLost();

	/**
	* Called when the game has been won
	*/
	void OnGameWon();

private:

	/** The width of the minefield*/
	int Width = -1;

	/** The height of the minefield*/
	int Height = -1;

	/** The number of bombs present in the minefield*/
	int BombCount = -1;

	/** The number of safe tiles the player has to trigger in order to win*/
	int RemainingTilesToWin = -1;

	/** The current state of the game*/
	MineSweeper::GameState GameState = MineSweeper::Playing;

	/** A reference to the uniform grid panel used to store the tiles */
	TSharedPtr<SUniformGridPanel> TilesUniformGrid;

	/** A matrix of STile elements, to be accessed using XY coordinates */
	TArray<TArray<TSharedPtr<STile>>> GameTiles;

};
