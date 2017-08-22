﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Particle::Particle() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(4.0f,4.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,32,32);
	// Default GameObject active == true
	this->gameObject->active = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Particle::~Particle() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Particle::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Particle::Update() {
	/* Destroy
	..............................................................................*/
	Destroy(this->gameObject, this->startLifeTime);

	/* Transform
	..............................................................................*/
	this->transform->position.x += cos(this->startAngle) * this->startSpeed * this->time->deltaTime;
	this->transform->position.y += sin(this->startAngle) * this->startSpeed * this->time->deltaTime;

	if (this->sizeOverLifeTime) {
		this->transform->scale.x -= this->startSize / this->startLifeTime * this->time->deltaTime;
		this->transform->scale.y -= this->startSize / this->startLifeTime * this->time->deltaTime;
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Particle::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Particle::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void Particle::Instantiate(Transform* transform) {
	this->gameObject->active = true;
	this->birthTime = this->time->currentTime;
	this->transform->position = transform->position;
	this->startAngle = RandomRange(0.0f,2.0f*PI);
	this->startLifeTime = RandomRange(this->startLifeTimeRange.x, this->startLifeTimeRange.y);
	this->startSpeed = RandomRange(this->startSpeedRange.x, this->startSpeedRange.y);
	this->startSize = RandomRange(this->startSizeRange.x, this->startSizeRange.y) * UNIT_TO_PIXEL;
	this->transform->scale = Float2D(this->startSize, this->startSize);
}
