#pragma once
#include "Levels.h"


class StartLevel : public Levels{

	
public:
	void init(); //gives its own implementation to the parent class abstract method init()
	void draw();
	void update();
};
