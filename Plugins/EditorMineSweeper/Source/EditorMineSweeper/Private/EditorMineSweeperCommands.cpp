/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#include "EditorMineSweeperCommands.h"

#define LOCTEXT_NAMESPACE "FEditorMineSweeperModule"

void FEditorMineSweeperCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "EditorMineSweeper", "Execute EditorMineSweeper action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
