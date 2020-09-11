#include "editorTile.h"
editorTile::editorTile(float tileWidth, float tileHeight)
{
	tileShape = new sf::RectangleShape();
	tileShape->setSize(sf::Vector2f(tileWidth, tileHeight));
	
}
void editorTile::setTile(sf::Vector2f pos)
{
	tileShape->setPosition(sf::Vector2f(pos.x, pos.y));
	active = true;


}


void editorTile::DisableTile()
{

	active = false;
}

void editorTile::setcolor(sf::Color color) 
{
	tileShape->setFillColor(color);

}
