#include "kage2dutil/gameobject.h"
#include <map>
#include <string>

namespace
{
	long long g_maxId=0;
	std::map<std::string, sf::Texture *> g_textures;
}

namespace kage
{
	namespace TextureManager
	{
		sf::Texture *getTexture(const std::string &filename)
		{
			std::map<std::string, sf::Texture *>::iterator it = g_textures.find(filename);
			if (it == g_textures.end())
			{
				sf::Texture *im = new sf::Texture;
				if (!im->loadFromFile(filename))
				{
					delete im;
					return 0;
				}
				g_textures[filename] = im;
				return im;
			}
			return it->second;
		}

		sf::Sprite *getSprite(const std::string &filename)
		{
			sf::Texture *t = getTexture(filename);
			sf::Sprite *s = new sf::Sprite();

			if (t)
			{
				s->setTexture(*t);
			}
			return s;
		}
	}
}
