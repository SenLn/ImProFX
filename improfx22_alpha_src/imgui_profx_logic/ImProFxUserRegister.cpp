// ImProFxUserRegister. [system_file] RCSZ.
#include "../imgui_profx_src/improfx_core/framework_core.hpp"

// user register class header_file:
#include "demo2/improfx2_demo.h"

// 1. ʹ�÷���"FXUCLASS"ע����.
// 2. ʹ��"IMFXREF.ReflectionObjectCreate"����ע�����.
// [2023_12_14] RCSZ.

FXUCLASS(ImprofxDemoClass22);

// [��ʼ���׶�]: �û������ע��.
void CoreModuleSystem::ProfxSystemFramework::InitialStageRegUserClass()
{
	IMFXREF.ReflectionObjectCreate("ImprofxDemoClass22", "ImProFx20Ademo");
}