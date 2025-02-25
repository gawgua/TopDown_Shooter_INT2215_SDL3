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
}

Bullet::~Bullet()
{
	SDL_DestroyTexture(mTexture);
}

void Bullet::Update()
{
	move();
	checkOutsideScreen();
	//check collision with enemy
	LinkedList<Enemy>::Node* enemyNode = mGameState->enemies->head();
	while (enemyNode)
	{
		SDL_FRect enemyHitbox = enemyNode->data.getHitbox();
		if (SDL_HasRectIntersectionFloat(&mHitboxRect, &enemyHitbox))
		{
			isCollisionWith(&enemyNode->data);
		}
		enemyNode = enemyNode->next;
	}
}

void Bullet::Render()
{
	SDL_RenderTextureRotated(mGameState->game->getRenderer(), mTexture, nullptr, &mTexRect, mAngle, NULL, SDL_FLIP_NONE);
	//Debug hitbox
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderRect(mGameState->game->getRenderer(), &mHitboxRect);
	//debug angle
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 0, 0, 255, 255);
	SDL_RenderLine(mGameState->game->getRenderer(), mTexRect.x + mTexRect.w / 2, mTexRect.y + mTexRect.h / 2, mTexRect.x + mTexRect.w / 2 + 50 * SDL_cos(mAngle * SDL_PI_D / 180), mTexRect.y + mTexRect.h / 2 + 50 * SDL_sin(mAngle * SDL_PI_D / 180));
}

void Bullet::move()
{
	float moveX = mSpeed * SDL_cos(mAngleRad);
	float moveY = mSpeed * SDL_sin(mAngleRad);

	mTexRect.x += moveX;
	mTexRect.y += moveY;
	mHitboxRect.x += moveX;
	mHitboxRect.y += moveY;
}

void Bullet::onCollision(EntityType type)
{
		if (type == EntityType::ENEMY)
	{
		mIsAlive = false;
	}
}