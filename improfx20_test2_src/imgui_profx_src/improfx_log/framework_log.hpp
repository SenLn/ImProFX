// framework_log. [2023_10_11] RCSZ.

#ifndef _FRAMEWORK_LOG_HPP
#define _FRAMEWORK_LOG_HPP
#include <iostream>
#include <sstream>
#include <chrono>
#include <cstdarg>

#include "../framework_define.hpp"

enum LOGLABEL {
	LOG_ERR  = 1 << 1, // ��ǩ <����>
	LOG_WARN = 1 << 2, // ��ǩ <����>
	LOG_INFO = 1 << 3, // ��ǩ <��Ϣ>
	LOG_TRC  = 1 << 4, // ��ǩ <����>
	LOG_PERF = 1 << 5  // ��ǩ <����>
};

#define SYSMD_LB_LOG "[framework_log]: "

// format number => string, %xd(fill_zero).
std::string number_fmt_fillzero(uint32_t number, int32_t digits);

namespace LOGCONS {
	// @param "Label" (level label), "LogStrText" (log information)
	void PushLogProcess(const LOGLABEL& Label, const std::string& LogStrText);
	// @param label, module_label, text, params. [20231205]
	void PushLogger(const LOGLABEL& Label, const char* ModuleLabel, const char* LogText, ...);

	// false: not printing on the console.
	void SET_PRINTLOG_STATE(bool State);
	
	// @return Vector3T<size_t> (x : Lines, y : warring, z : error)
	Vector3T<size_t> LogLinesStatistics();

	namespace ReadLogCache {
		/*
		* ��ȡ��־��.
		* @param  uint32_t [End, End - LINES]
		* @return string
		*/
		std::vector<std::string> ExtractLogSegment(const uint32_t& Lines);
	}
	// get src time[sec].
	size_t GetTimeNow();
}

namespace LOGFILE {
	// async thread process. write folder.
	bool StartLogFileProcess(const char* folder);
	bool FreeLogFileProcess();
}

#endif