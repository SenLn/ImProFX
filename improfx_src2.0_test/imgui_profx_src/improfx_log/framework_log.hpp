// framework_log. [2023_10_11] RCSZ.

#ifndef _FRAMEWORK_LOG_HPP
#define _FRAMEWORK_LOG_HPP
#include <iostream>
#include <sstream>
#include <chrono>

#include "../framework_define.hpp"

#define LOG_ERR  "[ERROR]"   // ��ǩ <����>
#define LOG_WARN "[WARRING]" // ��ǩ <����>
#define LOG_INFO "[INFO]"    // ��ǩ <��Ϣ>
#define LOG_TRC  "[TRACE]"   // ��ǩ <����>
#define LOG_PERF "[PERF]"    // ��ǩ <����>

#define SYSMD_LB_LOG std::string("[log_system]: ")

// format number => string, %xd(fill_zero).
std::string number_fmt_fillzero(uint32_t number, int32_t digits);

namespace LOGCONS {
	/*
	* @param  string, bool
	* @return void
	*/
	void LogInfoPush(const char* Lable, std::string LogStrText);
	/*
	* @param  void
	* @return Vector3T<size_t> LogLines x : Lines, y : warring, z : error
	*/
	Vector3T<size_t> LogLinesNumber();

	namespace ReadLogCache {
		/*
		* ��ȡ��־��.
		* @param  uint32_t [End, End - LINES]
		* @return string
		*/
		std::vector<std::string> ExtractLogSegment(uint32_t Lines);
	}
	// get src time[sec].
	size_t GetTimeNow();
}

namespace LOGFILE {
	// async process. write folder.
	bool StartLogFileProcess(const char* folder);
	bool FreeLogFileProcess();
}

#endif