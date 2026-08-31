#include "EditingLevel.h"
#include "StartLevel.h"
#include "GlobalState.h"
#include "VisualizationLevel.h"


void EditingLevel::init() {
	//set background
    addGameObject(new Background(0.125f, 0.165f, 0.196f));

    //"Back" button and its label 
    addGameObject(new Label(getOffset(210, 30, "Go to Home Page"), 850, 0.616f, 0.698f, 0.749f, 30, "Go to Home Page"));
    addGameObject(new Button(200,900 , 100, 50, 0.322f, 0.427f, 0.510f, " ", "Back"));
    addGameObject(new Label(getOffset(200,20,"Back"), 900, 0.867f, 0.902f, 0.929f, 20, "Back"));

    //"Visualize" button and its label 
    addGameObject(new Button(1340, 900, 100, 50, 0.322f, 0.427f, 0.510f, " ", "Visualize"));
    addGameObject(new Label(getOffset(1345, 20, "Vizualize"), 910, 0.867f, 0.902f, 0.929f, 20, "Visualize"));

    //"Clear" button and its label
    addGameObject(new Label(getOffset(210, 30, "Clear Grid"), 700, 0.616f, 0.698f, 0.749f, 30, "Clear Grid"));
    addGameObject(new Button(200, 750, 100, 50, 0.322f, 0.427f, 0.510f, " ", "Clear"));
    addGameObject(new Label(getOffset(200, 20, "Clear"), 750, 0.867f, 0.902f, 0.929f, 20, "Clear"));

    //GUI "Instructions" label for helping the user Build his Own Binary Tree
    addGameObject(new Label(getOffset(1355,40,"Instructions: "), 150, 0.867f, 0.902f, 0.929f, 40, "Instructions: "));

    //"1. Left-click to add nodes" label 
    addGameObject(new Label(getOffset(1350, 30, "1. Left-click"), 250, 0.616f, 0.698f, 0.749f, 30, "1. Left-click"));
    addGameObject(new Label(getOffset(1350, 30, " to add nodes."), 290, 0.616f, 0.698f, 0.749f, 30, " to add nodes."));

    //"2. Right-click and drag to parent." label 
    addGameObject(new Label(getOffset(1350, 30, "2. Right-click and"), 400, 0.616f, 0.698f, 0.749f, 30, "2. Right-click and"));
    addGameObject(new Label(getOffset(1350, 30, "drag to parent."), 440, 0.616f, 0.698f, 0.749f, 30, "drag to parent."));

    //"3. Drop on Left or Right box (if Available) to assign child." label
    addGameObject(new Label(getOffset(1355, 30, "3. Drop on Left or Right"), 550, 0.616f, 0.698f, 0.749f, 30, "3. Drop on Left or Right"));
    addGameObject(new Label(getOffset(1355, 30, "box (if Available)"), 590, 0.616f, 0.698f, 0.749f, 30, "box (if Available)"));
    addGameObject(new Label(getOffset(1355, 30, "to assign child."), 630, 0.616f, 0.698f, 0.749f, 30, "to assign child."));

	//"4. Press 'visualize' to start Visualization" label
    addGameObject(new Label(getOffset(1355, 30, "4. Press 'visualize' to"), 740, 0.616f, 0.698f, 0.749f, 30, "4. Press 'visualize' to"));
    addGameObject(new Label(getOffset(1355, 30, "start Visualization"), 780, 0.616f, 0.698f, 0.749f, 30, "start Visualization"));

    //create a new Grid using the EditingLevel's Nodes and Edges vectors
    grid = new Grid(nodes, edges, GlobalState::getInstance()->CANVAS_WIDTH / 2, 1000 / 2 - 50, 750, 750);
    addGameObject(grid);

}
void EditingLevel::draw() {
    Levels::draw();//calls base class' draw() method to draw the gameObjects
}
void EditingLevel::update() {
    Levels::update();//calls base class' update() method to update the gameObjects
    const std::string& btn = GlobalState::getInstance()->getButtonID();//get the button_pressed from the GlobalState
    if (btn == "Back") {
        GlobalState::getInstance()->setButtonID("");
        GlobalState::getInstance()->changeLevel(new StartLevel());//go to StartLevel

    }
    if (btn == "Clear") {
        GlobalState::getInstance()->setButtonID("");
        GlobalState::getInstance()->changeLevel(new EditingLevel());//re-initialize the level

    }
    if (btn == "Visualize") {
        GlobalState::getInstance()->setButtonID("");
        VisualizationLevel* newLevel = new VisualizationLevel(grid->getNodes(), grid->getEdges());
        //so when the grid and editingLevel gets deleted they wont delete newLevels' nodes and edges, parsed to the VisualizationLevel
        grid->clearVectors();
        clearVectors();
        GlobalState::getInstance()->changeLevel(newLevel);//go to VisualizationLevel

    }
}