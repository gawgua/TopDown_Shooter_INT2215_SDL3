#pragma once

#include "linkedlist.h"
//forward declaration to avoid circular dependency
class Game;
class Entity;
class Player;
class Enemy;
class Bullet;

struct GameState {
	Game* game;
	Player* player;
	LinkedList<Enemy>* enemies;
	LinkedList<Bullet>* bullets;

	int mouseX, mouseY;
	float movedX, movedY;
	double deltaTime;
	Uint32 score;
	bool isGameOver;
	bool isUserExit;
	bool isPaused;
};

#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"