#pragma once

#include "app.h"
#include"EditorTile.h"

#define TILE_ROW_COUNT 20
#define TILE_COLUMN_COUNT 10

class Example : public App
{
public:
	Example();
	virtual ~Example();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static Example &inst();

	sf::Sprite *m_backgroundSprite;
	sf::Sprite* m_cat;
	float tileWidth;
	float tileHeight;
	
	sf::RectangleShape tilePlaceHolder;
	EditorTile* editorTiles[TILE_ROW_COUNT * TILE_COLUMN_COUNT];

	sf::RectangleShape horizonalline[TILE_COLUMN_COUNT];
	int linecount;
	sf::RectangleShape vertilcallines[TILE_ROW_COUNT];


};
