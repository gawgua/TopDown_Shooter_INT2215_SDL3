#include "entity.h"

Entity::~Entity() 
{
	SDL_DestroyTexture(mTexture);
}

void Entity::Render()
{
	SDL_RenderTextureRotated(mGameState->game->getRenderer(), mTexture, nullptr, &mTexRect, mAngle, NULL, SDL_FLIP_NONE);
	////Debug hitbox
	//SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 255, 0, 0, 255);
	//SDL_RenderRect(mGameState->game->getRenderer(), &mHitboxRect);
	////debug angle
	//SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 0, 0, 255, 255);
	//SDL_RenderLine(mGameState->game->getRenderer(), mTexRect.x + mTexRect.w / 2, mTexRect.y + mTexRect.h / 2, mTexRect.x + mTexRect.w / 2 + 50 * SDL_cos(mAngle * SDL_PI_D / 180), mTexRect.y + mTexRect.h / 2 + 50 * SDL_sin(mAngle * SDL_PI_D / 180));
}

void Entity::isCollisionWith(Entity* other)
{
	SDL_FRect otherHitbox = other->getHitbox();
	if (SDL_HasRectIntersectionFloat(&mHitboxRect, &otherHitbox))
	{
		onCollision(other->getType());
		other->onCollision(mType);
	}
}

void Entity::checkOutsideScreen()
{
	if (mTexRect.x < 0 || mTexRect.x > SCREEN_WIDTH || mTexRect.y < 0 || mTexRect.y > SCREEN_HEIGHT)
		mIsAlive = false;
}