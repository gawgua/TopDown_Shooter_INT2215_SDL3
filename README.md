# TopDown_Shooter_INT2215_SDL3

Project for INT2215 (Advanced Programming) subject in Semester 24252 at University of Engineering and Technology - Vietnam National University.

## How to play?

Keybind:

- WASD: Movement
- Left Mouse: Shoot
- Esc: Pause Game

## Image of the game

![image](https://github.com/user-attachments/assets/644867c7-e8ac-4dc8-a83c-a4f0495d7b39)
![image](https://github.com/user-attachments/assets/52b7c060-6128-4ea9-ac0c-f0c45b1d14c8)
![image](https://github.com/user-attachments/assets/fa0b550c-91cd-41a3-a6c6-d36bc7759e3e)

## How to build from source?

### 1. Clone this repo

Run this command

```bash
   mkdir TopDownShooter
   cd TopDownShooter
   git clone --recurse-submodules https://github.com/gawgua/TopDown_Shooter_INT2215_SDL3.git
```

### 2. Build

```bash
 cmake --preset <preset>
```

The build should be located on `./out/build/src/Debug` or `./out/build/src/Release`

## Issues

- The game use GameState struct as global object to pass around all the object in the game. This created circular dependencies and need to be refactored.
- Zombie still dont collide with tree (can be fix by copy logic of Player to Enemy class).
- Tree spawning outside of map, and spawn on top each other.
- Need to add Setting menu.
- The texture of this game is kinda mid.

## Author

24020254 - Nguyen Ngoc Khoi Nguyen\
QH-2024-I/CQ-I-IT2
