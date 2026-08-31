#pragma once
#include "Widget.h"
#include <string>
#include "sgg/graphics.h"
#include "setColor.h"
#include "Interactable.h"


class Button : public Widget,public Interactable {// A class for the application's Buttons
protected:
	const float width; //the button's dimensions 
	const float height;
	const std::string id; //the button's id is used to ditermine which button was clicked by the user 
	graphics::Brush button_br; //brush used for the Button's image, colour, etc.
	graphics::Brush shadow_br; //brush used for the Button's shadow 

public:
	Button(float x, float y, float w, float h, float r, float g, float b, const std::string& image, const std::string& b_id) : 
	Widget(x, y, r, g, b, image), width(w), height(h), id(b_id) {};

	const std::string& getID() const { return id; } //returns the button's id
	void init();
	void draw();
	void update();
	bool contains() override; 
	
};