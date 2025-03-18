#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "constant.h"
struct GameState;

enum EntityType
{
	UNDEFINED,
	PLAYER,
	BULLET,
	ENEMY
};

class Entity
{
public:
	Entity() {};
	~Entity();

	EntityType getType() { return mType; }
	static std::string getTypeString(EntityType type);
	bool isAlive() { return mIsAlive; }
	int getHp() { return mHp; }
	SDL_FPoint getCenter() { return { mTexRect.x + mTexRect.w / 2, mTexRect.y + mTexRect.h / 2 }; }
	SDL_FRect getHitbox() { return mHitboxRect; }
	SDL_FRect getTexRect() { return mTexRect; }
	float getRadianAngle() { return mAngleRad; }
	int getAngle() { return mAngle; }
	void isCollisionWith(Entity* other);

	virtual void Render();
	virtual void Update() = 0;
	virtual void onCollision(EntityType type) = 0;
protected:
	void checkOutsideScreen();

	EntityType mType = EntityType::UNDEFINED;

	GameState* mGameState;

	SDL_Texture* mTexture;
	SDL_FRect mHitboxRect;
	SDL_FRect mTexRect;
	float mAngleRad;
	int mAngle;
	bool mIsAlive = true;
	int mHp = 1;

	const float mSpeed = 0.0;
	const float mHitboxSize = 50.0;
	const float mTexSize = 50.0;
	const char* mTexturePath;
};

#include "gamestate.h"