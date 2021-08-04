/* 
* Author: Dario Mazzanti (darmaz@gmail.com), 2021
*/

#include "EditorMineSweeper.h"
#include "EditorMineSweeperStyle.h"
#include "EditorMineSweeperCommands.h"
#include "Widgets/SMineSweeperWidget.h"

#include "ToolMenus.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FEditorMineSweeperModule"

// a namespace to easily access and modify some settings
namespace EditorMineSweeperModule
{
    static const FName MineSweeperTabName = FName(TEXT("MineSweeperTab"));
	static const FName MenuPlacement = FName(TEXT("LevelEditor.MainMenu.Window"));
	static const FName MenuSection = FName(TEXT("Fun"));
	static const FName ToolbarPlacement = FName(TEXT("LevelEditor.LevelEditorToolBar"));
	
	static const FText DisplayName = FText::FromString("Mine Sweeper");
	static const FText TooltipText = FText::FromString("Open Mine Sweeper Tab");

	static const int DefaultWidth = 4;
	static const int DefaultHeight = 4;
	static const int DefaultBombsNumber = 3;
}

void FEditorMineSweeperModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FEditorMineSweeperStyle::Initialize();
	FEditorMineSweeperStyle::ReloadTextures();

	FEditorMineSweeperCommands::Register();

	// registering our custom nomad tab, so we can spawn it when we need it
	RegisterTab();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorMineSweeperCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FEditorMineSweeperModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEditorMineSweeperModule::RegisterMenus));
}

void FEditorMineSweeperModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorMineSweeperModule::MineSweeperTabName);
	}

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEditorMineSweeperStyle::Shutdown();

	FEditorMineSweeperCommands::Unregister();
}


TSharedRef<SDockTab> FEditorMineSweeperModule::SpawnTab(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(EditorMineSweeperModule::DisplayName)
		.ToolTipText(EditorMineSweeperModule::TooltipText)
		[
            SNew(SMineSweeperWidget)
            .Width(EditorMineSweeperModule::DefaultWidth)
            .Height(EditorMineSweeperModule::DefaultHeight)
            .BombsNumber(EditorMineSweeperModule::DefaultBombsNumber)
        ];
}


void FEditorMineSweeperModule::PluginButtonClicked()
{
	// when cliccking the toolbar button, we try to spawn the minesweeper tab
	FGlobalTabmanager::Get()->TryInvokeTab(EditorMineSweeperModule::MineSweeperTabName);
}

void FEditorMineSweeperModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		// adding a drop down editor menu item 
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(EditorMineSweeperModule::MenuPlacement);
		{
			FToolMenuSection& Section = Menu->FindOrAddSection(EditorMineSweeperModule::MenuSection);
			Section.AddMenuEntryWithCommandList(FEditorMineSweeperCommands::Get().PluginAction, PluginCommands);
		}

		// adding a toolbar button
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(EditorMineSweeperModule::ToolbarPlacement);
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection(EditorMineSweeperModule::MenuSection);
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorMineSweeperCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FEditorMineSweeperModule::RegisterTab()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EditorMineSweeperModule::MineSweeperTabName, FOnSpawnTab::CreateStatic(&FEditorMineSweeperModule::SpawnTab))
        .SetDisplayName(EditorMineSweeperModule::DisplayName)
        .SetTooltipText(EditorMineSweeperModule::TooltipText)
        .SetGroup(WorkspaceMenu::GetMenuStructure().GetToolsCategory())
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "Toolbar.Icon"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorMineSweeperModule, EditorMineSweeper)
