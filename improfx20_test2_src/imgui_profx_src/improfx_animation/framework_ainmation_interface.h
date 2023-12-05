// framework_ainmation_interface.
// [INTERFACE].

#ifndef _FRAMEWORK_AINMATION_INTERFACE_H
#define _FRAMEWORK_AINMATION_INTERFACE_H
#include "../improfx_log/framework_log.hpp"

// [2023_11_25](1): ImProFx��ܶ����ؼ��ӿ�.
namespace IFC_ANIM {

	// animation_base stateful(�̶��ڵ㶯���任)
	class ImAnimBaseStateful {
	public:
		virtual void UpdateTick(bool hover, bool active, float smooth_scale) = 0;
		virtual void ComponentsInit() = 0;

		virtual Vector4T<float>* AnimtransColor() = 0;
		virtual Vector2T<float>* AnimtransSize() = 0;
		virtual Vector2T<float>* AnimtransPosition() = 0;
	};

	// animation dynamic node data.
	struct ImAnimDynamicNode {

		Vector4T<float> TransColor;
		Vector2T<float> TransSize;
		Vector2T<float> TransPosition;
	};

	// animation_base dynamic(��̬�ڵ㶯���任)[δ����]
	class ImAnimBaseDynamic {
	public:
		virtual void UpdateTick(const char* state_key, float smooth_scale) = 0;
		virtual void ComponentsInit() = 0;

		virtual void ConfigAddNode(const char* key, ImAnimDynamicNode value) = 0;
		virtual void ConfigDeleteNode(const char* key) = 0;

		virtual Vector4T<float>* AnimtransColor() = 0;
		virtual Vector2T<float>* AnimtransSize() = 0;
		virtual Vector2T<float>* AnimtransPosition() = 0;
	};
}

#endif