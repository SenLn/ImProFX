// framework_log. [2023_10_11] RCSZ.

#ifndef _FRAMEWORK_LOG_HPP
#define _FRAMEWORK_LOG_HPP
#include <iostream>
#include <mutex>
#include <sstream>
#include <chrono>

#include "../framework_define.hpp"

#define LOG_ERR  "[ERROR]"   // ��ǩ <����>
#define LOG_WARN "[WARRING]" // ��ǩ <����>
#define LOG_INFO "[INFO]"    // ��ǩ <��Ϣ>
#define LOG_TRC  "[TRACE]"   // ��ǩ <����>
#define LOG_PERF "[PERF]"    // ��ǩ <����>

#define SYSTEM_MODULE_LABLE_log std::string("[log_system]: ")

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
		std::string ExtractLogSegment(uint32_t Lines);
	}
	// get src time[sec].
	size_t GetTimeNow();
}

namespace LOGFILE {
	// async process. write folder, timer.
	bool StartLogFileProcess(const char* folder, int64_t timer);
	bool FreeLogFileProcess();

	bool LogFileStatus();
}

#endif