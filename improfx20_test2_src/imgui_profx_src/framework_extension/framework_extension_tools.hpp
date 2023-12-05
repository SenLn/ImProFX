// framework_extension_tools. RCSZ 2023_12_02.
// �ṩ����չģ��ʹ��, �����������.

#ifndef _FRAMEWORK_EXTENSION_TLOOS_HPP
#define _FRAMEWORK_EXTENSION_TLOOS_HPP
#include <memory>
#include "../improfx_log/framework_log.hpp"

enum EXTLOGLABEL {
	LogError   = 1 << 1, // ����
	LogWarning = 1 << 2, // ����
	LogInfo    = 1 << 3, // ��Ϣ
	LogTrace   = 1 << 4, // ����
	LogPerf    = 1 << 5  // ����
};

namespace ExtLog {
#define EXT_LOGGER_BUFFER_LEN 3072
	// extension module logger.
	inline void ELog(const EXTLOGLABEL& Label, const char* ModuleLabel, const char* LogText, ...) {
		char LoggerStrTemp[EXT_LOGGER_BUFFER_LEN] = {};

		va_list ParamArgs;
		va_start(ParamArgs, LogText);
		sprintf_s(LoggerStrTemp, EXT_LOGGER_BUFFER_LEN, LogText, ParamArgs);
		va_end(ParamArgs);

		LOGCONS::PushLogProcess((LOGLABEL)Label, "[EXT]:" + std::string(ModuleLabel) + LoggerStrTemp);
	}
#define FRMEXT_MODULE std::string("[extension_tools]: ")
}

template<typename ClassT, typename... ParamT>
std::shared_ptr<ClassT> SharedPointerObject(ParamT ...params) {
	ClassT* CreateObject = new ClassT(params...);
	// create object => std::shared_ptr.
	ExtLog::ELog(LogTrace, FRMEXT_MODULE + "create extension object: " + typeid(ClassT).name());
	return std::shared_ptr<ClassT>(CreateObject);
}

#endif