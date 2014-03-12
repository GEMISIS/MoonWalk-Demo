#ifndef _MAIN_GAME_STATE_H_
#define _MAIN_GAME_STATE_H_

#include "game_state.h"
#include "camera.h"

class main_game_state : public game_state
{
public:
	main_game_state() : game_state()
	{
	}
	bool updateLogic();
	bool updateGraphics();
protected:
	void initializeGraphics();
	void updateFrameBuffer();
	void updateCamera();
	virtual bool draw()
	{
		return false;
	};
	unsigned int renderBufferDepthStencil;
	unsigned int frameBuffer;
	unsigned int frameBufferTexture;

	unsigned int width;
	unsigned int height;

	camera_t camera;
private:
	unsigned int quadVertexHandle;
	unsigned int quadColorHandle;
	unsigned int quadTextureHandle;

	unsigned int programObject;

	unsigned int vertexShader;
	unsigned int fragmentShader;

	unsigned char* vertexShaderProgramData;
	unsigned int vertexShaderProgramLength;
	unsigned char* fragmentShaderProgramData;
	unsigned int fragmentShaderProgramLength;

	void updateUniforms(RiftEye eye);
};

#endif