#include"Levels.h"


void Levels:: draw() {
	for (GameObject* obj : objects) {
		obj->draw();
	}
}
void Levels:: update() {
	for (GameObject* obj : objects) {
		obj->update();
	}
}

void Levels::addGameObject(GameObject* obj) {
	objects.push_back(obj);
	obj->init();//to initialize the object when added to the vector
}

float Levels::getOffset(float centerX, float fontSize, const std::string& text) {//to center the label to the according x,y coordinations


	float charWidthInPixels = fontSize * 0.45f;// Estimate character width from its size
	float totalTextWidth = text.length() * charWidthInPixels;// Calculate the total width in pixels of the text
	float startX = centerX - (totalTextWidth / 2.0f);// get the StartX by going left half the calculated text width

	return startX;
}