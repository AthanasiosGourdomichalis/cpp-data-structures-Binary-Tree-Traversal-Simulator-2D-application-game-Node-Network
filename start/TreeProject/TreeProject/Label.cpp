#include "Label.h"
#include "setColor.h"



void Label :: init(){
	label_br.fill_opacity = 1.0f;
	label_br.outline_opacity = 1.0f;
	SETCOLOR(label_br.fill_color, r, g, b);
	SETCOLOR(label_br.outline_color, 0.0f, 0.0f, 0.0f);
    }
void Label :: draw(){
    graphics::drawText(pos_x,pos_y, size, text, label_br);
}
void Label::update() {

}

