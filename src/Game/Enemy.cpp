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

	SDL_Point spawnPos = getRandSpawnPos(mGameState->game->getMap());
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
	mSpeed = speedBasedOnScore();

#ifdef TOPDOWN_DEBUG
	SDL_Log("Enemy created at: %f, %f, speed: %f", mTexRect.x, mTexRect.y, mSpeed);
#endif // TOPDOWN_DEBUG
}

void Enemy::Update()
{
	rotateToPlayer();
	//move enemy to player
	move();
	//check collision with player
	isCollisionWith(mGameState->player);
	//check collision with other enemy
	LinkedList<Enemy>::Node* enemyNode = mGameState->enemies->head();
	while (enemyNode)
	{
		if (enemyNode->data != this)
		{
			SDL_FRect enemyHitbox = enemyNode->data->getHitbox();
			if (SDL_HasRectIntersectionFloat(&mHitboxRect, &enemyHitbox))
			{
				isCollisionWith(enemyNode->data);
			}
		}
		enemyNode = enemyNode->next;
	}
}

SDL_Point Enemy::getRandSpawnPos(Map* map)
{
	enum ScreenSide 
	{ 
		TOP, 
		RIGHT, 
		BOTTOM, 
		LEFT 
	};

	SDL_Point spawnPos = { 0, 0 };
	do {
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
	} while (!map->isInMap({(float)spawnPos.x, (float)spawnPos.y, 100.0, 100.0}));

	return spawnPos;
}

void Enemy::move()
{
	float moveX = mGameState->deltaTime * mSpeed * SDL_cos(mAngleRad);
	float moveY = mGameState->deltaTime * mSpeed * SDL_sin(mAngleRad);
	
	mTexRect.x += moveX + mGameState->movedX;
	mTexRect.y += moveY + mGameState->movedY;
	mHitboxRect.x += moveX + mGameState->movedX;
	mHitboxRect.y += moveY + mGameState->movedY;
}

void Enemy::onCollision(Entity* other)
{
	if (other->getType() == EntityType::BULLET)
	{
		mIsAlive = false;
		mGameState->score++;
	}
	if (other->getType() == EntityType::PLAYER)
	{
		mIsAlive = false;
	}
	if (other->getType() == EntityType::ENEMY)
	{
		//push back enemy to avoid collision with each other
		SDL_FRect collisionRect;
		SDL_FRect otherHitbox = other->getHitbox();
		SDL_GetRectIntersectionFloat(&mHitboxRect, &otherHitbox, &collisionRect);

		// move half of collision rect because other enemy will move the other half
		if (collisionRect.w < collisionRect.h)
		{
			if (mHitboxRect.x < other->getHitbox().x)
			{
				mTexRect.x -= collisionRect.w / 2;
				mHitboxRect.x -= collisionRect.w / 2;
			}
			else
			{
				mTexRect.x += collisionRect.w / 2;
				mHitboxRect.x += collisionRect.w / 2;
			}
		}
		else
		{
			if (mHitboxRect.y < other->getHitbox().y)
			{
				mTexRect.y -= collisionRect.h / 2;
				mHitboxRect.y -= collisionRect.h / 2;
			}
			else
			{
				mTexRect.y += collisionRect.h / 2;
				mHitboxRect.y += collisionRect.h / 2;
			}
		}

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

float Enemy::speedBasedOnScore()
{
	//+15 speed per 10 score
	int ratio = mGameState->score / 10;
	float random = SDL_rand(31) - 15; // random from -15 to +15
	return mSpeed + ratio * 15 + random;
}