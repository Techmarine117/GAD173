#pragma once
#include <SFML/Graphics.hpp>
class Scenes
{
public:
	sf::RenderWindow* m_window;

	virtual bool start() = 0;
	virtual void update(float deltaT) = 0;
	virtual void render() = 0;
	virtual void cleanup() = 0;


};

