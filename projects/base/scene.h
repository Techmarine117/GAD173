#pragma once
#include <iostream>
class scene
{

	scene();
	scene(std::string sceneName);
	~scene();
	virtual void Init();
	virtual void Run();
	virtual void Close();

	std::string sceneName;
};

