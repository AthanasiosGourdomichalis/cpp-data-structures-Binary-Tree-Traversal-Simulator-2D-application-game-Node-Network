#include "sgg/graphics.h"
#include "GlobalState.h"




void draw() {

    GlobalState::getInstance()->draw();
}

void update(float ms) {

    GlobalState::getInstance()->update(ms);
}

int main(int argc, char** argv) {

    //initializes the window
    graphics::createWindow(1200, 800, "Tree Traversal Simulator");
    //set window size and fit
        
    graphics::setCanvasSize(GlobalState::getInstance()->CANVAS_WIDTH, GlobalState::getInstance()->CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    //initisialize the app
    GlobalState::getInstance()->init();
    
    
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);



    
    graphics::startMessageLoop();
    
    GlobalState::getInstance()->cleanup();

    return 0;
}