
#define MOD_NAME "4D Contacts"
#define MOD_VER "1.0"

#include <4dm.h>
#include "4Dconsole.h"
#include "4DKeyBinds.h"
using namespace fdm;


bool glasses = true;
bool compass = true;

bool Player_isHoldingGlasses_H(Player* self) {
	return glasses;
}

void(__thiscall* player_renderHUD)(Player* self, GLFWwindow* window);
void player_renderHUD_H(Player* self, GLFWwindow* window) {
	player_renderHUD(self,window);
	
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


// fallback to regular keyInput handling
bool(__thiscall* Player_keyInput)(Player* self, GLFWwindow* window, World* world, int key, int scancode, int action, int mods);
bool Player_keyInput_H(Player* self, GLFWwindow* window, World* world, int key, int scancode, int action, int mods) {
	
	if ( action == GLFW_PRESS && key == glfw::Keys::F3 ) {
		toggleGlasses(window, action, mods);
		toggleCompass(window, action, mods);
	}
	
	return Player_keyInput(self, window, world, key, scancode, action, mods);
}


DWORD WINAPI Main_Thread(void* hModule) {
	
	// why do I have to do this Tr1Ngle?? Why?????
	for (int i = 0; i < 500; i++) {
		if (KeyBinds::IsLoaded())
			break;
		Sleep(10);
	}
	
	if (KeyBinds::IsLoaded()) {
		KeyBinds::addBind( "Toggle 4D Glasses", glfw::Keys::F3, KeyBindsScope::PLAYER, toggleGlasses );
		KeyBinds::addBind( "Toggle Compass",    glfw::Keys::F3, KeyBindsScope::PLAYER, toggleCompass );
	} else {
		registerConsoleKeyinfo({{"F3","Toggle Glasses & Compass"}});
		Hook( FUNC_PLAYER_KEYINPUT, Player_keyInput_H, &Player_keyInput );
	}
	
	Hook( FUNC_PLAYER_ISHOLDINGGLASSES, Player_isHoldingGlasses_H );
	Hook( FUNC_PLAYER_RENDERHUD, player_renderHUD_H, &player_renderHUD );
	
	EnableHook();
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD _reason, LPVOID lpReserved) {
	if (_reason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main_Thread, hModule, 0, NULL);
	return true;
}
