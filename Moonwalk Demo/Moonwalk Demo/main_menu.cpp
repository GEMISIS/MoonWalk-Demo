#include "main_menu.h"
#include "main_game.h"

void main_menu::initializeGraphics()
{
	printf("main menu-initializeGraphics\n"); 
}
void main_menu::initializeLogic()
{
	printf("main menu-initializeLogic\n");
}
void main_menu::initializeSound()
{
	printf("main menu-initializeSound\n");
}

bool main_menu::updateGraphics()
{
	return true;
}
bool main_menu::updateSound()
{
	return true;
}
bool main_menu::updateLogic()
{
	return true;
}

bool main_menu::processWindow(HWND winHandle, UINT message, WPARAM windowParam, LPARAM messageParam)
{
	if(GetKeyState(VK_ESCAPE) & 0x8000)
	{
		current_state->~game_state();
		current_state = new main_game();
		current_state->initialize();
	}
	return true;
}