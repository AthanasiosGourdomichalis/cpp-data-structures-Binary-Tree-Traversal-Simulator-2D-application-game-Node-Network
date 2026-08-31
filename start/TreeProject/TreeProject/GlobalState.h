#pragma once
#include <vector>
#include <string>
#include "Levels.h"
#include "StartLevel.h"
#include "Label.h"
#include "Button.h"

class GlobalState {
private:
    static GlobalState* instance; //the only GlobalState class instance (singleton)
    Levels* currentLevel = nullptr; //Keeps (stores) the current level the user is currently in
    std::string buttonPressed; //keeps (stores) the button pressed by the user in any level
    std::string traversal;//keeps (stores) the traversal method that the user choses for later use
    GlobalState() {}

public:
    const float CANVAS_WIDTH = 1500.0f;
    const float CANVAS_HEIGHT = 1000.0f;
    void setButtonID(const std::string& buttonID) { 
        buttonPressed = buttonID;
    }
    const std::string& getButtonID() const {return buttonPressed;}
    
    ~GlobalState();

    
    static GlobalState* getInstance();
    void init();
    void update(float dt);
    void draw();
    void changeLevel(Levels* newLevel); 
    void setTraversal(const std::string& trav);
    const std::string& getTraversal();
    static void cleanup();
};