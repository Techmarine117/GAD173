#include "save.h"
#include"app.h"
#include"editorTile.h"
#include "Scenes.h"
#include <SFML/Graphics.hpp>


#define TILE_ROW_COUNT 20

#define TILE_COLUMN_COUNT 10
#define MAX_GRID_INDEX 20 * 10

class Tiles
{
	int id = 0;

	sf::Texture* m_texture = nullptr;
};
class GameEditor : public Scenes {
public:
	void loadTilemap();
	GameEditor();
	virtual ~GameEditor();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static GameEditor& inst();
	int selectedTileType;
	sf::Color selectedColor;
	sf::Sprite* m_backgroundSprite;
	sf::Sprite* m_cat;
	float tileWidth;
	float tileHeight;
	int maxCellIndex = (TILE_ROW_COUNT * TILE_COLUMN_COUNT);





	bool isGame;
	bool isGameEditor;


	sf::RectangleShape tilePlaceHolder;
	editorTile* editorTiles[TILE_ROW_COUNT * TILE_COLUMN_COUNT];

	sf::RectangleShape horizonalline[TILE_COLUMN_COUNT];
	int linecount;
	sf::RectangleShape vertilcallines[TILE_ROW_COUNT];
	void GameEditor::saveScene(std::string flieName);
	void GameEditor::loadScene(std::string flieName);


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