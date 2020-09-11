#pragma once
#include<SFML/Graphics.hpp>
class editorTile
{
public:
	bool active;
	sf::RectangleShape* tileShape;

	editorTile(float tileWidth, float tileHeight);

	void editorTile::setcolor(sf::Color color);






	void editorTile::setTile(sf::Vector2f pos);






	void editorTile::DisableTile();
};

