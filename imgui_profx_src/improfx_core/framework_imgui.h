// framework_imgui. [2023_10_13] RCSZ.

#ifndef _FRAMEWORK_IMGUI_H
#define _FRAMEWORK_IMGUI_H
#include "../improfx_log/framework_log.hpp"

#include "imgui_glfw/imgui.h"
#include "imgui_glfw/imgui_impl_glfw.h"
#include "imgui_glfw/imgui_impl_opengl3.h"

#if defined(_MSV_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib,"legacy_stdio_definitons.lib")
#endif

#define SYSTEM_MODULE_LABLE_imgui std::string("[gui_imgui]: ")

// ImGui ȫ�ֿؼ����(��λ��).
#define IMGUI_ITEM_SPC ImGui::GetStyle().ItemSpacing.x

namespace CoreModuleImGui {

	struct GuiConfig {

		std::string     shader_version;
		std::string     fonts_filepath;
		Vector4T<float> fonts_color;
		float           fonts_size;
		float           frame_rounding, window_rounding;

		GuiConfig() :
			shader_version  ({}),
			fonts_filepath  ({}),
			fonts_color     ({}), 
			fonts_size      (16.0f),
			frame_rounding  (0.0f),
			window_rounding (0.0f)
		{}
		GuiConfig(std::string version, std::string path, Vector4T<float> color, float size, float round, float wround) :
			shader_version  (version),
			fonts_filepath  (path),
			fonts_color     (color),
			fonts_size      (size),
			frame_rounding  (round),
			window_rounding (wround)
		{}
	};

	class RenderImGui {
	protected:
		void ImGuiInit(GLFWwindow* window_object, GuiConfig cfgdata = {});
		void ImGuiFree();
		
		void RenderGuiContextA();
		void RenderGuiContextB();
	};
}

namespace ImGuiPro {
	/*
	* ȫ�����ڱ���(No WindowContext)
	* @param  texture_hd (������), draw_fps = true (FPS��ʾ)
	* @return void
	*/
	void FullScreenBackground(uint32_t texture_hd, bool draw_fps = true);
	/*
	* ȫ�Ӵ��ڱ���(Size���յ�ǰ���ڴ�С����)
	* @param  texture_hd (������), uv_cropping (uv���Ĳü�����)
	* @return void
	*/
	void FullWindowBackground(uint32_t texture_hd, ImVec2 uv_cropping = ImVec2(1.0f, 1.0f));
	/*
	* �������Ӵ���(BeginBg-ImGui::End), "FullWindowBackground"����
	* @param  name (����Unique), texture_hd (������), size (�̶���С), uv_cropping (uv���Ĳü�����), p_open = (bool*)0, flags = 0
	* @return void
	*/
	void BeginBg(
		const char*      name, 
		uint32_t         texture_hd, 
		ImVec2           size, 
		ImVec2           uv_cropping = ImVec2(1.0f, 1.0f), 
		bool*            p_open      = (bool*)0, 
		ImGuiWindowFlags flags       = 0
	);
	/*
	* �ؼ����м���
	* @param  width (�ؼ����)
	* @return float (����x�����)
	*/
	float ItemCenteredCalc(float width);
	/*
	* ���д���ɫ�ı�
	* @param  text, color
	* @return void
	*/
	void TextCentered(const char* text, ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	/*
	* ���ı�ͼƬ��ť
	* @param  name (��ť�����ı�), texture_hd (������), size (��ť��С), id (��ťUnique���), uv_cropping (uv���Ĳü�����)
	* @return bool (stat flag)
	*/
	bool ButtonImageText(const char* name, uint32_t texture_hd, ImVec2 size, uint32_t id, ImVec2 uv_cropping = ImVec2(1.0f, 1.0f));
	/*
	* �����ı������
	* @param  name (����Title), buffer (char*), buffer_size (length), width (����򳤶�), password (�鿴�����־), id (imgui unique id) 
	* @return void
	*/
	void InputTextCentered(const char* name, char* buffer, size_t buffer_size, float width, bool& password, int id);
	/*
	* ���������������
	* @param  size (���ڹ̶���С), focus (�Ƿ񳣾۽�), window_ui(�Ӵ��ڰ�װ)
	* @return void
	*/
	void MouseFloatingWindow(ImVec2 size, bool focus, std::function<void()> window_ui);
	/*
	* ģ��LED״̬ɫ��
	* @param  state (true:open, false:close), h_color (�ߵ�ƽ��ɫ), l_color (�͵�ƽ��ɫ), size (rect��С)
	* @return void
	*/
	void AnalogLED(
		bool   state,
		ImVec4 h_color = ImVec4(0.0f, 1.0f, 1.0f, 1.0f),
		ImVec4 l_color = ImVec4(0.0f, 0.1f, 0.1f, 1.0f),
		ImVec2 size    = ImVec2(20.0f, 20.0f)
	);

	// ImGui::PushStyleColor �ط�װ ImVec4 => Vector4T<float>
	void PushStyleColor(ImGuiCol index, Vector4T<float> color);

	// ���� + �ָ���.
	void EndEnterLine();
}

#endif