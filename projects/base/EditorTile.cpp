#include "EditorTile.h"
#include<SFML/Graphics.hpp>







EditorTile::EditorTile(float tileWidth, float tileHeight)
{
	tileShape = new sf::RectangleShape();
	tileShape->setSize(sf::Vector2f(tileWidth, tileHeight));
	
}
void EditorTile::setTile(sf::Vector2f pos)
{
	tileShape->setPosition(sf::Vector2f(pos.x, pos.y));
	active = true;


}


void EditorTile::DisableTile()
{

	active = false;
}