// framework_register.
#include "improfx_core/framework_core.hpp"

// user register class header file.
#include "../imgui_profx_logic/improfx20_test.h"
#include "../imgui_profx_logic/StabilityTesting/improfx_fst_24h.h"

// 1. ʹ�÷���"REGISTER_USER_CLASS"ע����.
// 2. ʹ��"IMFXOBJ.ReflectionObjectCreate"����ע�����.
// [2023_11_16] RCSZ.

FXUCLASS(TestUserClass);
FXUCLASS(StabilityTesting);

void RegUserClassFunction()
{
	IMFXREF.ReflectionObjectCreate("TestUserClass", "ImProFx20");
	IMFXREF.ReflectionObjectCreate("StabilityTesting", "ARCH_FST");
}