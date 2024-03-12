// framework_renderer. [2023_12_28] RCSZ
/*
* ImProFX ��Ⱦ�����: IMFXGL 
* ��ǰ����: OpenGL 4.6 [64BIT] [C++17]
* Update: 20231228
*/

#ifndef _FRAMEWORK_RENDERER_H
#define _FRAMEWORK_RENDERER_H
#include "../framework_define.hpp"

#ifdef ENABLE_OPENGL_API
// opengl version 4.6 api.
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define DEFRES_FLAG_NORMAL   1 // ������Դ.
#define DEFRES_FLAG_INVALID -1 // ��Ч��Դ.

#define DEF_IMFXSTAT_SUCCESS 1
#define DEF_IMFXSTAT_FAILED  0

#define DEF_CHANNEL_RGB  3 // texture channels 3 bytes.
#define DEF_CHANNEL_RGBA 4 // texture channels 4 bytes.

using INIT_PARAMETERS = uint32_t;
using INIT_RETURN     = GLenum;

using ResUnique    = const std::string&;
using ResourceFlag = int;

using ImfxShader          = GLuint;
using ImfxTexture         = GLuint;
using ImfxVertexBuffer    = GLuint;
using ImfxVertexAttribute = GLuint;
using ImfxFrameBuffer     = GLuint;
using ImfxRenderBuffer    = GLuint;

constexpr GLuint OGLinvalidHandle = NULL;
#endif

// shader read script mode. 
enum ScriptReadMode {

	StringFilepath = 1 << 1, // ��ɫ���ļ�·��.
	StringScript   = 1 << 2  // ��ɫ���ı�.
};

// shader sampling texture filter mode.
enum TextureFilterMode {

	NearestNeighborFiltering = 1 << 1, // �ڽ�����.
	LinearFiltering          = 1 << 2, // ���Թ���.
	AnisotropicFiltering     = 1 << 3, // �������Թ���.
	MipmapFiltering          = 1 << 4  // Mipmap����.
};

// io save image_file mode_type.
enum SaveImageMode {

	ImageJPG = 1 << 1, // .jpgͼ���ļ�.
	ImagePNG = 1 << 2  // .pngͼ���ļ�.
};

// renderer logger function object.
using RendererLogger = void (*)(const LOGLABEL&, const char*, const char*, ...);

#endif