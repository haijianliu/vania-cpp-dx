﻿
#ifndef _TIME_H_
#define _TIME_H_

class Time {
private:
	DWORD lastTime = 0;
	DWORD currentTime = 0;

	#ifdef _DEBUG
		DWORD lastFPSTime = 0;
		DWORD frameCounter = 0;
	#endif


public:

	#ifdef _DEBUG
		int countFPS = 0;
	#endif

	float deltaTime = 0;

	Time();
	~Time();
	void Start();
	void SetTime();
	void Update();
	bool CheckFPS(int frameRate);
};


#endif
