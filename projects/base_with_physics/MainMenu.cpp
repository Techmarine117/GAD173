#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu() 
{
}

MainMenu::~MainMenu()
{
}



bool MainMenu::start()
{
	ismainMenu = true;
	

	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);


	if (ismainMenu)

	{
		mainOffset = 50;
		textOffset = 90;
		sf::Vector2f windowcenter = sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2);
		if (font.loadFromFile("data/bluehigh.ttf"))
		{
			std::cout << "can't load font" << std::endl;

		}

		for (size_t i = 0; i < 4; i++) {
			mainText[i].setFont(font);
			mainText[i].setPosition(sf::Vector2f(
				windowcenter.x - (mainText[i].getGlobalBounds().width / 2),
				windowcenter.y - (mainText[i].getGlobalBounds().width / 2) + (textOffset * i) + mainOffset));
			std::cout << windowcenter.y - (mainText[i].getGlobalBounds().width / 2) + (textOffset * i) + mainOffset << std::endl;
			mainText[i].setColor(sf::Color::White);
			mainText[i].setCharacterSize(100);


		}

		mainText[0].setString("play");
		mainText[1].setString("editor");
		mainText[3].setString("options");
		mainText[2].setString("Exit");



	}

	return true;
}

void MainMenu::update(float deltaT)
{
	// You need to update the physics system every game update
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_window);
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseWasPressd = true;

	}
	if (mouseWasPressd == true &&!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseWasPressd = false;
		for (size_t i = 0; i < 4; i++)
		{

			sf::FloatRect bound = mainText[i].getGlobalBounds();

			if (bound.contains(mousePosition))
			{
				switch (i)
				{
				case 0:
					std::cout << " Play Button is pressed " << std::endl;
					SceneManager::Run(1);

					break;
				case 1:
					std::cout << "Editor Button is pressed" << std::endl;
					SceneManager::Run(2);
					ismainMenu = false;
					break;
				case 2:
					std::cout << "Exit Button is pressed" << std::endl;
					m_window->close();
					break;
				case 3:
					std::cout << "options is pressed" << std::endl;
				default:


					break;
				}


			}

		}
	}

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window->hasFocus())
	{
		
	}


}

void MainMenu::render()
{
	if (ismainMenu)
	{
		m_window->draw(mainText[2]);
		m_window->draw(mainText[0]);
		m_window->draw(mainText[1]);
		m_window->draw(mainText[3]);

	}
	
	
}

void MainMenu::cleanup()
{
	delete m_backgroundSprite;
}

