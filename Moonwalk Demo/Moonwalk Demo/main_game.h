#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include "main_game_state.h"
#include "camera.h"
#include "wavefrontObject.h"
#include "kinect.h"

struct axis_t
{
	float x, y, z;
};

struct quart_t
{
	axis_t axis;
	float rotationAngle;
};

struct joint_t
{
	vertex_t position;
	quart_t rotation;
};

class main_game : public main_game_state
{
public:
	main_game() : main_game_state()
	{
	}
	bool processWindow(HWND, UINT, WPARAM, LPARAM);
	bool updateLogic();
	bool updateGraphics();
	bool updateSound();
protected:
	bool draw();
	void initializeLogic();
	void initializeGraphics();
	void initializeSound();
private:
	float mroRotation;
	wavefrontObject* mroModel;
	wavefrontObject* MKIIIModel;
	wavefrontObject* tardisModel;

	unsigned int creditsTextureHandle;
	unsigned char* creditsTextureData;

	unsigned int moonTextureHandle;
	unsigned char* moonTextureData;

	unsigned int starsTextureHandle;
	unsigned char* starsTextureData;

	float earthRotation;
	unsigned int earthTextureHandle;
	unsigned char* earthTextureData;

	unsigned int sunTextureHandle;
	unsigned char* sunTextureData;

	unsigned int feedbackDisplayHandle;
	unsigned char feedbackDisplayData[640 * 480 * 4];

	vertex_t playerWorldRotation;

	joint_t leftHand;
	vertex_t rightHand, leftFoot, rightFoot;

	Kinect* kinect;
};

#endif