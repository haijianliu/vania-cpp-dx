﻿
#include "Engine.h"


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Resources::Resources() {
	// Animation Object
	this->enemyDestroy = new AnimationObject(32,32,6,1,4);
	// Audio
	for (unsigned int i = 0; i < 4; i++) {
		this->audShoot.push_back(new Audio("assets/Sound/SE/sfx_wpn_laser8.wav"));
	}
	this->audSceneBGM = new Audio("assets/Sound/BGM/Venus.wav");
	this->audSceneBGM->loop = true;
	this->audLanding = new Audio("assets/Sound/SE/sfx_movement_jump14_landing.wav");
	this->audPlayerHurt = new Audio("assets/Sound/SE/sfx_sounds_error14.wav");
	this->audPlayerNoAmmo = new Audio("assets/Sound/SE/sfx_wpn_noammo1.wav");
	this->audEnemyDamage = new Audio("assets/Sound/SE/sfx_sounds_impact1.wav");
	this->audEnemyDestroy = new Audio("assets/Sound/SE/sfx_exp_shortest_soft9.wav");
	// ParticleSystem
	this->fxTail = new ParticleSystem(100);
	this->fxTail->rateOverTime = false;
	this->fxTail->SetStartLifeTimeRange(1.0f,2.0f);
	this->fxTail->SetStartSpeedRange(0.02f,0.2f);
	this->fxTail->SetStartSizeRange(0.01f,0.02f);
	this->fxTail->SetStartAngleRange(0.0f,2.0f*PI);
	this->fxTail->SetGravity(0.0f);
	this->fxTail->SetColor(63,140,242,255);
	this->fxDestroy = new ParticleSystem(40);
	this->fxDestroy->SetStartLifeTimeRange(0.1f,0.4f);
	this->fxDestroy->SetStartSpeedRange(0.2f,1.0f);
	this->fxDestroy->SetStartSizeRange(0.05f,0.1f);
	this->fxDestroy->SetGravity(0.0f);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Resources::~Resources() {
	// Texture
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
	if (this->texBlock.texture != NULL) this->texBlock.texture->Release();
	if (this->texUIEnergyBG.texture != NULL) this->texUIEnergyBG.texture->Release();
	// AnimationObject
	delete this->enemyDestroy;
	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		delete this->audShoot[i];
	}
	delete this->audSceneBGM;
	delete this->audLanding;
	delete this->audPlayerHurt;
	delete this->audPlayerNoAmmo;
	delete this->audEnemyDamage;
	delete this->audEnemyDestroy;
	// ParticleSystem
	delete this->fxDestroy;
	delete this->fxTail;
}


/*------------------------------------------------------------------------------
< Start > before SceneManager Start && before GameObject PreStart
------------------------------------------------------------------------------*/
void Resources::Start() {
	// GetDevice
	this->device = GetDevice();

	// LoadTexture
	Resources::LoadTexture(&this->texDefault);
	Resources::LoadTexture(&this->texTile);
	Resources::LoadTexture(&this->texPlayerIdle);
	Resources::LoadTexture(&this->texPlayerShoot);
	Resources::LoadTexture(&this->texPlayerRun);
	Resources::LoadTexture(&this->texPlayerJump);
	Resources::LoadTexture(&this->texPlayerDuck);
	Resources::LoadTexture(&this->texPlayerDuckFire);
	Resources::LoadTexture(&this->texPlayerHurt);
	Resources::LoadTexture(&this->texBullet);
	Resources::LoadTexture(&this->texFxDestroy);
	Resources::LoadTexture(&this->texEnemyDestroy);
	Resources::LoadTexture(&this->texCrabWalk);
	Resources::LoadTexture(&this->texBlock);
	Resources::LoadTexture(&this->texUIEnergyBG);
	// AnimationObject
	this->enemyDestroy->animation->sprite->device = this->device;
	this->enemyDestroy->animation->sprite->texture = this->texEnemyDestroy;
	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		this->audShoot[i]->LoadAudio();
	}
	this->audSceneBGM->LoadAudio();
	this->audLanding->LoadAudio();
	this->audPlayerHurt->LoadAudio();
	this->audPlayerNoAmmo->LoadAudio();
	this->audEnemyDamage->LoadAudio();
	this->audEnemyDestroy->LoadAudio();
	// ParticleSystem
	this->fxDestroy->LinkTexture(this->texFxDestroy);
	this->fxTail->LinkTexture(this->texDefault);
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void Resources::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
}