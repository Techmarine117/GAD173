#include "kage2dutil/gameobject.h"

namespace
{
	long long g_maxId=0;
}


namespace kage
{

	void GameObject::update(float dt)
	{
		if(m_life>0)
		{
			m_life-=dt;
			if(m_life<=0)
			{
				m_dead = true;
				return;
			}
		}
		if(m_physicsStyle == e_psNewtonian)
		{
			if(m_gravity)
				m_velocity += World::gravity()*dt;
			m_velocity += m_force * dt;
			m_position+=m_velocity * dt;
			m_force.set(0,0);
		}
		if(m_physicsStyle == e_psBox2D)
		{
//			m_position.set(m_body->GetPosition().x, 600-m_body->GetPosition().y);
//			m_rotation = m_body->GetAngle();
		}
		if(m_type==1)
			m_rotation = atan2(-m_velocity.x,-m_velocity.y);
	}

	void GameObject::render(sf::RenderWindow &rw)
	{
		if(m_sprite)
		{
			m_sprite->setPosition(m_position.x, m_position.y);
			m_sprite->setRotation(m_rotation*57.29f);
			rw.draw(*m_sprite);
			m_overlap = false;
		}
	}

	GameObject::GameObject()
	{
		m_life = 0;
		m_dead = false;
		m_position.set(0,0);
		m_velocity.set(0,0);
		m_force.set(0,0);
		m_physicsStyle = e_psNone;
		m_sprite = 0;
		m_id = 0;
		m_collide = true;
//		m_body = 0;
		m_rotation = 0;
		m_overlap=false;
		m_gravity = true;
		m_type = 0;
		m_order = 0;
	}

	GameObject::~GameObject()
	{
		//if(m_body)
		//{
		//	m_body->GetWorld()->DestroyBody(m_body);
		//	m_body = 0;
		//}
		delete m_sprite;
		m_sprite = 0;
	}

	GameObject *GameObject::build()
	{
		return new GameObject;
	}

	GameObject &GameObject::position(const kf::Vector2 &pos)
	{
		m_position = pos;
		if(m_physicsStyle == e_psBox2D)
		{
//			m_body->SetTransform(b2Vec2(m_position.x,600-m_position.y),m_rotation);
		}

		return *this;
	}

	GameObject &GameObject::velocity(const kf::Vector2 &vel)
	{
		m_velocity = vel;
		if(m_physicsStyle == e_psBox2D)
		{
//			m_body->SetLinearVelocity(b2Vec2(m_velocity.x,-m_velocity.y));
		}
		return *this;
	}

	GameObject &GameObject::addForce(const kf::Vector2 &force)
	{
		m_force += force;
		if(m_physicsStyle == e_psBox2D)
		{
//			m_body->ApplyForce(b2Vec2(force.x,-force.y),b2Vec2(0,0),true);
		}
		return *this;
	}

	kf::Vector2 GameObject::position()
	{
		return m_position;
	}

	kf::Vector2 GameObject::velocity()
	{
		return m_velocity;
	}

		
	CollisionCallback_t CollisionCallback = 0;

}
