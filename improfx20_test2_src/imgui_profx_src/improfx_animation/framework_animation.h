// framework_animation. [2023_11_01] RCSZ.

#ifndef _FRAMEWORK_ANIMATION_H
#define _FRAMEWORK_ANIMATION_H
#include "framework_ainmation_interface.h"

#define SYSMD_LB_ANIM "[im_animation]: "

namespace vector_transcalc {
	void TransVec2F(Vector2T<float>& input_src, const Vector2T<float>& input_tag, const float& cst, const float& speed, const float& smooth);
	void TransVec4F(Vector4T<float>& input_src, const Vector4T<float>& input_tag, const float& cst, const float& speed, const float& smooth);
}

namespace ImGuiProAnim {
	/*
	* ImGuiProAnim �����ؼ�ע��
	* @param  input (FrmDat.DataAnimation), key (�������Hash.key), comp (������ɵ��������)
	* @return state
	*/
	bool AnimCompReg(
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input, 
		const char*														key, 
		IFC_ANIM::ImAnimBaseStateful*									comp
	);
	/*
	* ImGuiProAnim �����ؼ�ɾ��
	* @param  input (FrmDat.DataAnimation), key (�������Hash.key)
	* @return state
	*/
	bool AnimCompDelete(std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input, const char* key);

	class ImAnimButton :public IFC_ANIM::ImAnimBaseStateful {
	protected:
		Vector4T<float> anim_color = {}; // smooth transformation color. button
		Vector2T<float> anim_size  = {}; // scale size.
		
	public:
		// hover = false, active = false, mode: normal
		// hover = true,  active = false, mode: hover
		// hover = true,  active = true,  mode: active
		void UpdateTick(bool hover, bool active, float smooth_scale) override;

		void ComponentsInit() override {
			anim_color = ConfigNormalColor;
			anim_size  = ConfigNormalSize;
		}

		Vector4T<float>* AnimtransColor() override { return &anim_color; };
		Vector2T<float>* AnimtransSize() override { return &anim_size; };
		Vector2T<float>* AnimtransPosition() override { return nullptr; };

		Vector4T<float> ConfigNormalColor = {}, ConfigHoverColor = {}, ConfigActiveColor = {};
		Vector2T<float> ConfigNormalSize = {}, ConfigHoverSize = {}, ConfigActiveSize = {};
		
		float ConfigColorTransSpeed = 1.0f;
		float ConfigSizeTransSpeed  = 1.0f;
	};

	/*
	* ������ť�����ؼ�����
	* @param  copy = nullptr (���ڸ��������úõĶ���)
	* @return ImAnimButton* 
	*/
	ImAnimButton* CreateAnimButton(ImAnimButton* copy = nullptr);

	/*
	* ���ð�ť�����ؼ�
	* @param  unique_name (��ť�ı�[Unique]), input (FrmDat.DataAnimation), comp_name (�������Key), trans_smooth = 1.0f (��������)
	* @return bool
	*/
	bool CallAnimButton(
		const char*                                                     unique_name, 
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input,
		const char*                                                     comp_name, 
		float                                                           trans_smooth = 1.0f
	);

	/*
	* ����ͼƬ��ť�����ؼ�
	* @param  unique_name (��ť�ı�[Unique]), input (FrmDat.DataAnimation), comp_name (�������Key), texture_hd (������),
	* @param  trans_smooth = 1.0f (��������)
	* @return bool
	*/
	bool CallAnimButtonImage(
		const char*														unique_name,
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input,
		const char*														comp_name,
		uint32_t														texture_hd,
		float															trans_smooth = 1.0f
	);

	class ImAnimFixedWindow :public IFC_ANIM::ImAnimBaseStateful {
	protected:
		Vector4T<float> anim_color = {}; // smooth transformation color. window background
		Vector2T<float> anim_size  = {}; // scale size.

	public:
		// hover = false, active = false, mode: close
		// hover = false, active = true,  mode: open
		void UpdateTick(bool hover, bool active, float smooth_scale) override;

		void ComponentsInit() override {
			anim_color = ConfigCloseColor;
			anim_size  = ConfigCloseSize;
		}

		Vector4T<float>* AnimtransColor() override { return &anim_color; };
		Vector2T<float>* AnimtransSize() override { return &anim_size; };
		Vector2T<float>* AnimtransPosition() override { return nullptr; };

		Vector4T<float> ConfigCloseColor = {}, ConfigOpenColor = {};
		Vector2T<float> ConfigCloseSize = {}, ConfigOpenSize = {};

		float ConfigColorTransSpeed = 1.0f;
		float ConfigSizeTransSpeed  = 1.0f;
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
	* @param  unique_name (��ť�ı�[Unique]), input (FrmDat.DataAnimation), comp_name (�������Key), window_ui (�Ӵ��ں�������),
	* @param  open_flag (imgui����"p_open"��־), flags = 0 (imgui���ڱ�־"ImGuiWindowFlags"), trans_smooth = 1.0f (��������)
	* @return void
	*/
	void CallAnimFixedWindow(
		const char*														unique_name,
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input,
		const char*														comp_name,
		bool&															open_flag,
		std::function<void()>											window_ui,
		ImGuiWindowFlagsAm												flags        = 0,
		float															trans_smooth = 1.0f
	);
	
	class ImAnimSourceComp :public IFC_ANIM::ImAnimBaseStateful {
	protected:
		Vector4T<float> anim_color    = {}; // smooth transformation color.
		Vector2T<float> anim_size     = {}; // scale size.
		Vector2T<float> anim_position = {}; // move position.

	public:
		// hover = false, active = false, mode: low
		// hover = false, active = true,  mode: high
		void UpdateTick(bool hover, bool active, float smooth_scale) override;

		void ComponentsInit() override {
			anim_color    = ConfigLowColor;
			anim_size     = ConfigLowSize;
			anim_position = ConfigLowPosition;
		}

		Vector4T<float>* AnimtransColor() override { return &anim_color; };
		Vector2T<float>* AnimtransSize() override { return &anim_size; };
		Vector2T<float>* AnimtransPosition() override { return &anim_position; };

		Vector4T<float> ConfigLowColor = {}, ConfigHighColor = {};
		Vector2T<float> ConfigLowSize = {}, ConfigHighSize = {};
		Vector2T<float> ConfigLowPosition = {}, ConfigHighPosition = {};

		float ConfigColorTransSpeed    = 1.0f;
		float ConfigSizeTransSpeed     = 1.0f;
		float ConfigPositionTransSpeed = 1.0f;
	};

	/*
	* ����Դ�����ؼ����� [�ƶ� & ��ɫ]
	* @param  copy = nullptr (���ڸ��������úõĶ���)
	* @return ImAnimSrcMoveColor*
	*/
	ImAnimSourceComp* CreateAnimSourceComp(ImAnimSourceComp* copy = nullptr);

	/*
	* ����Դ�����ؼ� [�ƶ� & ��ɫ].
	* @param  input (FrmDat.DataAnimation), comp_name (�������Key), state_flag (״̬�л�),
	* @param  context (��ɫ�任&��С�任 ͨ����������, ����ɽ�����ڻ���λ�ñ任), trans_smooth = 1.0f (��������)
	* @return void
	*/
	void CallAnimSourceComp(
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input,
		const char*														comp_name,
		bool															state_flag,
		std::function<void(Vector4T<float>, Vector2T<float>)>			context,
		float															trans_smooth = 1.0f
	);

	// ����λ�� (���ڿؼ����ٹ�λ).
	void CallAnimSourceCompRES(
		std::unordered_map<std::string, IFC_ANIM::ImAnimBaseStateful*>& input,
		const char*														comp_name,
		Vector4T<float>													setcolor,
		Vector2T<float>													setsize,
		Vector2T<float>													setpoition
	);
}

#endif