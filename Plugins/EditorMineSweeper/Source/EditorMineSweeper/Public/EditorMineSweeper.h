/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#pragma once

#include "CoreMinimal.h"

class FToolBarBuilder;
class FMenuBuilder;

class FEditorMineSweeperModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked();

private:

	/**
	* Called by the module to register the MineSweeper toolbar and drop down menu buttons
	*/
	void RegisterMenus();

	/**
	 * Static: Called by the module to register the MineSweeper tab with the tab manager
	 */
	static void RegisterTab();

	/**
	 * Static: Creates and returns a SDockTab shared reference. 
	 * This function can be used as a callback when registering a tab spawner with the tab manager.
	 */
	static TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);

	/** Reference to a command list, which we will use to store menu and toolbar items to functions*/
	TSharedPtr<class FUICommandList> PluginCommands;
};
