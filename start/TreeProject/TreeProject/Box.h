#pragma once
#include "sgg/graphics.h"
#include "SETCOLOR.h"
#include <string>
#include "GameObject.h"
//used in the visualization of the tree's nodes order to create an array
class Box :public GameObject{ 
	
	bool box_active;//which cell of the array is active
	const std::string letter;// nodes id
	graphics::Brush box_br;
	graphics::Brush letter_br;
public:
	Box(float x, float y, const std::string& txt) :GameObject(x,y), letter(txt) {
		box_active = false;// starts as not active
	};
	void init() {
		box_br.fill_opacity = 0.8f;
		box_br.gradient = true;
		box_br.gradient_dir_u = 0.5f;
		box_br.gradient_dir_v = 0.5f;
		box_br.outline_opacity = 1.0f;
		SETCOLOR(box_br.fill_color, 0.60f, 0.80f, 1.00f);
		SETCOLOR(box_br.outline_color, 0.0f, 0.0f, 0.0f);
		letter_br.outline_opacity = 0.0f;
		letter_br.fill_opacity = 1.0f;
		SETCOLOR(letter_br.fill_color, 0.13f, 0.20f, 0.28f);

	}

	void draw() {
		graphics::drawRect(pos_x, pos_y,80.0f, 40.0f, box_br);
		graphics::drawText(pos_x-12.0f, pos_y+15.0f, 30.0f, letter, letter_br);//pos_x-12, pos_y+15 to be in the center of the array cell

	}

	void update() {
		if (box_active) {//changes the color to yellow-gold
			box_br.outline_width = 3.0f;
			SETCOLOR(box_br.outline_color, 1.0f, 0.9f, 0.2f);
			SETCOLOR(box_br.fill_color, 0.9f, 0.7f, 0.2f);
			SETCOLOR(box_br.fill_secondary_color, 0.7f, 0.5f, 0.1f);

		}
		else {
			box_br.outline_width = 1.0f;//reset the color to blue
			SETCOLOR(box_br.outline_color, 0.1f, 0.2f, 0.4f);
			SETCOLOR(box_br.fill_color, 0.58f, 0.71f, 0.76f);
			SETCOLOR(box_br.fill_secondary_color, 0.45f, 0.60f, 0.65f);

		}
	}

	void setActive(bool flag) {//to change the box's state
		box_active = flag;
	}
};