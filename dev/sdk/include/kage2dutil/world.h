#ifndef QGF2D_WORLD_HEADER
#define QGF2D_WORLD_HEADER
#include "kf/kf_vector2.h"
#include <SFML/Graphics.hpp>
//#include "box2d\Box2D.h"


namespace kage
{
	class GameObject;

	namespace World
	{
		kf::Vector2 gravity();
		void gravity(const kf::Vector2 &grav);
		long long newID();
		void update(float dt);
		void render(sf::RenderWindow &rw);
		void add(GameObject *obj);
		void remove(GameObject *obj);
		template<typename T>
		T *build()
		{
			GameObject *obj = new T;
			obj->m_id = newID();
			add(obj);
			return (T*)obj;
		}
	}
}

#endif