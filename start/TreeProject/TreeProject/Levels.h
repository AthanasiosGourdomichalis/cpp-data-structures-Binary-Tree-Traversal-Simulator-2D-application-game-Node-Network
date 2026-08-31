#pragma once
#include "GameObject.h"
#include "Label.h"
#include "Button.h"
#include "Background.h"
#include <vector>
#include <string>
class Levels { //Base class for the application's different Levels 
	std::vector<GameObject*> objects; //Each level's window graphical object
protected:
	
public:
	
	Levels() {};
	virtual ~Levels() { //to call the destructor of the subclass first (bacause of Levels* currentLevel in "GlobalState.h") 
		for (GameObject* obj : objects) {
			delete obj;
		}
	};

	virtual void init()=0; //to obligate every subclass to implement each own init() method
	virtual void draw();
	virtual void update();
	float getOffset(float centerX, float fontSize, const std::string& text); 
	void addGameObject(GameObject* obj);



};
