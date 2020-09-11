#include "cmath"
#include "kf/kf_log.h"
#include "SceneManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "GameEditor.h"

using namespace std;

int main()
{
	SceneManager sceneManager;
	MainMenu* mainMenu = new MainMenu();
	Game* game = new Game();
	GameEditor* gameEditor = new  GameEditor();
	sceneManager.AddScene(mainMenu);
	sceneManager.AddScene(game);
	sceneManager.AddScene(gameEditor);
	
	
	sceneManager.run();
	return 0;
}
