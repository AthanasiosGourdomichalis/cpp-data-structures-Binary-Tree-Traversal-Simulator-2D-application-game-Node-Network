#include "Button.h"
#include "sgg/graphics.h"
#include "GlobalState.h"
#include "Levels.h"
using namespace std;



void Button::init() {
	button_br.fill_opacity = 1.2f;
	button_br.outline_opacity = 0.0f;
	button_br.texture = image;
	SETCOLOR(button_br.fill_color, r, g, b);
	SETCOLOR(button_br.outline_color, 0.0f, 0.0f, 0.0f);
	shadow_br.outline_opacity = 0.0f;
	shadow_br.fill_opacity = 0.5f;
	SETCOLOR(shadow_br.fill_color, 0.0f, 0.0f, 0.0f);

}



void Button::draw() {
	if (contains()) {//if we are above the button with the mouse (hover)
		graphics::setScale(1.05f, 1.05f); //enlarge the button's dimensions ( 5% )
	}
	if(image==" "){ graphics::drawRect(pos_x + 5.0f, pos_y + 5.0f, width, height, shadow_br); }//if the button doesn't have an image, then add a shadow
	graphics::drawRect(pos_x, pos_y, width, height, button_br);
	graphics::resetPose();//reset the button's dimensions when not above it
	
}

bool Button::contains() { 
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	return (pos_x - width / 2.0f <= mx && mx <= pos_x + width / 2.0f) && (pos_y - height / 2.0f <= my && my <= pos_y + height / 2.0f);
}



void Button::update() {
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (contains()) {//if above the button (hover)
		if (image != " ") {
			SETCOLOR(button_br.fill_color, 0.85f, 0.90f, 1.0f);//change the color to hover color if the button is an image
		}
		else {
			SETCOLOR(button_br.fill_color, 1.0f, 0.76f, 0.0f);//change the color to hover color if the button is NOT an image
		}
		if (ms.button_left_pressed) {//if button pressed
			graphics::playSound("assets/click.wav", 1.0f, false);//plays click sound
			GlobalState::getInstance()->setButtonID(getID());//updates the button_pressed in GlobalState to know which button was pressed last
			
		}
	}else
		SETCOLOR(button_br.fill_color, r, g, b);//reset button color
		
	
	

}