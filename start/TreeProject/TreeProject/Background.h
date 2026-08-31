#pragma once
#include "Widget.h"
#include "sgg/graphics.h"
#include "setColor.h"

class Background : public GameObject { //to use it as a gameobject class instance in each level's vector (polymorphism)
    graphics::Brush br;
	float r, g, b; 
public:
	Background(float r, float g,float b): GameObject(0.0f, 0.0f), r(r), g(g), b(b) {};
	void update() override {}; 
	void init() override {SETCOLOR(br.fill_color, r, g,b );};
	void draw() override {graphics::setWindowBackground(br);};//sets each level's background color
};
