#ifndef _EXTENDED_GL_
#define _EXTENDED_GL_

typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

typedef bool (APIENTRY* wglSwapIntervalEXTType) (int interval);
typedef void (APIENTRY* glBindFramebufferType) (unsigned int target, unsigned int frameBuffer);
typedef void (APIENTRY* glGenFramebuffersType) (unsigned int n, unsigned int* ids);
typedef void (APIENTRY* glFramebufferTexture2DType) (unsigned int target, unsigned int attachment,
	unsigned int textarget, unsigned int texture, int level);
typedef void (APIENTRY* glGenRenderbuffersType) (unsigned int n, unsigned int* renderbuffers);
typedef void (APIENTRY* glBindRenderbufferType) (unsigned int n, unsigned int renderbuffer);
typedef void (APIENTRY* glRenderbufferStorageType) (unsigned int target, unsigned int internalformat,
	unsigned int width, unsigned int height);
typedef void (APIENTRY* glFramebufferRenderbufferType) (unsigned int target, unsigned int attachment,
	unsigned int renderbuffertarget, unsigned int renderbuffer);
typedef void (APIENTRY* glGenBuffersType) (unsigned int n, unsigned int* buffers);
typedef void (APIENTRY* glBindBufferType) (unsigned int target, unsigned int buffer);//
typedef void (APIENTRY* glBufferDataType) (unsigned int target, unsigned int size, const void* data,
	unsigned int usage);
typedef void (APIENTRY* glDeleteBuffersType) (unsigned int n, const unsigned int* buffers);
typedef unsigned int (APIENTRY* glCreateShaderType) (unsigned int shaderType);
typedef void (APIENTRY* glDeleteShaderType) (unsigned int shader);
typedef void (APIENTRY* glShaderSourceARBType) (unsigned int shaderObject);
typedef void (APIENTRY* glShaderSourceType) (unsigned int shader, unsigned int count,
	const unsigned char** string, const unsigned int* length);
typedef void (APIENTRY* glCompileShaderType) (unsigned int shader);
typedef unsigned int (APIENTRY* glCreateProgramType) (void);
typedef void (APIENTRY* glDeleteProgramType) (unsigned int program);
typedef void (APIENTRY* glAttachShaderType) (unsigned int program, unsigned int shader);
typedef void (APIENTRY* glLinkProgramType) (unsigned int program);
typedef void (APIENTRY* glUseProgramType) (unsigned int program);
typedef void (APIENTRY* glTexImage2DMultisampleType) (unsigned int target, unsigned int samples,
	int internalformat, unsigned int width, unsigned int height, bool fixedsamplelocations);

typedef int (APIENTRY* glGetUniformLocationType) (unsigned int program, const char* name);

typedef void (APIENTRY* glUniform1fType) (unsigned int location, float v0);
typedef void (APIENTRY* glUniform2fType) (unsigned int location, float v0, float v1);
typedef void (APIENTRY* glUniform3fType) (unsigned int location, float v0, float v1, float v2);
typedef void (APIENTRY* glUniform4fType) (unsigned int location, float v0, float v1, float v2, float v3);

typedef void (APIENTRY* glUniform1iType) (unsigned int location, int v0);
typedef void (APIENTRY* glUniform2iType) (unsigned int location, int v0, int v1);
typedef void (APIENTRY* glUniform3iType) (unsigned int location, int v0, int v1, int v2);
typedef void (APIENTRY* glUniform4iType) (unsigned int location, int v0, int v1, int v2, int v3);

typedef void (APIENTRY* glUniform1uiType) (unsigned int location, unsigned int v0);
typedef void (APIENTRY* glUniform2uiType) (unsigned int location, unsigned int v0, unsigned int v1);
typedef void (APIENTRY* glUniform3uiType) (unsigned int location, unsigned int v0, unsigned int v1, unsigned int v2);
typedef void (APIENTRY* glUniform4uiType) (unsigned int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

typedef void (APIENTRY* glUniform1fvType) (unsigned int location, unsigned int count, const float* value);
typedef void (APIENTRY* glUniform2fvType) (unsigned int location, unsigned int count, const float* value);
typedef void (APIENTRY* glUniform3fvType) (unsigned int location, unsigned int count, const float* value);
typedef void (APIENTRY* glUniform4fvType) (unsigned int location, unsigned int count, const float* value);

typedef void (APIENTRY* glUniform1ivType) (unsigned int location, unsigned int count, const int* value);
typedef void (APIENTRY* glUniform2ivType) (unsigned int location, unsigned int count, const int* value);
typedef void (APIENTRY* glUniform3ivType) (unsigned int location, unsigned int count, const int* value);
typedef void (APIENTRY* glUniform4ivType) (unsigned int location, unsigned int count, const int* value);

typedef void (APIENTRY* glUniform1uivType) (unsigned int location, unsigned int count, const unsigned int* value);
typedef void (APIENTRY* glUniform2uivType) (unsigned int location, unsigned int count, const unsigned int* value);
typedef void (APIENTRY* glUniform3uivType) (unsigned int location, unsigned int count, const unsigned int* value);
typedef void (APIENTRY* glUniform4uivType) (unsigned int location, unsigned int count, const unsigned int* value);

typedef void (APIENTRY* glUniformMatrix2fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix3fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix4fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);

typedef void (APIENTRY* glUniformMatrix2x3fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix3x2fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix2x4fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix4x2fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix3x4fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);
typedef void (APIENTRY* glUniformMatrix4x3fvType) (unsigned int location, unsigned int count, bool transpose, const float* value);

extern wglSwapIntervalEXTType wglSwapIntervalEXT;
extern glBindFramebufferType glBindFramebuffer;
extern glGenFramebuffersType glGenFramebuffers;
extern glFramebufferTexture2DType glFramebufferTexture2D;
extern glGenRenderbuffersType glGenRenderbuffers;
extern glBindRenderbufferType glBindRenderbuffer;
extern glRenderbufferStorageType glRenderbufferStorage;
extern glFramebufferRenderbufferType glFramebufferRenderbuffer;
extern glGenBuffersType glGenBuffers;
extern glBindBufferType glBindBuffer;
extern glBufferDataType glBufferData;
extern glDeleteBuffersType glDeleteBuffers;
extern glCreateShaderType glCreateShader;
extern glDeleteShaderType glDeleteShader;
extern glShaderSourceARBType glShaderSourceARB;
extern glShaderSourceType glShaderSource;
extern glCreateProgramType glCreateProgram;
extern glDeleteProgramType glDeleteProgram;
extern glCompileShaderType glCompileShader;
extern glAttachShaderType glAttachShader;
extern glLinkProgramType glLinkProgram;
extern glUseProgramType glUseProgram;
extern glTexImage2DMultisampleType glTexImage2DMultisample;

extern glGetUniformLocationType glGetUniformLocation;

extern glUniform1fType glUniform1f;
extern glUniform2fType glUniform2f;
extern glUniform3fType glUniform3f;
extern glUniform4fType glUniform4f;
extern glUniform1iType glUniform1i;
extern glUniform2iType glUniform2i;
extern glUniform3iType glUniform3i;
extern glUniform4iType glUniform4i;
extern glUniform1uiType glUniform1ui;
extern glUniform2uiType glUniform2ui;
extern glUniform3uiType glUniform3ui;
extern glUniform4uiType glUniform4ui;
extern glUniform1fvType glUniform1fv;
extern glUniform2fvType glUniform2fv;
extern glUniform3fvType glUniform3fv;
extern glUniform4fvType glUniform4fv;
extern glUniform1ivType glUniform1iv;
extern glUniform2ivType glUniform2iv;
extern glUniform3ivType glUniform3iv;
extern glUniform4ivType glUniform4iv;
extern glUniform1uivType glUniform1uiv;
extern glUniform2uivType glUniform2uiv;
extern glUniform3uivType glUniform3uiv;
extern glUniform4uivType glUniform4uiv;
extern glUniformMatrix2fvType glUniformMatrix2fv;
extern glUniformMatrix3fvType glUniformMatrix3fv;
extern glUniformMatrix4fvType glUniformMatrix4fv;
extern glUniformMatrix2x3fvType glUniformMatrix2x3fv;
extern glUniformMatrix3x2fvType glUniformMatrix3x2fv;
extern glUniformMatrix2x4fvType glUniformMatrix2x4fv;
extern glUniformMatrix4x2fvType glUniformMatrix4x2fv;
extern glUniformMatrix3x4fvType glUniformMatrix3x4fv;
extern glUniformMatrix4x3fvType glUniformMatrix4x3fv;

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1
#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW 0x88E0
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_MULTISAMPLE 0x809D
#define WGL_NUMBER_PIXEL_FORMATS_ARB            0x2000
#define WGL_DRAW_TO_WINDOW_ARB                  0x2001
#define WGL_DRAW_TO_BITMAP_ARB                  0x2002
#define WGL_ACCELERATION_ARB                    0x2003
#define WGL_NEED_PALETTE_ARB                    0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB             0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB              0x2006
#define WGL_SWAP_METHOD_ARB                     0x2007
#define WGL_NUMBER_OVERLAYS_ARB                 0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                0x2009
#define WGL_TRANSPARENT_ARB                     0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB           0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB         0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB          0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB         0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB         0x203B
#define WGL_SHARE_DEPTH_ARB                     0x200C
#define WGL_SHARE_STENCIL_ARB                   0x200D
#define WGL_SHARE_ACCUM_ARB                     0x200E
#define WGL_SUPPORT_GDI_ARB                     0x200F
#define WGL_SUPPORT_OPENGL_ARB                  0x2010
#define WGL_DOUBLE_BUFFER_ARB                   0x2011
#define WGL_STEREO_ARB                          0x2012
#define WGL_PIXEL_TYPE_ARB                      0x2013
#define WGL_COLOR_BITS_ARB                      0x2014
#define WGL_RED_BITS_ARB                        0x2015
#define WGL_RED_SHIFT_ARB                       0x2016
#define WGL_GREEN_BITS_ARB                      0x2017
#define WGL_GREEN_SHIFT_ARB                     0x2018
#define WGL_BLUE_BITS_ARB                       0x2019
#define WGL_BLUE_SHIFT_ARB                      0x201A
#define WGL_ALPHA_BITS_ARB                      0x201B
#define WGL_ALPHA_SHIFT_ARB                     0x201C
#define WGL_ACCUM_BITS_ARB                      0x201D
#define WGL_ACCUM_RED_BITS_ARB                  0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                 0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                0x2021
#define WGL_DEPTH_BITS_ARB                      0x2022
#define WGL_STENCIL_BITS_ARB                    0x2023
#define WGL_AUX_BUFFERS_ARB                     0x2024
#define WGL_FULL_ACCELERATION_ARB               0x2027
#define WGL_SAMPLE_BUFFERS_ARB  0x2041
#define WGL_SAMPLES_ARB     0x2042

#define GL_TEXTURE_2D_MULTISAMPLE 0x9100

void initExtendedGL();

#endif