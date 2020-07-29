#include "example.h"
#include <math.h>

Example::Example(): App()
{
}

Example::~Example()
{
}

Example &Example::inst()
{
	static Example s_instance;
	return s_instance;
}

bool Example::start()
{
	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window.getSize().x) / resolution.x, float(m_window.getSize().y) / resolution.y);
	
	float winWidth = m_window.getSize().x;
	float winHeight = m_window.getSize().y;
	tileWidth = winWidth / TILE_ROW_COUNT;
	tileHeight = (winHeight * 0.5)/ TILE_COLUMN_COUNT;

	//initializing title placeholder
	tilePlaceHolder = sf::RectangleShape();
	tilePlaceHolder.setSize(sf::Vector2f(tileWidth,tileHeight));
	tilePlaceHolder.setFillColor(sf::Color::Blue);


	
	// makes horizonalline
	for (size_t i = 0; i < TILE_COLUMN_COUNT; i++)
	{
		horizonalline[i] =  sf::RectangleShape();
		horizonalline[i].setSize(sf::Vector2f(winWidth, 2));
		horizonalline[i].setPosition(sf::Vector2f(0, tileHeight * (i + 1)));
		horizonalline[i].setFillColor(sf::Color::Green);

	}

	// makes vertilcallines
	for (size_t i = 0; i < TILE_ROW_COUNT; i++)
	{
		vertilcallines[i] =  sf::RectangleShape();
		vertilcallines[i].setSize(sf::Vector2f(winHeight * 0.5, 2));
		vertilcallines[i].setRotation(90);
		vertilcallines[i].setPosition(sf::Vector2f(tileWidth * (i + 1),0));
		vertilcallines[i].setFillColor(sf::Color::Green);

	}

	
	
	return true;


	
	
}

void Example::update(float deltaT)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}

	ImGui::Begin("Kage2D");
	if(ImGui::Button("Exit"))
	{ 
		m_running = false;
	}
	ImGui::End();

	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_window);
	std::cout << mousePosition.x << "" << mousePosition.y << std::endl;
	int newMouseX = mousePosition.x / tileWidth;
	int newMouseY = mousePosition.y / tileHeight;
	if (newMouseX <= 0)
		newMouseX = 0;
	if (newMouseX >= TILE_ROW_COUNT -1)
		newMouseX = TILE_ROW_COUNT -1;
	if (newMouseY <= 0)
		newMouseY = 0;

	if (newMouseY >= TILE_COLUMN_COUNT -1)
		newMouseY = TILE_COLUMN_COUNT -1;

	tilePlaceHolder.setPosition(sf::Vector2f(newMouseX * tileWidth,newMouseY * tileHeight));
	// lift click event
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))) 
	{
		int index = newMouseY * TILE_ROW_COUNT + newMouseX;
		
		if (editorTiles[index] != nullptr) 
		{
			editorTiles[index]->setTile(sf::Vector2f(newMouseX * tileWidth, newMouseY * tileHeight));

		}
		else
		{
			editorTiles[index] = new EditorTile(tileWidth, tileHeight);
			editorTiles[index]->setTile(sf::Vector2f(newMouseX * tileWidth, newMouseY * tileHeight));


		}


		// Right click event
		//if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))) 
		{
			
			
			//auto rect = make_unique<sf::Rectangle>(sf::Vector2f(50, 100));
			//rect.reset();

		}
		
	}

}

void Example::render()
{
	m_window.draw(*m_backgroundSprite);
	m_window.draw(tilePlaceHolder);
	
	for (size_t i = 0; i < TILE_COLUMN_COUNT; i++)
	{
		m_window.draw(horizonalline[i]);
	}

	for (size_t i = 0; i < TILE_ROW_COUNT; i++)
	{
		m_window.draw(vertilcallines[i]);

	}

	for (size_t i = 0; i < TILE_ROW_COUNT * TILE_COLUMN_COUNT; i++)
	{
		if( editorTiles[i]!=nullptr && editorTiles[i]->active)
		{


		m_window.draw(*editorTiles[i]->tileShape);

		}
	}
	

}

void Example::cleanup()
{
	delete m_backgroundSprite;
	
}



