# Introduction

This is the ButtonUp! project for Nathan Furnal (55803). You can find more
information about the code in the following points. More explanation about how
to play the game can be found in the `DOC.md` file.

# Core
This section of the code contains the core logic of the game. It implements the
building blocks of the game and packages it in a library to be used in the
various UI's.
# TUI
A textual interface for the game, it reads from `stdin` and writes to
`stdout`. For a proper experience, a terminal supporting Unicode is required.
# GUI
A Qt GUI for the game, it is implemented as a 2D view of the buttons. The
players are first prompted to choose to first player and then clicking anywhere
within a column will move the buttons (following the rules of course!). End of
round and end of game management is available.
# Test
Tests the core functionalities of the game by checking that the moves are
properly implemented and walking through a game step by step to check that all
specific cases are handled.
