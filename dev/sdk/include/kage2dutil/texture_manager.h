#ifndef QGF2D_TEXTUREMANAGER_HEADER
#define QGF2D_TEXTUREMANAGER_HEADER

#include <SFML/Graphics.hpp>


namespace kage
{
	namespace TextureManager
	{
		sf::Texture *getTexture(const std::string &filename);
		sf::Sprite *getSprite(const std::string &filename);
	}
}

#endif