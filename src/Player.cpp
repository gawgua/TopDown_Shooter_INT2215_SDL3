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
	mHp = 5;
}

void Player::Update()
{
	rotateToMouse();

	if (mHp <= 0)
		mIsAlive = false;
}

void Player::shoot()
{
	mGameState->bullets->push_back(new Bullet(mGameState));
}

void Player::onCollision(EntityType type) //only trigger with enemy
{
	if (type == EntityType::ENEMY)
		mHp--;
}

void Player::rotateToMouse()
{
	// tan(a) = doi / ke
	mAngleRad = SDL_atan2(mGameState->mouseY - mGameState->screenH / 2, mGameState->mouseX - mGameState->screenW / 2); //radian
	mAngle = (int)(mAngleRad * 180 / SDL_PI_D + 360) % 360; //convert to degree 
}