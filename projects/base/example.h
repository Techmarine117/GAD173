#pragma once

#include "app.h"
#include"EditorTile.h"

#define TILE_ROW_COUNT 10
#define TILE_COLUMN_COUNT 20

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
	float tileCountColumn = TILE_COLUMN_COUNT;
	float tileCountRow = TILE_ROW_COUNT;
	sf::RectangleShape tilePlaceHolder;
	EditorTile* editorTiles[TILE_ROW_COUNT * TILE_COLUMN_COUNT];

	sf::RectangleShape horizonalline[10];
	int linecount;
	sf::RectangleShape vertilcallines[25];


};
