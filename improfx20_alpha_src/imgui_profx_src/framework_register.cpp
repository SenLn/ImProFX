// framework_register.
#include "improfx_core/framework_core.hpp"

// user register class header file.
#include "../imgui_profx_logic/demo/improfx2_demo.h"

// 1. ʹ�÷���"REGISTER_USER_CLASS"ע����.
// 2. ʹ��"IMFXOBJ.ReflectionObjectCreate"����ע�����.
// [2023_11_16] RCSZ.

FXUCLASS(ImprofxDemoClass);

void RegUserClassFunction()
{
	IMFXREF.ReflectionObjectCreate("ImprofxDemoClass", "ImProFx2aDemo");
}