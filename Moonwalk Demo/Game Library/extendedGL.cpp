#include <Windows.h>
#include <stdio.h>
#include "extendedGL.h"
#include "fileIO.h"

wglSwapIntervalEXTType wglSwapIntervalEXT = NULL;
glBindFramebufferType glBindFramebuffer = NULL;
glGenFramebuffersType glGenFramebuffers = NULL;
glFramebufferTexture2DType glFramebufferTexture2D = NULL;
glGenRenderbuffersType glGenRenderbuffers = NULL;
glBindRenderbufferType glBindRenderbuffer = NULL;
glRenderbufferStorageType glRenderbufferStorage = NULL;
glFramebufferRenderbufferType glFramebufferRenderbuffer = NULL;
glGenBuffersType glGenBuffers = NULL;
glBindBufferType glBindBuffer = NULL;
glBufferDataType glBufferData = NULL;
glDeleteBuffersType glDeleteBuffers = NULL;
glCreateShaderType glCreateShader = NULL;
glDeleteShaderType glDeleteShader = NULL;
glShaderSourceARBType glShaderSourceARB = NULL;
glShaderSourceType glShaderSource = NULL;
glCreateProgramType glCreateProgram = NULL;
glDeleteProgramType glDeleteProgram = NULL;
glCompileShaderType glCompileShader = NULL;
glAttachShaderType glAttachShader = NULL;
glLinkProgramType glLinkProgram = NULL;
glUseProgramType glUseProgram = NULL;
glTexImage2DMultisampleType glTexImage2DMultisample = NULL;

glGetUniformLocationType glGetUniformLocation = NULL;

glUniform1fType glUniform1f = NULL;
glUniform2fType glUniform2f = NULL;
glUniform3fType glUniform3f = NULL;
glUniform4fType glUniform4f = NULL;
glUniform1iType glUniform1i = NULL;
glUniform2iType glUniform2i = NULL;
glUniform3iType glUniform3i = NULL;
glUniform4iType glUniform4i = NULL;
glUniform1uiType glUniform1ui = NULL;
glUniform2uiType glUniform2ui = NULL;
glUniform3uiType glUniform3ui = NULL;
glUniform4uiType glUniform4ui = NULL;
glUniform1fvType glUniform1fv = NULL;
glUniform2fvType glUniform2fv = NULL;
glUniform3fvType glUniform3fv = NULL;
glUniform4fvType glUniform4fv = NULL;
glUniform1ivType glUniform1iv = NULL;
glUniform2ivType glUniform2iv = NULL;
glUniform3ivType glUniform3iv = NULL;
glUniform4ivType glUniform4iv = NULL;
glUniform1uivType glUniform1uiv = NULL;
glUniform2uivType glUniform2uiv = NULL;
glUniform3uivType glUniform3uiv = NULL;
glUniform4uivType glUniform4uiv = NULL;
glUniformMatrix2fvType glUniformMatrix2fv = NULL;
glUniformMatrix3fvType glUniformMatrix3fv = NULL;
glUniformMatrix4fvType glUniformMatrix4fv = NULL;
glUniformMatrix2x3fvType glUniformMatrix2x3fv = NULL;
glUniformMatrix3x2fvType glUniformMatrix3x2fv = NULL;
glUniformMatrix2x4fvType glUniformMatrix2x4fv = NULL;
glUniformMatrix4x2fvType glUniformMatrix4x2fv = NULL;
glUniformMatrix3x4fvType glUniformMatrix3x4fv = NULL;
glUniformMatrix4x3fvType glUniformMatrix4x3fv = NULL;

void initExtendedGL()
{
	wglSwapIntervalEXT = (wglSwapIntervalEXTType)wglGetProcAddress("wglSwapIntervalEXT");
	glBindFramebuffer = (glBindFramebufferType)wglGetProcAddress("glBindFramebuffer");
	glGenFramebuffers = (glGenFramebuffersType)wglGetProcAddress("glGenFramebuffers");
	glFramebufferTexture2D = (glFramebufferTexture2DType)wglGetProcAddress("glFramebufferTexture2D");
	glGenRenderbuffers = (glGenRenderbuffersType)wglGetProcAddress("glGenRenderbuffers");
	glBindRenderbuffer = (glBindRenderbufferType)wglGetProcAddress("glBindRenderbuffer");
	glRenderbufferStorage = (glRenderbufferStorageType)wglGetProcAddress("glRenderbufferStorage");
	glFramebufferRenderbuffer = (glFramebufferRenderbufferType)wglGetProcAddress("glFramebufferRenderbuffer");
	glGenBuffers = (glGenBuffersType)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (glBindBufferType)wglGetProcAddress("glBindBuffer");
	glBufferData = (glBufferDataType)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (glDeleteBuffersType)wglGetProcAddress("glDeleteBuffers");
	glCreateShader = (glCreateShaderType)wglGetProcAddress("glCreateShader");
	glDeleteShader = (glDeleteShaderType)wglGetProcAddress("glDeleteShader");
	glShaderSourceARB = (glShaderSourceARBType)wglGetProcAddress("glShaderSourceARB");
	glShaderSource = (glShaderSourceType)wglGetProcAddress("glShaderSource");
	glCreateProgram = (glCreateProgramType)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (glDeleteProgramType)wglGetProcAddress("glDeleteProgram");
	glCompileShader = (glCompileShaderType)wglGetProcAddress("glCompileShader");
	glAttachShader = (glAttachShaderType)wglGetProcAddress("glAttachShader");
	glLinkProgram = (glLinkProgramType)wglGetProcAddress("glLinkProgram");
	glUseProgram = (glUseProgramType)wglGetProcAddress("glUseProgram");
	glTexImage2DMultisample = (glTexImage2DMultisampleType)wglGetProcAddress("glTexImage2DMultisample");

	glGetUniformLocation = (glGetUniformLocationType)wglGetProcAddress("glGetUniformLocation");

	glUniform1f = (glUniform1fType)wglGetProcAddress("glUniform1f");
	glUniform2f = (glUniform2fType)wglGetProcAddress("glUniform2f");
	glUniform3f = (glUniform3fType)wglGetProcAddress("glUniform3f");
	glUniform4f = (glUniform4fType)wglGetProcAddress("glUniform4f");
	
	glUniform1i = (glUniform1iType)wglGetProcAddress("glUniform1i");
	glUniform2i = (glUniform2iType)wglGetProcAddress("glUniform2i");
	glUniform3i = (glUniform3iType)wglGetProcAddress("glUniform3i");
	glUniform4i = (glUniform4iType)wglGetProcAddress("glUniform4i");

	glUniform1ui = (glUniform1uiType)wglGetProcAddress("glUniform1ui");
	glUniform2ui = (glUniform2uiType)wglGetProcAddress("glUniform2ui");
	glUniform3ui = (glUniform3uiType)wglGetProcAddress("glUniform3ui");
	glUniform4ui = (glUniform4uiType)wglGetProcAddress("glUniform4ui");

	glUniform1fv = (glUniform1fvType)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (glUniform2fvType)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (glUniform3fvType)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (glUniform4fvType)wglGetProcAddress("glUniform4fv");

	glUniform1iv = (glUniform1ivType)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (glUniform2ivType)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (glUniform3ivType)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (glUniform4ivType)wglGetProcAddress("glUniform4iv");

	glUniform1uiv = (glUniform1uivType)wglGetProcAddress("glUniform1uiv");
	glUniform2uiv = (glUniform2uivType)wglGetProcAddress("glUniform2uiv");
	glUniform3uiv = (glUniform3uivType)wglGetProcAddress("glUniform3uiv");
	glUniform4uiv = (glUniform4uivType)wglGetProcAddress("glUniform4uiv");

	glUniformMatrix2fv = (glUniformMatrix2fvType)wglGetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (glUniformMatrix3fvType)wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (glUniformMatrix4fvType)wglGetProcAddress("glUniformMatrix4fv");

	glUniformMatrix2x3fv = (glUniformMatrix2x3fvType)wglGetProcAddress("glUniformMatrix2x3fv");
	glUniformMatrix3x2fv = (glUniformMatrix3x2fvType)wglGetProcAddress("glUniformMatrix3x2fv");
	glUniformMatrix2x4fv = (glUniformMatrix2x4fvType)wglGetProcAddress("glUniformMatrix2x4fv");
	glUniformMatrix4x2fv = (glUniformMatrix4x2fvType)wglGetProcAddress("glUniformMatrix4x2fv");
	glUniformMatrix3x4fv = (glUniformMatrix3x4fvType)wglGetProcAddress("glUniformMatrix3x4fv");
	glUniformMatrix4x3fv = (glUniformMatrix4x3fvType)wglGetProcAddress("glUniformMatrix4x3fv");
}
