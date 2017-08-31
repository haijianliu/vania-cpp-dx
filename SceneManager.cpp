﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneManager::SceneManager() {
	// Camera
	this->camera = GetCamera();
	// Resources
	this->resources = GetResources();

	// UIObject
	this->uiEnergyBG = new UIObject(-144.0f,-104.0f,112.0f,32.0f);
	// GameObject
	this->player = new Player();
	// Scene
	scenes.push_back(new Scene00());
	scenes.push_back(new Scene01());
	scenes.push_back(new Scene02());

	// active Scene
	SceneManager::SetActiveScene(0);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneManager::~SceneManager() {
	// UIObject
	delete this->uiEnergyBG;
	// Player
	delete this->player;
	// Scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		delete this->scenes[i];
	}
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneManager::Start() {
	// set SceneManager in scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->sceneManager = this;
	}
	// Camera target
	this->camera->target = this->player;

	// Resources
	this->uiEnergyBG->sprite->texture = this->resources->texUIEnergyBG;

	// Scene Start
	// this->resources->audSceneBGM->Play();
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->Start();
	}
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneManager::Update() {
	this->scenes[this->activeScene]->Update();
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void SceneManager::Draw() {
	this->scenes[this->activeScene]->Draw();
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void SceneManager::SetActiveScene(unsigned int i) {
	this->activeScene = i;
	this->camera->activeRange = i;
}
