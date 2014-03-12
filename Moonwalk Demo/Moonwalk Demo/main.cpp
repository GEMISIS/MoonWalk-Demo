// Include the header for windows functions.
#include <Windows.h>
// Include the header for standard I/O functions.
#include <stdio.h>

// Include the functions for SFML's graphics and audio.
#include <GL/GL.h>
#include <GL/GLU.h>

// Include the header for the game states.
#include "game_state.h"
#include "windowSystem.h"
#include "extendedGL.h"

#include "main_menu.h"
#include "main_game.h"

// Actually declare the current state.
game_state* current_state = NULL;

#ifndef _DEBUG
int main();
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return main();
}
#endif

void onResize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, float(width) / height, 0.1f, 100);
  glMatrixMode(GL_MODELVIEW);
}

LRESULT CALLBACK windowProcessN(HWND winHandle, UINT message, WPARAM windowParam, LPARAM messageParam)
{
	switch(message)
	{
	case WM_SIZE:
		onResize(LOWORD(messageParam),HIWORD(messageParam));
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	if(current_state != NULL)
	{
		current_state->processWindow(winHandle, message, windowParam, messageParam);
	}
	//Sleep(50);
	return DefWindowProc(winHandle, message, windowParam, messageParam);
}

int main()
{
	windowProcess = (LRESULT CALLBACK)windowProcessN;
	WNDCLASS window = createGLWindow((LPCWSTR)L"Moon Walk Demo", 1280, 800, false);
	onResize(1280, 800);
	glEnable(GL_DEPTH_TEST);

	MSG msg;
	bool done = false;

	initExtendedGL();

	current_state = new main_game();
	current_state->initialize();

	int version = 0;
	printf("%s\n", glGetString(GL_VERSION));
	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		current_state->updateLogic();
	
		// Draw graphics here.
		{
			// Set color and depth clear value
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.f, 0.f, 0.f, 0.f);

			current_state->updateGraphics();
		}

		current_state->updateSound();

		updateWindow();
	}
	killGLWindow();

	return 0;
}