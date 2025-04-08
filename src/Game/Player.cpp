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
	mdeltaTimeShoot = 0.0f;
}

void Player::Update()
{
	rotateToMouse();

	for (auto tree : *mGameState->game->getMap()->getTrees())
	{
		SDL_FRect intersection;
		SDL_FRect treeHitbox = tree->getHitbox();
		if (SDL_GetRectIntersectionFloat(&mHitboxRect, &treeHitbox, &intersection))
		{
			// move half of collision rect because other enemy will move the other half
			if (intersection.w < intersection.h)
			{
				if (mHitboxRect.x < treeHitbox.x)
				{
					mGameState->movedX += intersection.w;
				}
				else
				{
					mGameState->movedX -= intersection.w;
				}
			}
			else
			{
				if (mHitboxRect.y < treeHitbox.y)
				{
					mGameState->movedY += intersection.h;
				}
				else
				{
					mGameState->movedY -= intersection.h;
				}
			}
		}
	}

	if (mHp <= 0)
		mIsAlive = false;

	mdeltaTimeShoot -= mGameState->deltaTime;
}

void Player::shoot()
{
	if (mdeltaTimeShoot > 0.0f)
		return;
	mdeltaTimeShoot = 0.5f; // 2 shots per second
	mGameState->bullets->push_back(new Bullet(mGameState));
}

void Player::onCollision(Entity* other)
{
	if (other->getType() == EntityType::ENEMY)
	{
		mGameState->game->getAudioManager()->playHurt();
		mHp--;
	}
}

void Player::rotateToMouse()
{
	//get mouse position
	float x, y;
	SDL_RenderCoordinatesFromWindow(mGameState->game->getRenderer(), mGameState->mouseX, mGameState->mouseY, &x, &y);
	// tan(a) = doi / ke
	mAngleRad = SDL_atan2(y - SCREEN_HEIGHT / 2, x - SCREEN_WIDTH / 2); //radian
	mAngle = (int)(mAngleRad * 180 / SDL_PI_D + 360) % 360; //convert to degree 
}