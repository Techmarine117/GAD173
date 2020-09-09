#pragma once

#include "app.h"
#include"EditorTile.h"
#include "Saving.h"


#define TILE_ROW_COUNT 20
#define TILE_COLUMN_COUNT 10
#define MAX_GRID_INDEX 20 * 10


  

class Tiles 
{
	int id = 0;

	sf::Texture* m_texture = nullptr;

};




class Example : public App
{
public:
	void loadTilemap();
	Example();
	virtual ~Example();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static Example &inst();
	int selectedTileType;
	sf::Color selectedColor;
	sf::Sprite *m_backgroundSprite;
	sf::Sprite* m_cat;
	float tileWidth;
	float tileHeight;
	int maxCellIndex = (TILE_ROW_COUNT * TILE_COLUMN_COUNT);

	int mainOffset;
	int textOffset;
	sf::Vector2f WindowCenter;
	sf::Text mainText[4];
	sf::Font font;
	
	bool ismainMenu;
	bool isGame;
	bool isGameEditor;
	
	
	sf::RectangleShape tilePlaceHolder;
	EditorTile* editorTiles[TILE_ROW_COUNT * TILE_COLUMN_COUNT];

	sf::RectangleShape horizonalline[TILE_COLUMN_COUNT];
	int linecount;
	sf::RectangleShape vertilcallines[TILE_ROW_COUNT];
	void Example::saveScene(std::string flieName);
	void Example::loadScene(std::string flieName);
	

	sf::Sprite m_currentTile;
public:
	 int cellMap[200] =
	{
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

	};

	




};
