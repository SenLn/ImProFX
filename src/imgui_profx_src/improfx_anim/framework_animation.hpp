// framework_animation. [2023_11_01] RCSZ.

#ifndef _FRAMEWORK_ANIMATION_H
#define _FRAMEWORK_ANIMATION_H
#include "../improfx_log/framework_log.hpp"

#define SYSTEM_MODULE_LABLE_animation std::string("[im_animation]: ")

namespace ImGuiProAnim {

	class ImAnimationBase {
	public:
		virtual void update_tick(bool hover, bool active, float smooth_scale) = 0;
		virtual void comp_init() = 0;

		virtual Vector4T<float> animtrans_color() = 0;
		virtual Vector2T<float> animtrans_size() = 0;
		virtual Vector2T<float> animtrans_position() = 0;
	};

	/*
	* ImGuiProAnim �����ؼ�ע��
	* @param  input (DataCompAnim), key (�������Hash.key), comp (������ɵ��������)
	* @return void
	*/
	void AnimCompReg(std::unordered_map<std::string, ImAnimationBase*>& input, const char* key, ImAnimationBase* comp);

	class ImAnimButton :public ImAnimationBase {
	protected:
		Vector4T<float> anim_color = {}; // smooth transformation color. button
		Vector2T<float> anim_size = {};  // scale size.
		
	public:
		// hover = false, active = false, mode: normal
		// hover = true,  active = false, mode: hover
		// hover = true,  active = true,  mode: active
		void update_tick(bool hover, bool active, float smooth_scale) override;

		void comp_init() override {
			anim_color = config_normal_color;
			anim_size  = config_normal_size;
		}

		Vector4T<float> animtrans_color() override { return anim_color; };
		Vector2T<float> animtrans_size() override { return anim_size; };
		Vector2T<float> animtrans_position() override { return Vector2T<float>(); };

		Vector4T<float> config_normal_color = {}, config_hover_color = {}, config_active_color = {};
		Vector2T<float> config_normal_size = {}, config_hover_size = {}, config_active_size = {};
		
		float config_color_transspeed = 1.0f;
		float config_size_transspeed  = 1.0f;
	};

	/*
	* ������ť�����ؼ�����
	* @param  copy = nullptr (���ڸ��������úõĶ���)
	* @return ImAnimButton* 
	*/
	ImAnimButton* CreateAnimButton(ImAnimButton* copy = nullptr);

	/*
	* ���ð�ť�����ؼ�
	* @param  unique_name (��ť�ı�[Unique]), input (DataCompAnim), comp_name (�������Key), trans_smooth = 1.0f (FPSƽ�����Ų���)
	* @return bool
	*/
	bool CallAnimButton(
		const char*                                        unique_name, 
		std::unordered_map<std::string, ImAnimationBase*>& input, 
		const char*                                        comp_name, 
		float                                              trans_smooth = 1.0f
	);

	/*
	* ����ͼƬ��ť�����ؼ�
	* @param  unique_name (��ť�ı�[Unique]), input (DataCompAnim), comp_name (�������Key), texture_hd (������),
	* @param  trans_smooth = 1.0f (FPSƽ�����Ų���)
	* @return bool
	*/
	bool CallAnimButtonImage(
		const char*                                        unique_name,
		std::unordered_map<std::string, ImAnimationBase*>& input,
		const char*                                        comp_name,
		uint32_t                                           texture_hd,
		float                                              trans_smooth = 1.0f
	);

	class ImAnimFixedWindow :public ImAnimationBase {
	protected:
		Vector4T<float> anim_color = {}; // smooth transformation color. window background
		Vector2T<float> anim_size = {};  // scale size.

	public:
		// hover = false, active = false, mode: close
		// hover = false, active = true,  mode: open
		void update_tick(bool hover, bool active, float smooth_scale) override;

		void comp_init() override {
			anim_color = config_close_color;
			anim_size = config_close_size;
		}

		Vector4T<float> animtrans_color() override { return anim_color; };
		Vector2T<float> animtrans_size() override { return anim_size; };
		Vector2T<float> animtrans_position() override { return Vector2T<float>(); };

		Vector4T<float> config_close_color = {}, config_open_color = {};
		Vector2T<float> config_close_size = {}, config_open_size = {};

		float config_color_transspeed = 1.0f;
		float config_size_transspeed = 1.0f;
	};

	/*
	* �����̶�(��С)���ڶ����ؼ�����
	* @param  copy = nullptr (���ڸ��������úõĶ���)
	* @return ImAnimFixedWindow*
	*/
	ImAnimFixedWindow* CreateAnimFixedWindow(ImAnimFixedWindow* copy = nullptr);

	typedef int ImGuiWindowFlagsAm;
	/*
	* ���ù̶�(��С)���ڶ����ؼ�.
	* @param  unique_name (��ť�ı�[Unique]), input (DataCompAnim), comp_name (�������Key), window_ui (�Ӵ��ڰ�װ),
	* @param  open_flag (imgui����p_open��־), flags = 0 (imgui���ڱ�־[ImGuiWindowFlags]), trans_smooth = 1.0f (FPSƽ�����Ų���)
	* @return void
	*/
	void CallAnimFixedWindow(
		const char*                                        unique_name,
		std::unordered_map<std::string, ImAnimationBase*>& input,
		const char*                                        comp_name,
		bool&                                              open_flag,
		std::function<void()>                              window_ui,
		ImGuiWindowFlagsAm                                 flags = 0,
		float                                              trans_smooth = 1.0f
	);
}

#endif