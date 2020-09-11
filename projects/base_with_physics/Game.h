#pragma once
#include"Scenes.h"
#include "app.h"
#include "kage2dutil/physics.h"


class Game: public Scenes
{
public:
	Game();
	virtual ~Game();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static Game&inst();
	
	sf::CircleShape mousePointer;
	sf::Sprite *m_backgroundSprite;
};
