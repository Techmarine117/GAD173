#ifndef QGF2D_GAMEOBJECT_HEADER
#define QGF2D_GAMEOBJECT_HEADER
#include "kf/kf_vector2.h"
#include <SFML/Graphics.hpp>
//#include "box2d\Box2D.h"
#include "world.h"

namespace kage
{
	class GameObject
	{
	public:
		enum PhysicsStyle
		{
			e_psNone=0,
			e_psNewtonian,
			e_psBox2D
		};
		kf::Vector2 m_position;
		kf::Vector2 m_velocity;
		kf::Vector2 m_force;
		float m_rotation;
		float m_life;
		bool m_dead;
		long long m_id;
		PhysicsStyle m_physicsStyle;
		bool m_overlap;
		int m_type;
		bool m_collide;
		bool m_gravity;
		int m_order;
		sf::Sprite *m_sprite;
//		b2Body *m_body;
		GameObject();
		virtual ~GameObject();
		void update(float dt);
		void render(sf::RenderWindow &rw);
		GameObject &position(const kf::Vector2 &pos);
		GameObject &velocity(const kf::Vector2 &vel);
		kf::Vector2 position();
		kf::Vector2 velocity();
		GameObject &addForce(const kf::Vector2 &force);
		static GameObject *build();
	};

	typedef void (*CollisionCallback_t)(GameObject *obj1, GameObject *obj2);
		
	extern CollisionCallback_t CollisionCallback;

}

#endif