﻿
#ifndef _GROUND_H_
#define _GROUND_H_

class Ground {
private:
	Vertex2D vertex[4] = {Vertex2D()};
	Sprite* sprite;

public:
	Transform* transform;

	Ground(Sprite* sprite);
	virtual ~Ground();
	void Start();
	void Update();
	void Draw();
};

#endif
