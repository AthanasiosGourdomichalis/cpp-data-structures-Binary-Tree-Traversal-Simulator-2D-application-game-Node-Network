#pragma once
#include "GameObject.h"
#include "sgg/graphics.h"
#include "Interactable.h"
#include <string>

class Widget : public GameObject {//Generic (interface) Base Class for the application's GUI Elements 
protected:
	std:: string image; //element's image 
	float r;
	float g;
	float b;
	
public:
	Widget(float x, float y, float r = 1.0f, float g = 1.0f, float b = 1.0f, const std::string& img = "") //default arguments colour:white , img = "" (no image)
		: GameObject(x, y), r(r), g(g), b(b), image(img) {
		
	}; 
	~Widget() {}; 
	//abstract methods
	virtual void draw()=0;
	virtual void init()=0;
	virtual void update()=0;
};