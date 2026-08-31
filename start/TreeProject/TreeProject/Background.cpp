#include "Background.h"
#include "setColor.h"

Background::Background() 
    : GameObject(0.0f, 0.0f) 
{
}

void Background :: update(){

}

void Background :: init(){
	
    SETCOLOR(br.fill_color, 0.847f, 0.843f, 0.839f);



	
	

}

void Background :: draw(){
    graphics::setWindowBackground(br);
}