# EnigmaQuest

EnigmaQuest is a 2D Top-Down RPG built with **C++** and the **raylib** library. Players control a knight navigating an open-world environment, battling enemies such as goblins and slimes while navigating around various environmental obstacles.

## Features

* **Action Combat**: Engage enemies using a sword with directional swinging and knockback mechanics.
* **Animated Sprites**: Character animations for idle and running states for both the player and enemies.
* **Dynamic Health System**: Includes an "i-frame" (invincibility frame) system where the player's sprite flashes when taking damage.
* **Environment Interaction**: Collision detection with world props like rocks and logs, as well as defined map boundaries.
* **Audio**: Integrated background music that loops during gameplay.

## Controls

* **W/A/S/D**: Move the character.
* **Left Mouse Button**: Attack with your sword.

## Technical Overview

The project uses an object-oriented approach with several key classes:

* `BaseCharacter`: A parent class handling common logic like health, movement, and animation ticking.
* `Character`: The player-controlled entity that manages input handling and weapon mechanics.
* `Enemy`: AI-controlled entities (Goblin and Slime) that track the player's position to deal damage.
* `Prop`: Static environmental objects with collision boxes.

## Build Instructions

This project includes a `Makefile` configured for macOS (compatible with Homebrew installations of raylib).

### Prerequisites

* C++ Compiler (Clang or GCC)
* [raylib](https://www.raylib.com/) library

### Compilation

To build the release version, run:

```bash
make

```

To build the debug version with symbols and no optimization:

```bash
make BUILD_MODE=DEBUG

```

### Running the Game

Once compiled, run the executable:

```bash
./game

```

## Project Structure

* `main.cpp`: Entry point containing the game loop and initialization.
* `characters/`: Sprite sheets for player, enemies, and weapons.
* `nature_tileset/`: Map textures and environmental prop assets.
* `audio/`: Sound files for the game soundtrack.