// framework_renderer_ext. renderer extension interface.
/*
* ImProFX IMFXGL ͼ�γ������չ�ӿ� Version: 0.1.0, Update: 2024.01.03
* ��ɫ��֧��: ������ɫ��, ƬԪ��ɫ��, ������ɫ��, ����ϸ�ֿ�����ɫ��, ����ϸ��������ɫ��, ������ɫ��, ����׷����ɫ��.
* ��ǰ����ͼ�ο�: OpenGL
* ��չ�ӿ�ֻ��Ԥ��(�ݲ�����)
*/

#ifndef _FRAMEWORK_RENDERER_EXT_H
#define _FRAMEWORK_RENDERER_EXT_H

#define ENABLE_OPENGL_API
#include "framework_renderer.h"

// graphics pipeline.
class Ext_ImFxGLmanagerShaderGP {
public:
	// loader: vertex, fragment shader.
	virtual void ShaderLoaderVS(const std::string& vs, ScriptReadMode mode = StringFilepath) = 0;
	virtual void ShaderLoaderFS(const std::string& fs, ScriptReadMode mode = StringFilepath) = 0;

	// loader: geometry, tessellation_control, tessellation_evaluation shader.
	virtual void ShaderLoaderGES(const std::string& exts, ScriptReadMode mode = StringFilepath) = 0;
	virtual void ShaderLoaderTCS(const std::string& exts, ScriptReadMode mode = StringFilepath) = 0;
	virtual void ShaderLoaderTES(const std::string& exts, ScriptReadMode mode = StringFilepath) = 0;

	virtual bool CreateCompileShaders() = 0;

	virtual ImfxShader _MS_GETRES(ResourceFlag& flag) = 0;
};

// compute pipeline.
class Ext_ImFxGLmanagerShaderCP {
public:
	// loader: compute shader.
	virtual void ShaderLoaderCS(const std::string& exts, ScriptReadMode mode = StringFilepath) = 0;

	virtual bool CreateCompileShaders() = 0;

	virtual ImfxShader _MS_GETRES(ResourceFlag& flag) = 0;
};

// ray_tracing pipeline.
class Ext_ImFxGLmanagerShaderRTP {
public:
	// loader: ray_tracing shader.
	virtual void ShaderLoaderRTS(const std::string& exts, ScriptReadMode mode = StringFilepath) = 0;
	virtual bool DeviceRayTracing() = 0;

	virtual bool CreateCompileShaders() = 0;

	virtual ImfxShader _MS_GETRES(ResourceFlag& flag) = 0;
};

// IMFXGL EXT texture attribute. (texture3d)
struct Ext_TextureAttr3D {
	uint32_t Layers, Width, Height, Channels;
	ImfxTexture Texture;

	Ext_TextureAttr3D() : Texture{}, Layers(0), Width(0), Height(0), Channels(0) {}
	Ext_TextureAttr3D(ImfxTexture tex, uint32_t num, uint32_t x, uint32_t y, uint32_t ch) :
		Texture(tex), Layers(num), Width(x), Height(y), Channels(ch)
	{}
};

class Ext_ImFxGLmanagerTexture3D {
	virtual bool CreateTexture(
		uint32_t          layers, 
		uint32_t          width, 
		uint32_t          height, 
		uint32_t          channels, 
		uint8_t*          data, 
		TextureFilterMode mode
	) = 0;
	virtual bool CreateTextureEmpty(uint32_t layers, uint32_t width, uint32_t height, uint32_t channels, TextureFilterMode mode) = 0;
	virtual bool CreateTextureLoader(const std::vector<std::string>& files, TextureFilterMode mode) = 0;

	virtual Ext_TextureAttr3D _MS_GETRES(ResourceFlag& flag) = 0;
};

#endif