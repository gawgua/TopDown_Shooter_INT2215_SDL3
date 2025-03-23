#include "bullet.h"

Bullet::Bullet(GameState* gameState)
{

	mType = EntityType::BULLET;

	mGameState = gameState;
	mTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mBulletTexturePath);
	if (!mTexture)
	{
		SDL_Log("Failed to load bullet texture: %s", SDL_GetError());
	}

	SDL_FPoint playerCenter = mGameState->player->getCenter();
	mTexRect = { playerCenter.x - mTexSize / 2, playerCenter.y - mTexSize / 2, mTexSize, mTexSize};
	//center hitbox to texture
	float hitboxX = mTexRect.x + (mTexRect.w - mHitboxSize) / 2;
	float hitboxY = mTexRect.y + (mTexRect.h - mHitboxSize) / 2;
	mHitboxRect = { hitboxX, hitboxY, mHitboxSize, mHitboxSize };
	mAngle = mGameState->player->getAngle();
	mAngleRad = mGameState->player->getRadianAngle();

#ifdef TOPDOWN_DEBUG
	SDL_Log("Bullet created at: %f, %f", mTexRect.x, mTexRect.y);
#endif // TOPDOWN_DEBUG
}

void Bullet::Update()
{
	move();
	checkOutsideScreen();
	//check collision with enemy
	LinkedList<Enemy>::Node* enemyNode = mGameState->enemies->head();
	while (enemyNode)
	{
		SDL_FRect enemyHitbox = enemyNode->data->getHitbox();
		if (SDL_HasRectIntersectionFloat(&mHitboxRect, &enemyHitbox))
		{
			isCollisionWith(enemyNode->data);
		}
		enemyNode = enemyNode->next;
	}
}

void Bullet::move()
{
	float moveX = mGameState->deltaTime * mSpeed * SDL_cos(mAngleRad);
	float moveY = mGameState->deltaTime * mSpeed * SDL_sin(mAngleRad);

	mTexRect.x += moveX + mGameState->movedX;
	mTexRect.y += moveY + mGameState->movedY;
	mHitboxRect.x += moveX + mGameState->movedX;
	mHitboxRect.y += moveY + mGameState->movedY;
}

void Bullet::onCollision(EntityType type)
{
	if (type == EntityType::ENEMY)
	{
		mIsAlive = false;
	}
}