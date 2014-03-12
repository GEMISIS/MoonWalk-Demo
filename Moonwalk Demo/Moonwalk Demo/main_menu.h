#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "game_state.h"

class main_menu : public game_state
{
public:
	main_menu() : game_state()
	{
	}
	bool processWindow(HWND, UINT, WPARAM, LPARAM);
	bool updateLogic();
	bool updateGraphics();
	bool updateSound();
protected:
	void initializeLogic();
	void initializeGraphics();
	void initializeSound();
};

#endif