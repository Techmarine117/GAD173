#include "kage2dutil/world.h"
#include "kage2dutil/gameobject.h"

namespace
{
	long long g_maxId=1;
}


namespace kage
{

	namespace World
	{
		const int c_divisions = 10;

		std::map<long long, GameObject *> worldObjects;
		long long worldHighestID = 0;
		kf::Vector2 worldGravity(0,0);

		kf::Vector2 gravity()
		{
			return worldGravity;
		}

		void gravity(const kf::Vector2 &grav)
		{
			worldGravity = grav;
		}

		long long newID()
		{
			return ++worldHighestID;
		}

		void update(float dt)
		{
			std::vector<long long> deadobjects;
			for(std::map<long long, GameObject *>::iterator it = worldObjects.begin(); it!= worldObjects.end(); ++it)
			{
				it->second->update(dt);
				if(it->second->m_dead)
				{
					deadobjects.push_back(it->first);
				}
			}


			if(CollisionCallback)
			{
				std::vector<GameObject *> cells[c_divisions][c_divisions];

				int cx = 0;
				int cy = 0;
				int dx = 1920/c_divisions;
				int dy = 1080/c_divisions;

				for(std::map<long long, GameObject *>::iterator it = worldObjects.begin();it != worldObjects.end();it++)
				{
					if(it->second->m_collide && !it->second->m_dead)
					{
						int sx = int((it->second->m_position.x - it->second->m_sprite->getGlobalBounds().width * 0.5)/dx);
						int sy = int((it->second->m_position.y - it->second->m_sprite->getGlobalBounds().height * 0.5)/dy);
						int ex = int((it->second->m_position.x + it->second->m_sprite->getGlobalBounds().width * 0.5)/dx);
						int ey = int((it->second->m_position.y + it->second->m_sprite->getGlobalBounds().height * 0.5)/dy);
						for(int y=sy;y<=ey;y++)
						{
							for(int x=sx;x<=ex;x++)
							{
								if(x>=0 && x< c_divisions && y>=0 && y<c_divisions)
								{
									cells[y][x].push_back(it->second);
								}
							}
						}
					}
				}
				for(int y=0;y<c_divisions;y++)
				{
					for(int x=0;x<c_divisions;x++)
					{
						for(int i=0;i<cells[y][x].size();i++)
						{
							for(int j=i;j<cells[y][x].size();j++)
							{
								if(i!=j && !cells[y][x][i]->m_dead && !cells[y][x][j]->m_dead)
								{
									if(cells[y][x][i]->m_position.x + cells[y][x][i]->m_sprite->getGlobalBounds().width * 0.35f > cells[y][x][j]->m_position.x - cells[y][x][j]->m_sprite->getGlobalBounds().width * 0.35f
										&& cells[y][x][i]->m_position.x - cells[y][x][i]->m_sprite->getGlobalBounds().width * 0.35f < cells[y][x][j]->m_position.x + cells[y][x][j]->m_sprite->getGlobalBounds().width * 0.35f
										&& cells[y][x][i]->m_position.y + cells[y][x][i]->m_sprite->getGlobalBounds().height * 0.35f > cells[y][x][j]->m_position.y - cells[y][x][j]->m_sprite->getGlobalBounds().height * 0.35f
										&& cells[y][x][i]->m_position.y - cells[y][x][i]->m_sprite->getGlobalBounds().height * 0.35f < cells[y][x][j]->m_position.y + cells[y][x][j]->m_sprite->getGlobalBounds().height * 0.35f)
									{
										CollisionCallback(cells[y][x][i],cells[y][x][j]);
									}
								}
							}
						}
					}
				}
			}


			for(unsigned int i=0;i<deadobjects.size();++i)
			{
				std::map<long long, GameObject *>::iterator it = worldObjects.find(deadobjects[i]);
				if(it!=worldObjects.end())
				{
					delete it->second;
					worldObjects.erase(it);
				}
			}
		}
		
		bool sortOrder(GameObject *g1, GameObject *g2)
		{
			return g1->m_order < g2->m_order;
		}
		
		void render(sf::RenderWindow &rw)
		{
			std::vector<GameObject *> objects(worldObjects.size());
			int i = 0;
			for(std::map<long long, GameObject *>::iterator it = worldObjects.begin(); it!= worldObjects.end(); ++it)
			{
				objects[i] = it->second;
			}
			std::sort(objects.begin(), objects.end(),sortOrder);
			for (i = 0; i < objects.size(); ++i)
			{
				objects[i]->render(rw);
			}
		}

		void add(GameObject *obj)
		{
			if (obj->m_id == 0)
			{
				obj->m_id = newID();
			}
			auto it = worldObjects.find(obj->m_id);
			if (it == worldObjects.end())
			{
				worldObjects[obj->m_id] = obj;
			}
		}

		void remove(GameObject *obj)
		{
			auto it = worldObjects.find(obj->m_id);
			if (it != worldObjects.end())
			{
				delete it->second;
				worldObjects.erase(it);
			}
		}

	}



}
