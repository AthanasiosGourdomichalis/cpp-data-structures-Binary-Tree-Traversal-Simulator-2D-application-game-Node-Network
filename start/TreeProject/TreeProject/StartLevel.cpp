#include "StartLevel.h"
#include "EditingLevel.h"
#include "GameObject.h"
#include "GlobalState.h"

void StartLevel::init() {
    //set background
    addGameObject(new Background(0.125f, 0.165f, 0.196f));
    //"Select tree traversal"
    addGameObject(new Label(getOffset(800.0f, 70.0f, "Select Tree Traversal"), 100.0f, 0.918f, 0.878f, 0.812f, 70.0f, "Select Tree Traversal"));
    //"preorder" button and its label
    addGameObject(new Label(getOffset(450.0f, 50.0f, "preorder"), 230.0f, 0.918f, 0.878f, 0.812f, 50.0f, "preorder"));
    addGameObject(new Button(450.0f, 400.0f, 512.0f, 256, 1.0f, 1.0f, 1.0f, "assets/preorder.png", "preorder"));
    //"inorder" button and its label
    addGameObject(new Label(getOffset(1050.0f, 50.0f, "inorder"), 230.0f, 0.918f, 0.878f, 0.812f, 50.0f, "inorder"));
    addGameObject(new Button(1050.0f, 400.0f, 512.0f, 256.0f, 1.0f, 1.0f, 1.0f, "assets/inorder.png", "inorder"));
    //"postorder" button and its label
    addGameObject(new Label(getOffset(450.0f, 50.0f, "postorder"), 640.0f, 0.918f, 0.878f, 0.812f, 50.0f, "postorder"));
    addGameObject(new Button(450.0f, 800.0f, 512.0f, 256.0f, 1.0f, 1.0f, 1.0f, "assets/postorder.png", "postorder"));
	//"level-order" button and its label
    addGameObject(new Label(getOffset(1050.0f, 50.0f, "level-order"), 640.0f, 0.918f, 0.878f, 0.812f, 50.0f, "level-order"));
    addGameObject(new Button(1050.0f, 800.0f, 512.0f, 256.0f, 1.0f, 1.0f, 1.0f, "assets/level-order.png", "levelorder"));
}
void StartLevel::draw() {
    Levels::draw(); //calls base class' draw() method to draw the gameObjects
}

void StartLevel::update(){
    Levels::update(); //calls base class' update() to update the gameObjects
    const std::string& btn = GlobalState::getInstance()->getButtonID();//which button is pressed
    if(btn =="preorder"|| btn == "inorder"||
        btn == "postorder"|| btn == "levelorder"){//if one of the above
        GlobalState::getInstance()->setTraversal(btn);//sets the chosen traversal in GlobalState singleton instance
        GlobalState::getInstance()->setButtonID("");//resets button_pressed
        GlobalState::getInstance()->changeLevel(new EditingLevel());//changes to editing level
	
    }
}