#include <4dm.h>
#include "4Dconsole.h"
#include "4DKeyBinds.h"
using namespace fdm;


bool glasses = true;
bool compass = true;

$hook(bool, Player, isHoldingGlasses ) {
	return glasses;
}

$hook(void, Player, renderHud, GLFWwindow* window ) {
	original(self,window);
	
	// render rotated to be behind players back, if it isn't already rendered
	if (compass && !self->isHoldingCompass())
		CompassRenderer::renderHand(glm::mat4x4{{0,0,0,1},{0,0,0,0},{0,0,1,0},{1,0,0,0}});
}


// keyBinds mod
void toggleGlasses(GLFWwindow* _window, int action, int _mods){
	if ( action == GLFW_PRESS )
		glasses = !glasses;
}
void toggleCompass(GLFWwindow* _window, int action, int _mods){
	if ( action == GLFW_PRESS )
		compass = !compass;
}

$exec {
	KeyBinds::addBind( "Toggle 4D Glasses", glfw::Keys::F3, KeyBindsScope::PLAYER, toggleGlasses );
	KeyBinds::addBind( "Toggle Compass",    glfw::Keys::F3, KeyBindsScope::PLAYER, toggleCompass );
}
