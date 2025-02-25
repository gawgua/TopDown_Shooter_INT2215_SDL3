#include "enemy.h"

Enemy::Enemy(GameState* gameState)
{
	mType = EntityType::ENEMY;

	mGameState = gameState;
	mTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mEnemyTexturePath);
	if (!mTexture)
	{
		SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
	}

	SDL_Point spawnPos = getRandSpawnPos();
	float texX = spawnPos.x;
	float texY = spawnPos.y;
	mTexRect = { texX, texY, mTexSize, mTexSize };
	//center hitbox to texture
	float hitboxX = mTexRect.x + (mTexRect.w - mHitboxSize) / 2;
	float hitboxY = mTexRect.y + (mTexRect.h - mHitboxSize) / 2;
	mHitboxRect = { hitboxX, hitboxY, mHitboxSize, mHitboxSize };
	mAngle = 0;
	mAngleRad = 0.0;
	mIsAlive = true;
}

void Enemy::Update()
{
	rotateToPlayer();
	//move enemy to player
	move();
	//check collision with player
	isCollisionWith(mGameState->player);
}

Uint32 Enemy::Spawn(void* pGameState, SDL_TimerID id, Uint32 interval)
{
	GameState* gameState = (GameState*)pGameState;
	gameState->enemies->push_back(new Enemy(gameState));
	return ENEMY_SPAWN_INTERVAL;
}

SDL_Point Enemy::getRandSpawnPos()
{
	enum ScreenSide 
	{ 
		TOP, 
		RIGHT, 
		BOTTOM, 
		LEFT 
	};
	SDL_Point spawnPos = { 0, 0 };
	//random spawn position
	ScreenSide side = (ScreenSide)(SDL_rand(4));

	switch (side)
	{
	case TOP:
		spawnPos.x = SDL_rand(SCREEN_WIDTH);
		spawnPos.y = -100;
		break;
	case RIGHT:
		spawnPos.x = SCREEN_WIDTH;
		spawnPos.y = SDL_rand(SCREEN_HEIGHT);
		break;
	case BOTTOM:
		spawnPos.x = SDL_rand(SCREEN_WIDTH);
		spawnPos.y = SCREEN_HEIGHT;
		break;
	case LEFT:
		spawnPos.x = -100;
		spawnPos.y = SDL_rand(SCREEN_HEIGHT);
		break;
	}

	return spawnPos;
}

void Enemy::move()
{
	float moveX = mSpeed * SDL_cos(mAngleRad);
	float moveY = mSpeed * SDL_sin(mAngleRad);
	
	mTexRect.x += moveX;
	mTexRect.y += moveY;
	mHitboxRect.x += moveX;
	mHitboxRect.y += moveY;
}

void Enemy::onCollision(EntityType type) //only trigger with bullet
{
	if (type == EntityType::BULLET)
	{
		mIsAlive = false;
		mGameState->score++;
	}
}

void Enemy::rotateToPlayer()
{
	SDL_FPoint enemyHitbox = getCenter();
	SDL_FPoint playerHitbox = mGameState->player->getCenter();
	// tan(a) = doi / ke
	mAngleRad = SDL_atan2(playerHitbox.y - enemyHitbox.y, playerHitbox.x - enemyHitbox.x); //radian
	mAngle = (int)(mAngleRad * 180 / SDL_PI_D + 360) % 360; //convert to degree
}