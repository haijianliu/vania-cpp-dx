﻿
#ifndef _BOSS_H_
#define _BOSS_H_

class Boss : public GameObject {
private:

public:
	// Camera
	Camera* camera;

	// Collider
	BoxCollider* collider;
	// Animation

	// GameObject
	BossCore* core;
	std::vector<DeathWall*> deathWallsLeft;
	std::vector<DeathWall*> deathWallsRight;
	// UIObject
	UIObject* uiBossBG;
	UIObject* uiLife;

	// Target
	GameObject* target;

	// Parameter
	float hp = 1000.0f;
	float deathWallRange = 1.6f;

	// status
	bool awake = false;
	bool freeze = true;
	bool intro = false;

	// Constructors
	Boss ();
	~Boss();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
