#include "Game.h"
#include"SceneManager.h"

Game::Game()
{
}

Game::~Game()
{
}

Game& Game::inst()
{
	static Game s_instance;
	return s_instance;
}

bool Game::start()
{
	

	
	mousePointer = sf::CircleShape(10.f);

	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);

	
	return true;
}

void Game::update(float deltaT)
{
	// You need to update the physics system every game update
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_window);
	mousePointer.setPosition(mousePosition.x,m_window->getSize().y -200);



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window->hasFocus())
	{
		
	}

	
}

void Game::render()
{
	
	m_window->draw(*m_backgroundSprite);
	m_window->draw(mousePointer);
	
}

void Game::cleanup()
{
	delete m_backgroundSprite;
}

