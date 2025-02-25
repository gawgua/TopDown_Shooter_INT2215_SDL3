#include "player.h"

Player::Player(GameState* gameState)
{
	mType = EntityType::PLAYER;

	mGameState = gameState;
	mTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mPlayerTexturePath);
	if (!mTexture)
	{
		SDL_Log("Failed to load player texture: %s", SDL_GetError());
	}
	//center texture to screen
	float texX = (SCREEN_WIDTH - mTexSize) / 2.0;
	float texY = (SCREEN_HEIGHT - mTexSize) / 2.0;
	mTexRect = { texX, texY, mTexSize, mTexSize };
	//center hitbox to texture
	float hitboxX = mTexRect.x + (mTexRect.w - mHitboxSize) / 2.0;
	float hitboxY = mTexRect.y + (mTexRect.h - mHitboxSize) / 2.0;
	mHitboxRect = { hitboxX, hitboxY, mHitboxSize, mHitboxSize };
	mAngle = 0;
}

Player::~Player()
{
	SDL_DestroyTexture(mTexture);
}

void Player::Update()
{
	rotateToMouse();
}

void Player::Render()
{
	SDL_RenderTextureRotated(mGameState->game->getRenderer(), mTexture, nullptr, &mTexRect, mAngle, NULL, SDL_FLIP_NONE);
	//Debug hitbox
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderRect(mGameState->game->getRenderer(), &mHitboxRect);
	//debug angle
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 0, 0, 255, 255);
	SDL_RenderLine(mGameState->game->getRenderer(), mTexRect.x + mTexRect.w / 2, mTexRect.y + mTexRect.h / 2, mTexRect.x + mTexRect.w / 2 + 50 * SDL_cos(mAngle * SDL_PI_D / 180), mTexRect.y + mTexRect.h / 2 + 50 * SDL_sin(mAngle * SDL_PI_D / 180));
}

void Player::shoot()
{
	mGameState->bullets->push_back(Bullet(mGameState));
}

void Player::onCollision(EntityType type) //only trigger with enemy
{
	if (type == EntityType::ENEMY)
		mIsAlive = false;
}

void Player::rotateToMouse()
{
	SDL_FPoint playerCenter = getCenter();
	// tan(a) = doi / ke
	mAngleRad = SDL_atan2(mGameState->mouseY - playerCenter.y, mGameState->mouseX - playerCenter.x); //radian
	mAngle = (int)(mAngleRad * 180 / SDL_PI_D + 360) % 360; //convert to degree 
}