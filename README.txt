================================================================================

Sonic Game
========
by: Hof Ronis 

================================================================================

Description
===========
I developed the game Sonic with C++ using "SFML". 

instructions
============

joystick:

use "Left" and "Right" buttons to move left and right.
use "Space" button to jump.
use "Escape" to pause.

kill/ die:

in collision between Sonic and enemy:
if the player jumps the Sonic kills the enemy, 
otherwise the enemy kills the player.

Complete level:

In order to complete a level the player needs to collect all the diamonds in the current level, 
the diamonds number will be displayed in the status bar.

================================================================================

classes
==============

1) GameManager.cpp - this class is responsible of all the other classes, it managing  all thing related to the game.
2) Menu.cpp - it responsible of presenting the menu in the game.
3) GameStatus.cpp- it responsible of the user game data like score and lives.
4) ResourceManager.cpp - it responsible of loading pictures and audio.
5) StageLoader.cpp- it responsible of loading levels, it holds the number of rows,cols and the number of diamonds in the level.
6) Collisions.h - manage all the collisions using multy dispach patern.
7) Constants.h - contain constants.

8) GameObject.cpp - all the objects shown on map.
9) DynamicGameObject.cpp - all of moving objects.
10) character.cpp - abstruct class off "living" objects.
11) Sonic.cpp - the player class, can move, draw and manage itself
12) Enemy.cpp - moving enemys on the map.
13,14,15) Beatle.cpp, Crabb.cpp, Boss.cpp - all kinds of enemys (Boss is the smart enemy).
16) StaticGameObject.cpp - static/non moving objects on the map.
17,18) Grass.cpp, Wall.cpp - static items on the map.
19) Collectable.cpp - items that collected by Sonic.
20) Ring.cpp - add score to Sonic.
21) Diamond.cpp - add score to Sonic and a collected in order to complete levels.

22) SonicState.cpp - a design paterns of states to move the Sonic efficiently.
23,24,25,26) WalkLeftState.cpp, WalkRightState.cpp, JumpState.cpp, standingState.cpp -all the options of moving the Sonic with States.
 
27) FactoryEnemy.cpp - a design patern that help to create an Enemy object
28) FactoryStatic.cpp - a design patern that help to create a Static object

29) main.cpp - for running the game.


Design paterns
==============
Singleton(ResourceManager), States design, Factory, Multy Dispach

================================================================================

Levels Format
============================
The format is "level"+ "number of stage"+ ".txt"

================================================================================

Data Structures
===================
2d vector of unique ptr's which hold the static objects, 
and vector that hold the dynamic objects.

================================================================================

Known bugs
=========
In some cases there is a problem with the collide between Sonic and right Wall.

In some computers visual studio can't open the background image so the exeption in the ResourceManager need to be deleted
or you need to load another image for the background.

================================================================================

