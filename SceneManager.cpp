﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneManager::SceneManager() {
	// Player
	this->player = new Player();
	// Particle
	this->fxDestroy = new ParticleSystem(40);
	this->fxTail = new ParticleSystem(100);
	// Audio
	for (unsigned int i = 0; i < 4; i++) {
		this->audShoot.push_back(new Audio("assets/Sound/SE/sfx_wpn_laser8.wav"));
	}
	this->audSceneBGM = new Audio("assets/Sound/BGM/Venus.wav");
	this->audSceneBGM->loop = true;
	this->audLanding = new Audio("assets/Sound/SE/sfx_movement_jump14_landing.wav");
	this->audEnemyDamage = new Audio("assets/Sound/SE/sfx_sounds_damage3.wav");
	this->audEnemyDestroy = new Audio("assets/Sound/SE/sfx_exp_shortest_soft9.wav");
	// Animation Object
	this->enemyDestroy = new AnimationObject(64,64,6,1,4);
	// Camera
	this->camera = GetCamera();
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
	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		delete this->audShoot[i];
	}
	delete this->audSceneBGM;
	delete this->audLanding;
	delete this->audEnemyDamage;
	delete this->audEnemyDestroy;
	// Player
	delete this->player;
	// Particle
	delete this->fxDestroy;
	delete this->fxTail;
	// Scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		delete this->scenes[i];
	}
	// delete Texture
	if (this->texDefault.texture != NULL) this->texDefault.texture->Release();
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerShoot.texture != NULL) this->texPlayerShoot.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();
	if (this->texPlayerDuck.texture != NULL) this->texPlayerDuck.texture->Release();
	if (this->texPlayerDuckFire.texture != NULL) this->texPlayerDuckFire.texture->Release();
	if (this->texPlayerHurt.texture != NULL) this->texPlayerHurt.texture->Release();
	if (this->texBullet.texture != NULL) this->texBullet.texture->Release();
	if (this->texFxDestroy.texture != NULL) this->texFxDestroy.texture->Release();
	if (this->texEnemyDestroy.texture != NULL) this->texEnemyDestroy.texture->Release();
	if (this->texCrabWalk.texture != NULL) this->texCrabWalk.texture->Release();
	// Animation Object
	delete this->enemyDestroy;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneManager::Start() {
	// GetDevice
	this->device = GetDevice();
	// set SceneManager in scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->sceneManager = this;
	}
	// Camera target
	this->camera->target = this->player;

	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		this->audShoot[i]->LoadAudio();
		this->player->audShoot.push_back(this->audShoot[i]);
	}
	this->audSceneBGM->LoadAudio();
	this->audLanding->LoadAudio();
	this->player->audLanding = this->audLanding;
	this->audEnemyDamage->LoadAudio();
	this->audEnemyDestroy->LoadAudio();
	// LoadTexture
	SceneManager::LoadTexture(&this->texDefault);
	SceneManager::LoadTexture(&this->texTile);
	SceneManager::LoadTexture(&this->texPlayerIdle);
	SceneManager::LoadTexture(&this->texPlayerShoot);
	SceneManager::LoadTexture(&this->texPlayerRun);
	SceneManager::LoadTexture(&this->texPlayerJump);
	SceneManager::LoadTexture(&this->texPlayerDuck);
	SceneManager::LoadTexture(&this->texPlayerDuckFire);
	SceneManager::LoadTexture(&this->texPlayerHurt);
	SceneManager::LoadTexture(&this->texBullet);
	SceneManager::LoadTexture(&this->texFxDestroy);
	SceneManager::LoadTexture(&this->texEnemyDestroy);
	SceneManager::LoadTexture(&this->texCrabWalk);
	// Link device && texture
	this->player->animIdle->sprite->device = this->device;
	this->player->animIdle->sprite->texture = this->texPlayerIdle;
	this->player->animShoot->sprite->device = this->device;
	this->player->animShoot->sprite->texture = this->texPlayerShoot;
	this->player->animRun->sprite->device = this->device;
	this->player->animRun->sprite->texture = this->texPlayerRun;
	this->player->animJump->sprite->device = this->device;
	this->player->animJump->sprite->texture = this->texPlayerJump;
	this->player->animDuck->sprite->device = this->device;
	this->player->animDuck->sprite->texture = this->texPlayerDuck;
	this->player->animDuckFire->sprite->device = this->device;
	this->player->animDuckFire->sprite->texture = this->texPlayerDuckFire;
	this->player->animHurt->sprite->device = this->device;
	this->player->animHurt->sprite->texture = this->texPlayerHurt;
	this->fxDestroy->LinkTexture(this->texFxDestroy);
	this->fxTail->LinkTexture(this->texDefault);
	for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
		this->player->bullets[i]->sprite->texture = this->texBullet;
		this->player->bullets[i]->fxDestroy = this->fxDestroy;
		this->player->bullets[i]->fxTail = this->fxTail;
	}
	// Animation Object
	this->enemyDestroy->animation->sprite->device = this->device;
	this->enemyDestroy->animation->sprite->texture = this->texEnemyDestroy;

	// scene->Start
	// this->audSceneBGM->Play();
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
< LoadTexture >
------------------------------------------------------------------------------*/
void SceneManager::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
}

void SceneManager::SetActiveScene(unsigned int i) {
	this->activeScene = i;
	this->camera->activeRange = i;
}
