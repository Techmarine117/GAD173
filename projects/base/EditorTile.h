#pragma once
#include<SFML/Graphics.hpp>
class EditorTile
{
public:
	bool active;
	sf::RectangleShape * tileShape;
	
	EditorTile(float tileWidth, float tileHeight);
		


	
	void EditorTile::setTile(sf::Vector2f pos);
	
		
		
	


	void EditorTile::DisableTile();
	

		
	
};

