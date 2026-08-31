#include "GlobalState.h"
#include "Background.h"
#include <iostream>     

GlobalState* GlobalState::instance = nullptr;


GlobalState::~GlobalState() {//deletes the current level
    delete currentLevel;
}


GlobalState* GlobalState::getInstance() {//creates or returns the singleton instance of GlobalState
    if (!instance) {
        instance = new GlobalState();
    }
    return instance;
}


void GlobalState::init() {
   
    graphics::setFont("assets/font.ttf"); //sets the application's font 
    changeLevel(new StartLevel()); //sets the current level as 'Start Level' at the start of the application
}


void GlobalState::update(float dt) {
    currentLevel->update();

}


void GlobalState::draw() {
    currentLevel->draw();
}

void GlobalState :: changeLevel(Levels* newLevel) {//if a level is active delete it and point to the newLevel
    if (currentLevel) {
        delete currentLevel;
        
    }
    currentLevel = newLevel;
    currentLevel->init();//initializes the new level
}


void GlobalState::cleanup() { //destroyes the only GlobalState class instance
    if (instance) {
        delete instance;//calls  ~GlobalState() for the singleton 
        instance = nullptr;
    }
}

void GlobalState::setTraversal(const std::string& trav) {
    traversal = trav;
};
const std::string& GlobalState::getTraversal(){
    return traversal;
};