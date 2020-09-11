#pragma once
#include <vector>
#include "app.h"
#include"Scenes.h"
	static std::vector<Scenes*> scenes;
class SceneManager :public App
{

public:
	SceneManager();
	virtual ~SceneManager();
	void AddScene(Scenes* scene);
	void RemoveScene();
	static  void Run(int index);

	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
};

