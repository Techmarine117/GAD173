#include "GameEditor.h"
#include <math.h>



GameEditor::GameEditor() : Scenes()
{
	for (size_t i = 0; i < TILE_ROW_COUNT * TILE_COLUMN_COUNT; i++)
	{
		editorTiles[i] = nullptr;
	}
	
}

GameEditor::~GameEditor() 
{
}

GameEditor& GameEditor::inst()
{
	static GameEditor s_instance;
	return s_instance;
}

void GameEditor::loadTilemap()
{
	
	for (size_t i = 0; i < MAX_GRID_INDEX; i++)
	{
		int y = i / TILE_ROW_COUNT;
		int x = i - y * TILE_ROW_COUNT;
		switch (cellMap[i])
		{

		case 0:
			if (editorTiles[i] != nullptr && editorTiles[i]->active)
			{
				editorTiles[i]->DisableTile();

			}
			break;
		case 1:



			if (editorTiles[i] != nullptr)
			{
				editorTiles[i]->setTile(sf::Vector2f(x * tileWidth, y * tileHeight));
				editorTiles[i]->setcolor(sf::Color::White);
				cellMap[i] = 1;
			}
			else
			{
				editorTiles[i] = new editorTile(tileWidth, tileHeight);
				editorTiles[i]->setTile(sf::Vector2f(x * tileWidth, y * tileHeight));
				editorTiles[i]->setcolor(sf::Color::White);
				cellMap[i] = 1;

			}
			break;

		case 2:




			if (editorTiles[i] != nullptr)
			{
				editorTiles[i]->setTile(sf::Vector2f(x * tileWidth, y * tileHeight));
				editorTiles[i]->setcolor(sf::Color::Red);
				cellMap[i] = 2;
			}
			else
			{
				editorTiles[i] = new editorTile(tileWidth, tileHeight);
				editorTiles[i]->setTile(sf::Vector2f(x * tileWidth, y * tileHeight));
				editorTiles[i]->setcolor(sf::Color::Red);
				cellMap[i] = 2;

			}
			break;



		}

	}

}

bool GameEditor::start()
{


	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);
	

	float winWidth = m_window->getSize().x;
	float winHeight = m_window->getSize().y;
	tileWidth = winWidth / TILE_ROW_COUNT;
	tileHeight = (winHeight * 0.5) / TILE_COLUMN_COUNT;

	//initializing title placeholder
	tilePlaceHolder = sf::RectangleShape();
	tilePlaceHolder.setSize(sf::Vector2f(tileWidth, tileHeight));
	tilePlaceHolder.setFillColor(sf::Color::Blue);



	// makes horizonalline
	for (size_t i = 0; i < TILE_COLUMN_COUNT; i++)
	{
		horizonalline[i] = sf::RectangleShape();
		horizonalline[i].setSize(sf::Vector2f(winWidth, 2));
		horizonalline[i].setPosition(sf::Vector2f(0, tileHeight * (i + 1)));
		horizonalline[i].setFillColor(sf::Color::Green);

	}

	// makes vertilcallines
	for (size_t i = 0; i < TILE_ROW_COUNT; i++)
	{
		vertilcallines[i] = sf::RectangleShape();
		vertilcallines[i].setSize(sf::Vector2f(winHeight * 0.5, 2));
		vertilcallines[i].setRotation(90);
		vertilcallines[i].setPosition(sf::Vector2f(tileWidth * (i + 1), 0));
		vertilcallines[i].setFillColor(sf::Color::Green);





	}







	return true;




}

void GameEditor::update(float deltaT)
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_window);









	if (isGame)
	{
		sf::Vector2f windowcenter = sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2);
	

	}




	if (isGameEditor)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window->hasFocus())
		{
			
		}

		
		//std::cout << "Mouse Position X - " << mousePosition.x << " | " << "Mouse Position Y - " << mousePosition.y << std::endl;
		int newMouseX = mousePosition.x / tileWidth;
		int newMouseY = mousePosition.y / tileHeight;
		if (newMouseX <= 0)
			newMouseX = 0;
		if (newMouseX >= TILE_ROW_COUNT - 1)
			newMouseX = TILE_ROW_COUNT - 1;
		if (newMouseY <= 0)
			newMouseY = 0;

		if (newMouseY >= TILE_COLUMN_COUNT - 1)
			newMouseY = TILE_COLUMN_COUNT - 1;




		// keyboard presses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{


			selectedTileType = 1;
			selectedColor = sf::Color::White;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{


			selectedTileType = 2;
			selectedColor = sf::Color::Red;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{

			loadScene("file");
			loadTilemap();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{


			saveScene("file");

		}


		// lift click event

		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			int index = newMouseY * TILE_ROW_COUNT + newMouseX;

			if (editorTiles[index] != nullptr)
			{
				editorTiles[index]->setTile(sf::Vector2f(newMouseX * tileWidth, newMouseY * tileHeight));
				editorTiles[index]->setcolor(selectedColor);
				cellMap[index] = selectedTileType;
			}
			else
			{
				editorTiles[index] = new editorTile(tileWidth, tileHeight);
				editorTiles[index]->setTile(sf::Vector2f(newMouseX * tileWidth, newMouseY * tileHeight));
				editorTiles[index]->setcolor(selectedColor);
				cellMap[index] = selectedTileType;

			}



			for (size_t i = 0; i < 200; i++)
			{



			}







		}
	}

}

void GameEditor::render()
{


	
	if (isGameEditor)
	{


		m_window->draw(*m_backgroundSprite);


		for (size_t i = 0; i < TILE_COLUMN_COUNT; i++)
		{
			m_window->draw(horizonalline[i]);
		}

		for (size_t i = 0; i < TILE_ROW_COUNT; i++)
		{
			m_window->draw(vertilcallines[i]);

		}

		for (size_t i = 0; i < TILE_ROW_COUNT * TILE_COLUMN_COUNT; i++)
		{
			
			if (editorTiles[i] != nullptr && editorTiles[i]->active)
			{


				m_window->draw(*editorTiles[i]->tileShape);

			}
		}
	}

}

void GameEditor::cleanup()
{
	delete m_backgroundSprite;

}
void GameEditor::saveScene(std::string flieName)
{
	save saver;
	std::ostringstream os;
	for (int i : cellMap) {
		os << i;
	}



	std::string str(os.str());
	saver.Saved(flieName, str);

}

void GameEditor::loadScene(std::string flieName)
{
	save loader;
	std::string data = loader.Load(flieName);

	//std::cout << data;
	for (size_t i = 0; i < 200; i++)
	{
		char val = data.at(i);
		int num = val - 48;
		switch (num)
		{
		case 0:
			cellMap[i] = 0;
			break;
		case 1:
			cellMap[i] = 1;
			break;
		case 2:
			cellMap[i] = 2;
			break;
		default:
			std::cout << num;
			break;
		}

	}
}





