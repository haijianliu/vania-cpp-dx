﻿
#include "main.h"
#include "Time.h"


Time::Time() {

}

Time::~Time() {

}

void Time::Start() {
	timeBeginPeriod(1);
	this->lastTime = timeGetTime();

	#ifdef _DEBUG
		this->lastFPSTime = timeGetTime();
	#endif
}

// in a game loop but not in FPS check loop
void Time::SetTime() {
	this->currentTime = timeGetTime();

	#ifdef _DEBUG
	// reset frame counter
		if ((this->currentTime - this->lastFPSTime) >= 1000) {
			this->countFPS = (this->frameCounter * 1000) / (this->currentTime - this->lastFPSTime);
			this->lastFPSTime = this->currentTime;
			this->frameCounter = 0;
		}
	#endif
}


// in FPS check loop
void Time::Update() {
	this->deltaTime = ((float)this->currentTime - (float)this->lastTime) / 1000.0f;
	this->lastTime = this->currentTime;

	#ifdef _DEBUG
		this->frameCounter ++;
	#endif
}


bool Time::CheckFPS(int frameRate) {
	if (this->currentTime - this->lastTime >= (unsigned)1000 / frameRate) {
		return true;
	}
	else {
		return false;
	}
}
