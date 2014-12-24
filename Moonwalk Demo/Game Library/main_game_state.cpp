#include "main_game_state.h"
#include <GL\GLU.h>
#include "extendedGL.h"
#include "fileIO.h"

#define quadVertices 2

#define quadVetex_size 4
#define quadColor_size 4
#define quadTex_size 4

float quadVerts[quadVetex_size][quadVertices] = {
	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f}
};
float quadColor[quadColor_size][3] = {
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f}
};
float quadTexture[quadTex_size][2] = {
	{0.0, 0.0},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f}
};

void main_game_state::initializeGraphics()
{
	if(this->camera.hasOculusRift)
	{
		this->width = 640;
		this->height = 800;
	}
	else
	{
		this->width = 1280;
		this->height = 800;

		this->camera.FieldOfView = 60.0f;
		this->camera.AspectRatio = 1280.0f / 800.0f;
		this->camera.CloseDepth = 0.01f;
		this->camera.FarDepth = 10000.0f;
	}

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_MULTISAMPLE);

	glGenRenderbuffers(1, &renderBufferDepthStencil);
	glGenFramebuffers(1, &frameBuffer);
	glGenTextures(1, &frameBufferTexture);

	glGenBuffers(1, &quadVertexHandle);
	glBindBuffer(GL_ARRAY_BUFFER, quadVertexHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadVetex_size * quadVertices, quadVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &quadColorHandle);
	glBindBuffer(GL_ARRAY_BUFFER, quadColorHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadColor_size * 3, quadColor, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &quadTextureHandle);
	glBindBuffer(GL_ARRAY_BUFFER, quadTextureHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadTex_size * 2, quadTexture, 0x88E0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindTexture(GL_TEXTURE_2D, frameBufferTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, this->width, this->height, false);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferDepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferDepthStencil);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(this->camera.hasOculusRift)
	{
		this->vertexShaderProgramLength = loadFile("vertexProgram.glsl", &this->vertexShaderProgramData);
		this->fragmentShaderProgramLength = loadFile("fragmentProgram.glsl", &this->fragmentShaderProgramData);

		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->vertexShader, 1, (const unsigned char**)&this->vertexShaderProgramData, &this->vertexShaderProgramLength);
		glCompileShader(this->vertexShader);
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->fragmentShader, 1, (const unsigned char**)&this->fragmentShaderProgramData, &this->fragmentShaderProgramLength);
		glCompileShader(this->fragmentShader);

		this->programObject = glCreateProgram();

		glAttachShader(this->programObject, this->vertexShader);
		glAttachShader(this->programObject, this->fragmentShader);
		glLinkProgram(this->programObject);
	}
	else
	{
		this->programObject = 0;
	}
	// Initialize camera positions to 0.0f
	this->camera.Rotation.x = 0.0f;
	this->camera.Rotation.y = 0.0f;
	this->camera.Rotation.z = 0.0f;

	this->camera.Position.x = 0.0f;
	this->camera.Position.y = 0.0f;
	this->camera.Position.z = 0.0f;
}

void main_game_state::updateUniforms(RiftEye eye)
{
	if(this->camera.hasOculusRift)
	{
		int u_texRange = glGetUniformLocation(this->programObject, "u_texRange");
		int u_lensCenterOffset = glGetUniformLocation(this->programObject, "u_lensCenterOffset");
		int u_distortion = glGetUniformLocation(this->programObject, "u_distortion");
		int u_aspect = glGetUniformLocation(this->programObject, "u_aspect");
		int u_fillScale = glGetUniformLocation(this->programObject, "u_fillScale");

		glUniform2f(u_texRange, 1.0f, 1.0f);
		if(eye == Left)
		{
			glUniform2f(u_lensCenterOffset, this->camera.LeftEye.pDistortion->XCenterOffset, this->camera.LeftEye.pDistortion->YCenterOffset);
		}
		else
		{
			glUniform2f(u_lensCenterOffset, this->camera.RightEye.pDistortion->XCenterOffset, this->camera.RightEye.pDistortion->YCenterOffset);
		}
		glUniform4f(u_distortion, this->camera.riftHMD.DistortionK[0], this->camera.riftHMD.DistortionK[1], this->camera.riftHMD.DistortionK[2], this->camera.riftHMD.DistortionK[3]);
		glUniform1f(u_aspect, this->camera.AspectRatio);
		glUniform1f(u_fillScale, this->camera.StereoConfiguration.GetDistortionScale());
	}
}

bool main_game_state::updateGraphics()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glViewport(0, 0, this->width, this->height);

	this->updateCamera();

	this->draw();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture, 0);
	this->postProcessGraphics();

	glUseProgram(this->programObject);
	this->updateFrameBuffer();
	glUseProgram(0);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return true;
}

void main_game_state::updateFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glPushMatrix();
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.f, 0.f, 0.f, 0.f);

			if(this->camera.hasOculusRift)
			{
				this->updateUniforms(Left);
				this->camera.UpdateRiftView(Left);
				glTranslatef(0.0f, 0.0f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, frameBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, quadVertexHandle);
				glVertexPointer(quadVertices, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadColorHandle);
				glColorPointer(3, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadTextureHandle);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVetex_size);

				this->updateUniforms(Right);
				this->camera.UpdateRiftView(Right);
				glTranslatef(0.0f, 0.0f, 0.0f);
				glBindBuffer(GL_ARRAY_BUFFER, quadVertexHandle);
				glVertexPointer(quadVertices, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadColorHandle);
				glColorPointer(3, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadTextureHandle);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVetex_size);
			}
			else
			{
				glTranslatef(0.0f, 0.0f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, frameBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, quadVertexHandle);
				glVertexPointer(quadVertices, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadColorHandle);
				glColorPointer(3, GL_FLOAT, 0, 0);
				glBindBuffer(GL_ARRAY_BUFFER, quadTextureHandle);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVetex_size);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
	//glEnable(GL_DEPTH_TEST);
}

void main_game_state::updateCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->camera.FieldOfView, this->camera.AspectRatio, this->camera.CloseDepth, this->camera.FarDepth);
	if(this->camera.useingQuarts)
	{
		glRotatef(this->camera.RotationQuart.angle, this->camera.RotationQuart.axis.x,
			this->camera.RotationQuart.axis.y, this->camera.RotationQuart.axis.z);
	}
	else
	{
		glRotatef(this->camera.Rotation.z, 0, 0, 1);
		glRotatef(this->camera.Rotation.x, 1, 0, 0);
		glRotatef(this->camera.Rotation.y + 180.0f, 0, 1, 0);
	}
	glTranslatef(this->camera.Position.x, this->camera.Position.y, this->camera.Position.z);
}

bool main_game_state::updateLogic()
{
	if(this->camera.hasOculusRift)
	{
		this->camera.UpdateOculusRiftData();
	}
	return true;
}
