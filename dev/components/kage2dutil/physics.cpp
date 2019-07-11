////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage2dutil/physics.h"
#include "kage2dutil/gameobject.h"
#include "kage2dutil/sfml_util.h"

namespace kage
{

	namespace Physics
	{
		class ContactListener : public b2ContactListener
		{
		public:
			virtual void BeginContact(b2Contact* contact)
			{
				b2Fixture *f1 = contact->GetFixtureA();
				b2Fixture *f2 = contact->GetFixtureB();
				kf::Vector2 v1 = f1->GetBody()->GetLinearVelocity();
				kf::Vector2 v2 = f2->GetBody()->GetLinearVelocity();
				kf::Vector2 p1 = f1->GetBody()->GetPosition();
				kf::Vector2 p2 = f1->GetBody()->GetPosition();

				b2WorldManifold worldManifold;
				contact->GetWorldManifold(&worldManifold);

				kf::Vector2 norm = worldManifold.normal;

				if (f1->GetUserData())
				{
					((GameObject*)(f1->GetUserData()))->onCollision((GameObject *)f2->GetUserData());
				}

				if (f2->GetUserData())
				{
					((GameObject*)(f2->GetUserData()))->onCollision((GameObject *)f1->GetUserData());
				}
			}
		};

		class DebugDraw : public b2Draw
		{
		public:
			sf::RenderWindow *m_win;
			float m_scale;
			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
			{
				sf::Vertex lines[100];
				if (vertexCount > 99)
					vertexCount = 99;
				for (int i = 0; i < vertexCount; ++i)
				{
					lines[i].position.x = vertices[i].x * m_scale;
					lines[i].position.y = vertices[i].y * m_scale;
					lines[i].color = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
				}
				lines[vertexCount] = lines[0];
				m_win->draw(lines, vertexCount + 1, sf::LineStrip);
			}
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
			{
				DrawPolygon(vertices, vertexCount, color);
			}
			void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
			{
				kage::drawCircle(*m_win, (kf::Vector2)center*m_scale, radius*m_scale, 16, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
			{
				kage::drawCircle(*m_win, (kf::Vector2)center*m_scale, radius*m_scale, 16, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
				kage::drawArrow(*m_win, (kf::Vector2)center*m_scale, (kf::Vector2)center*m_scale + (kf::Vector2)axis*m_scale, 0.05f, 0.1f, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
			{
				kage::drawLine(*m_win, (kf::Vector2)p1*m_scale, (kf::Vector2)p2*m_scale, sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
			void DrawTransform(const b2Transform& xf)
			{
				kage::drawArrow(*m_win, (kf::Vector2)xf.p*m_scale, (kf::Vector2)xf.p*m_scale + (kf::Vector2)xf.q.GetXAxis()*m_scale, 0.05f, 0.1f, sf::Color(255, 0, 0, 255));
				kage::drawArrow(*m_win, (kf::Vector2)xf.p*m_scale, (kf::Vector2)xf.p*m_scale + (kf::Vector2)xf.q.GetYAxis()*m_scale, 0.05f, 0.1f, sf::Color(0, 255, 0, 255));
			}
			void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {}
		};

		class RayCastCallback : public b2RayCastCallback {
		public:
			Hit hit;

			RayCastCallback()
			{
			}

			float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
			{
				if (!hit.hit || fraction < hit.distance)
				{
					GameObject *t = (GameObject *)fixture->GetUserData();
					hit.pos.set(point.x, point.y);
					hit.distance = fraction;
					hit.hit = true;
					hit.gob = t;
					return fraction;
				}
				return 1;
			}
		};

		namespace
		{
			b2World *g_world = 0;
			int g_velocityIterations = 6;
			int g_positionIterations = 2;
			ContactListener g_contactListener;
			DebugDraw g_debugDraw;
		}

		b2World *getWorld()
		{
			return g_world;
		}

		void init(b2Vec2 gravity)
		{
			if (g_world)
			{
				delete g_world;
			}
			g_world = new b2World(gravity);
			g_world->SetContactListener(&g_contactListener);
			g_world->SetDebugDraw(&g_debugDraw);
			g_debugDraw.SetFlags(b2Draw::e_shapeBit);
		}

		void update(float dt)
		{
			g_world->Step(dt, g_velocityIterations, g_positionIterations);
		}

		void gravity(b2Vec2 gravity)
		{
			g_world->SetGravity(gravity);
		}
		
		b2Vec2 gravity()
		{
			return g_world->GetGravity();
		}

		void debugDraw(sf::RenderWindow *win, float scale)
		{
			g_debugDraw.m_win = win;
			g_debugDraw.m_scale = scale;
			g_world->DrawDebugData();
		}

		b2Body *createCircle(kf::Vector2f pos, float radius, float density, float damping, void *userData, b2BodyType type, float restitution)
		{
			b2BodyDef bodyDef;
			bodyDef.position = pos;
			bodyDef.type = type;
			b2Body *body = g_world->CreateBody(&bodyDef);
			b2CircleShape shape;
			shape.m_radius = radius;

			b2FixtureDef fixDef;
			fixDef.density = density;
			fixDef.restitution = restitution;
			fixDef.shape = &shape;
			fixDef.userData = userData;
			body->CreateFixture(&fixDef);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			body->SetLinearDamping(damping);
			return body;
		}

		b2Body *createBox(kf::Vector2f pos, kf::Vector2f size, float density, float damping, void *userData, b2BodyType type, float restitution)
		{
			b2BodyDef bodyDef;
			bodyDef.position = pos;
			bodyDef.type = type;
			b2Body *body = g_world->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);

			b2FixtureDef fixDef;
			fixDef.density = density;
			fixDef.restitution = restitution;
			fixDef.shape = &shape;
			fixDef.userData = userData;
			body->CreateFixture(&fixDef);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			body->SetLinearDamping(damping);
			return body;
		}

		Hit rayCast(kf::Vector2 p1, kf::Vector2 p2)
		{
			RayCastCallback cb;
			g_world->RayCast(&cb, p1, p2);
			return cb.hit;
		}
	}
}
