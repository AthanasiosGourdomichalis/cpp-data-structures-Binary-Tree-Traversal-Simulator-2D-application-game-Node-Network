#pragma once
#include "Widget.h"
#include <string>
#include "setColor.h"

class Label : public Widget{ //class used for the application's graphic Labels and Texts 
    protected:
	graphics::Brush label_br;
	const float size; //the text's size 
	std:: string text;

public:
	Label(float x, float y,float r, float g, float b, float sz, const std:: string& txt) : Widget(x, y, r, g, b, ""), size(sz), text(txt) {};// img = "" (text doesn't have an image)
	void init(){
		label_br.fill_opacity = 1.0f;
		label_br.outline_opacity = 1.0f;
		SETCOLOR(label_br.fill_color, r, g, b);
		SETCOLOR(label_br.outline_color, 0.0f, 0.0f, 0.0f);
	};
	void draw() {graphics::drawText(pos_x, pos_y, size, text, label_br);};
	void update() {};
	void setText(const std::string& newText)  { text = newText; }
	void setX(float x) { pos_x = x; }
};
