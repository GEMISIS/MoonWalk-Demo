#ifdef _WIN32
#include <Windows.h>

#define _BITS_PER_PIXEL_ 16

/**
  * An instance of the window.
  */
extern WNDCLASS windowsClass;

/*
The window process method for processing a window's events.
*/
extern LRESULT CALLBACK windowProcess;
WNDCLASS createGLWindow(LPCWSTR title, unsigned int width, unsigned int height, bool fullscreen);
void updateWindow();
void killGLWindow();

#elif __APPLE__
#elif __linux__
#endif
