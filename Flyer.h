﻿
#ifndef _FLYER_H_
#define _FLYER_H_

class Flyer : public GameObject {
private:

public:
	// Collider
	BoxCollider* collHorizonCheck;
	// Animation
	Animation* animFlyer;
	AnimationObject* enemyDestroy;

	// GameObject
	Orb* orb;

	// Parameter
	float speed = 1.0f;

	// status
	bool right = false;
	bool air = true;

	// Constructors
	Flyer ();
	~Flyer();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
