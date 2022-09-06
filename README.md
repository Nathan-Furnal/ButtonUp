# Introduction

You can find more information about the code in this file. More explanation
about how to play the game can be found in the `DOC.md` file. More details about
the design choices and algorithm can be found in the `Report.pdf` file.

# Demo

Here's a demo of the game with a few rounds until one player wins the game.



https://user-images.githubusercontent.com/45597572/188702889-82320d6a-2496-427c-8316-1fcb51489506.mp4



# Core
This section of the code contains the core logic of the game. It implements the
building blocks of the game and packages it in a library to be used in the
various UI's.
# TUI
A textual interface for the game, it reads from `stdin` and writes to
`stdout`. For a proper experience, a terminal supporting Unicode is required. If
you are on Windows, you need to [use the following
hack](https://stackoverflow.com/questions/57131654/using-utf-8-encoding-chcp-65001-in-command-prompt-windows-powershell-window/57134096#57134096)
to get Unicode support.

For proper ANSI code support, a Windows registry might need to be modified. One needs
to run (in the explorer) `regedit`, and navigate to
`HKEY_CURRENT_USER\Console`. There, either modify the `VirtualTerminalLevel`
registry to 1 or create it with a right click and set it to be a `DWORD`, then
name it `VirtualTerminalLevel` and set it to 1. [See here for more
info](https://ss64.com/nt/syntax-ansi.html).

Note that it is not necessary on Linux.
# GUI
A Qt GUI for the game, it is implemented as a 2D view of the buttons. The
players are first prompted to choose to first player and then clicking anywhere
within a column will move the buttons (following the rules of course!). End of
round and end of game management is available.
# Test
Tests the core functionalities of the game by checking that the moves are
properly implemented and walking through a game step by step to check that all
specific cases are handled.
# Design patterns

The more obvious choice for the TUI was using the MVC with a bit of the Observer
pattern. In short, the model has the core logic, the view manages I/O and the
controller parses the input from the view and has the model react
accordingly. The observer pattern is used to update the view when the model is
changed.

In the GUI, it's a bit different since Qt offers the possibility of the
Model-View pattern and there's no need to implement the Observer pattern from
scratch as we can use signal and slots instead, which more or less equivalent to
the notify/update found in the observer pattern.
