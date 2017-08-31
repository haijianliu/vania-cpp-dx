﻿
#ifndef _SCENE_H_
#define _SCENE_H_

class Scene {
private:
	// global GameObjects and Colliders parameter
	std::vector<GameObject*>* gpGameObjects;
	std::vector<BoxCollider*>* gpColliders;
	unsigned int startGameObjectsSize;
	unsigned int startCollidersSize;

public:
	// Scene GameObjects and Colliders
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;
	// SceneManager
	SceneManager* sceneManager;
	// Camera
	Camera* camera;

	// Map Data
	Int2D mapSize = Int2D(147,45);
	int tilePixel = 16;
	Int2D tileSize = Int2D(384/16,192/16);
	// Map path
	const char* cameraPath = "map/scene_Scene-Null";
	const char* rangePath = "map/scene_Scene-Null";
	const char* crabPath = "map/scene_Scene-Null";
	const char* aiPath = "map/scene_Scene-Null";
	const char* orbPath = "map/scene_Scene-Null";
	const char* blockPath = "map/scene_Scene-Null";
	const char* groundPath = "map/scene_Scene-Null";
	const char* backGroundPath = "map/scene_Scene-Null";
	// Map Object
	std::vector<NoneObject*> range;
	std::vector<Crab*> crabs;
	std::vector<Ground*> ai;
	std::vector<Orb*> orbs;
	std::vector<Block*> blocks;
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;

	Scene();
	virtual ~Scene();

	virtual void Start();
	void SetScene();
	virtual void Update();
	void Draw();

	// Functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	bool LoadMapData(const char* path, std::vector<Int2D>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);
	void SetPosition(GameObject* gameObject, int mapID);
};

#endif
