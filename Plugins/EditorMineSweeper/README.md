# Unreal Editor Mine Sweeper Plugin
A rough implementation of the classic *Mine Sweeper* game, running within an Unreal Editor tab.

## Comments
Most functionalities are there, but the layout is definitely not the best!

## Installation + Compiling
A C++ Unreal project is required. 
In order to use the EditorMineSweeper Plugin, download the project folder from this repository and put it in your project's Plugins folder (create one if your project is currently not using any plugin).
This should result in a folder structure like the following: `MY_PROJECT/Plugins/EditorMineSweeper`.

You then need to (re) compile your unreal project. 
If you are using Visual Studio or Rider to compile, you have to `regenerate your Visual Studio project from your *.uproject file` to update it with the new source you just added. 
If you instead are using the command line to compile, for example with a batch script like the ones described by Alex Forsythe [here](https://www.youtube.com/watch?v=94FvzO1HVzY), then you can skip the regeneration step and compile straight ahead.

## Using the Plugin / Playing the game
Once the plugin has been compiled and the editor has been started, you can click on the bomb shaped toolbar button to open the in-editor game tab.
From there, you can already play a game, or set the minefield width, height and bomb number parameters to values of your choice, and click the "Generate new minefield" button to start a game with the specified settings.

There are some hardcoded limitations to the settings you can provide:
- max width = 10
- max height = 10

You can change the value, which is shared for width and height, in the [SMineSweeperWidget.h](Source/EditorMineSweeper/Private/Widgets/SMineSweeperWidget.h#L69) file.



## Tested
Windows 10 + Unreal Engine 4.26.2

## ToDo
- Improve layout
- Adding custom graphics for buttons and tiles
- TBD

## Known Bugs
- When the game is finished (win or lose), popup message appears before the tiles type is revealed (it should be the other way around)

## Acknowledgements
- [UE4 Enhanced Output Log Plugin](https://github.com/Cultrarius/UE4_MagicConsole) for a reference on Slate Widgets. 
- Various online resources from forums and blogs have been used, together with some examples from UE4 source.
- Minesweeper game :)

___
This plugin has been developed by [Dario Mazzanti](https://www.dariomazzanti.com).  
*This README file was last updated on 2021-08-04 by Dario Mazzanti.*
