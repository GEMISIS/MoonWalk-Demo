#include "windowSystem.h"

#ifdef _WIN32
LRESULT CALLBACK windowProcess;
/**
 * Set up a rendering context for where to draw the openGL
 * stuff to.
 */
HGLRC renderingContext = NULL;

/**
 * Set up a device context for connecting the window to the graphics
 * interface device.
 */
HDC deviceContext = NULL;

/**
 * Set up a window handle for managing the actual window.
 */
HWND windowHandle = NULL;

/**
 * Set up a variable for an instance of our application.
 */
HINSTANCE appInstance;

/**
 * A boolean variable indicating whether the window is active.
 */
bool windowActive = true;

/**
 * A boolean variable indicating whether the window is fullscreen or not.
 */
bool isFullscreen = false;

/**
  * An instance of the window.
  */
WNDCLASS windowsClass;

WNDCLASS createGLWindow(LPCWSTR title, unsigned int width, unsigned int height, bool fullscreen)
{
	int pixelFormat;
	unsigned long windowExtendedStyle;
	unsigned long windowStyle;
	
	RECT windowRectangle;
	windowRectangle.left = 0;
	windowRectangle.right = width;
	windowRectangle.top = 0;
	windowRectangle.bottom = height;

	isFullscreen = fullscreen;

	appInstance = GetModuleHandle(NULL);
	windowsClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowsClass.lpfnWndProc = (WNDPROC)windowProcess;
	windowsClass.cbClsExtra = 0;
	windowsClass.cbWndExtra = 0;
	windowsClass.hInstance = appInstance;
	windowsClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowsClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowsClass.hbrBackground = NULL;
	windowsClass.lpszMenuName = NULL;
	windowsClass.lpszClassName = (LPCWSTR)L"OpenGL";

	if(!RegisterClass(&windowsClass))
	{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Error register class!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
				return windowsClass;
	}

	if(isFullscreen)
	{
		DEVMODE deviceModeScreenSettings;
		memset(&deviceModeScreenSettings, 0, sizeof(deviceModeScreenSettings));
		deviceModeScreenSettings.dmSize = sizeof(deviceModeScreenSettings);
		if(!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &deviceModeScreenSettings))
		{
			deviceModeScreenSettings.dmBitsPerPel = _BITS_PER_PIXEL_;
			deviceModeScreenSettings.dmPelsWidth = width;
			deviceModeScreenSettings.dmPelsHeight = height;
			deviceModeScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		}
		if(ChangeDisplaySettings(&deviceModeScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if(ChangeDisplaySettings(NULL, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				if(MessageBox(NULL, (LPCWSTR)L"The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?", (LPCWSTR)L"Warning", MB_YESNO | MB_ICONWARNING) == IDYES)
				{
					fullscreen = false;
				}
				else
				{
#ifdef _DEBUG
					MessageBox(NULL, (LPCWSTR)L"Error going fullscreen!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
					MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
					return windowsClass;
				}
			}
		}
	}
	if(isFullscreen)
	{
		windowExtendedStyle = WS_EX_APPWINDOW;
		windowStyle = WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		windowStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRectangle, windowStyle, false, windowExtendedStyle);

	if(!(windowHandle = CreateWindowEx(windowExtendedStyle, (LPCWSTR)L"OpenGL", title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle, 0, 0, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, NULL, NULL, appInstance, NULL)))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error creating window!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}

	if(isFullscreen)
	{
		SetWindowLong(windowHandle, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
	}

	static PIXELFORMATDESCRIPTOR pixelFormatDesc = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		_BITS_PER_PIXEL_,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		16,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if(!(deviceContext = GetDC(windowHandle)))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error creating device context!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}
	if(!(pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc)))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error finding a usable pixel format!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}
	if(!SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error setting pixel format!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}
	if(!(renderingContext = wglCreateContext(deviceContext)))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error creating rendering context!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}
	if(!wglMakeCurrent(deviceContext, renderingContext))
	{
		killGLWindow();
#ifdef _DEBUG
		MessageBox(NULL, (LPCWSTR)L"Error making rendering context the current one!", (LPCWSTR)L"CREATEWINDOW ERROR", MB_OK | MB_ICONERROR);
#else
		MessageBox(NULL, (LPCWSTR)L"Error starting application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		return windowsClass;
	}

	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);

	return windowsClass;
}

void updateWindow()
{
	SwapBuffers(deviceContext);
}

void killGLWindow()
{
	if(isFullscreen)
	{
		if(ChangeDisplaySettings(NULL, 0) != DISP_CHANGE_SUCCESSFUL)
		{
#ifdef _DEBUG
			MessageBox(NULL, (LPCWSTR)L"Changing display from fullscreen failed!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
			MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
			ShowCursor(true);
		}
		if(renderingContext)
		{

			if(!wglMakeCurrent(NULL, NULL))
			{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Release Of DC And RC Failed!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
			}
		}
		if(!wglDeleteContext(renderingContext))
		{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Error releasing rendering context!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
		}
		renderingContext = NULL;
		if(deviceContext && !ReleaseDC(windowHandle, deviceContext))
		{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Error releasing device context!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
				deviceContext = NULL;
		}
		if(windowHandle && !DestroyWindow(windowHandle))
		{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Error destroying window handle!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
				windowHandle = NULL;
		}
		if(!UnregisterClass((LPCWSTR)L"OpenGL", appInstance))
		{
#ifdef _DEBUG
				MessageBox(NULL, (LPCWSTR)L"Error unregistering class!", (LPCWSTR)L"killGLWindow ERROR", MB_OK | MB_ICONERROR);
#else
				MessageBox(NULL, (LPCWSTR)L"Error closing application!\nError code: needs insert", (LPCWSTR)L"Error", MB_OK | MB_ICONERROR);
#endif
				appInstance = NULL;
		}
	}
}
#elif __APPLE__
#elif __linux__
#endif
