﻿
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

class SceneManager {
private:

public:
	// Camera
	Camera* camera;
	// Resources
	Resources* resources;

	// UIObject
	UIObject* uiEnergyBG;
	UIObject* uiEnergy;
	// GameObject
	Player* player;
	// Scene
	unsigned int activeScene;
	std::vector<Scene*> scenes;

	SceneManager();
	~SceneManager();

	void Start();
	void Update();
	void Draw();

	// Functions
	void SetActiveScene(unsigned int i);
};

#endif
