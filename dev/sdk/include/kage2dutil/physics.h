////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_PHYSICS_HEADER
#define KAGE_PHYSICS_HEADER
#include "box2d/Box2D.h"
#include "kf/kf_vector2.h"

namespace sf
{
	class RenderWindow;
}

namespace kage
{
	class GameObject;

	namespace Physics
	{
		// Hit is used to hold raycast intersection results.
		struct Hit
		{
		public:
			kf::Vector2 pos;	// Position of intersection.
			float distance;		// Proportion of the ray at which the intersection occured.
			bool hit;			// Bool to say if an intersection happened.
			GameObject *gob;		// The thing that owns the collider that was intersected.

			Hit() : pos(kf::Vector2(0, 0)), distance(0), hit(false), gob(0) {}
		};



		void init(b2Vec2 gravity = b2Vec2(0,0));	// Initialise the physics system.
		void update(float dt);						// Step the physics system.
		void gravity(b2Vec2 gravity);
		b2Vec2 gravity();
		b2World *getWorld();						// Retrieve the Box2D world.
		void debugDraw(sf::RenderWindow *win, float scale);							// Draw debug information.
		b2Body *createCircle(kf::Vector2f pos, float radius, float density, float damping, void *userData, b2BodyType type, float restitution);		// Create a circle collider.
		b2Body *createBox(kf::Vector2f pos, kf::Vector2f size, float density, float damping, void *userData, b2BodyType type, float restitution);	// Create a box collider.
		Hit rayCast(kf::Vector2 p1, kf::Vector2 p2);	// Perform a ray cast. Only the closest intersection is returned.
		void setActive(b2Body *b, bool active);

		// Fluent Circle collider builder helper
		class CircleBuilder
		{
		public:
			kf::Vector2 m_pos;
			float		m_mass;
			float		m_density;
			float		m_radius;
			float		m_damping;
			void	   *m_userData;
			b2BodyType	m_type;
			bool		m_calcDensity;
			float		m_restitution;

		public:
			CircleBuilder() : m_pos(kf::Vector2(0, 0)),
				m_radius(1.0f),
				m_mass(0),
				m_density(1),
				m_damping(0),
				m_userData(0),
				m_calcDensity(false),
				m_type(b2_dynamicBody),
				m_restitution(0)
			{
			}

			CircleBuilder &pos(const kf::Vector2 &p)
			{
				m_pos = p;
				return *this;
			}

			CircleBuilder &pos(float x, float y)
			{
				m_pos.set(x, y);
				return *this;
			}

			CircleBuilder &radius(float r)
			{
				m_radius = r;
				return *this;
			}

			CircleBuilder &mass(float m)
			{
				m_mass = m;
				m_calcDensity = true;
				return *this;
			}

			CircleBuilder &density(float d)
			{
				m_damping = d;
				m_calcDensity = false;
				return *this;
			}

			CircleBuilder &damping(float d)
			{
				m_damping = d;
				return *this;
			}

			CircleBuilder &userData(void *ud)
			{
				m_userData = ud;
				return *this;
			}

			CircleBuilder &type(b2BodyType type)
			{
				m_type = type;
				return *this;
			}

			CircleBuilder &restitution(float r)
			{
				m_restitution = r;
				return *this;
			}

			b2Body *build()
			{
				if (m_calcDensity)
				{
					m_density = m_mass / (m_radius * m_radius * 3.14159265);
				}
				return createCircle(m_pos, m_radius, m_density, m_damping, m_userData, m_type, m_restitution);
			}
		};

		// Fluent Box collider builder helper
		class BoxBuilder
		{
		public:
			kf::Vector2 m_pos;
			float		m_mass;
			float		m_density;
			kf::Vector2 m_size;
			float		m_damping;
			void	   *m_userData;
			b2BodyType  m_type;
			bool		m_calcDensity;
			float		m_restitution;

		public:
			BoxBuilder() : m_pos(kf::Vector2(0, 0)), m_size(kf::Vector2(1, 1)), m_mass(0), m_density(1), m_damping(0), m_userData(0), m_calcDensity(false), m_type(b2_dynamicBody), m_restitution(0)
			{
			}

			BoxBuilder &pos(const kf::Vector2 &p)
			{
				m_pos = p;
				return *this;
			}

			BoxBuilder &pos(float x, float y)
			{
				m_pos.set(x, y);
				return *this;
			}

			BoxBuilder &size(float x, float y)
			{
				m_size.set(x, y);
				return *this;
			}

			BoxBuilder &size(float s)
			{
				m_size.set(s, s);
				return *this;
			}

			BoxBuilder &size(const kf::Vector2 &s)
			{
				m_size = s;
				return *this;
			}

			BoxBuilder &mass(float m)
			{
				m_mass = m;
				m_calcDensity = true;
				return *this;
			}

			BoxBuilder &density(float d)
			{
				m_damping = d;
				m_calcDensity = false;
				return *this;
			}

			BoxBuilder &damping(float d)
			{
				m_damping = d;
				return *this;
			}

			BoxBuilder &userData(void *ud)
			{
				m_userData = ud;
				return *this;
			}

			BoxBuilder &type(b2BodyType type)
			{
				m_type = type;
				return *this;
			}

			BoxBuilder &restitution(float r)
			{
				m_restitution = r;
				return *this;
			}

			b2Body *build()
			{
				if (m_calcDensity)
				{
					m_density = m_mass / (m_size.x * m_size.y);
				}
				return createBox(m_pos, m_size, m_density, m_damping, m_userData, m_type, m_restitution);
			}
		};

	}
}

#endif