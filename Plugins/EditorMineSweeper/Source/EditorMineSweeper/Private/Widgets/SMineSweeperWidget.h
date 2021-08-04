/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#pragma once

#include "CoreMinimal.h"
#include "SMinefield.h"

/**
* A SMineSweeperWidget represents the mine sweeper game, including the minefield and the interface.
*/


class EDITORMINESWEEPER_API SMineSweeperWidget  : public SCompoundWidget
{

public:

	/**
	* Arguments are:
	*	- width and height of the minefield
	*	- number of desired bombs
	*/
	SLATE_BEGIN_ARGS(SMineSweeperWidget)
		: _Width(3)
		, _Height(4)
		, _BombsNumber(3)
	{ }

	SLATE_ARGUMENT(int, Width)
	SLATE_ARGUMENT(int, Height)
	SLATE_ARGUMENT(int, BombsNumber)
 
    SLATE_END_ARGS()
	
	SMineSweeperWidget();
	~SMineSweeperWidget();

	// Required
	void Construct(const FArguments& InArgs);


private:

	/**
	* Called when the generate game button has been clicked by the user.
	* It will trigger the creation of a new minefield, essentially starting a new game
	*/
	FReply OnGenerateButtonClicked();
	
	/** A reference to the minefield widget */
	TSharedPtr<SMinefield> Minefield;

	/** A reference to the text box widget used to set the minefield width*/
	TSharedPtr<SEditableTextBox> WidthTextBlock;

	/** A reference to the text box widget used to set the minefield height*/
	TSharedPtr<SEditableTextBox> HeightTextBlock;

	/** A reference to the text box widget used to set the minefield bombs number*/
	TSharedPtr<SEditableTextBox> BombsTextBlock;


	int Width = -1;
	int Height = -1;
	int BombsNumber = -1;

	const int MINEFIELD_MAX_EDGE = 10;
};
