#pragma once

#include <iostream>
#include <string.h>
#include <sstream>

namespace cpputils {

	template < class L = std::ostream >
	class logger {
	public:
		using out_type = L;

	private:
		logger_type &out;

	public:
		logger(L &out) : out(out) {
		}
	};

	template < class T, class... Args >
	void log(std::ostringstream msg, const T &val, const Args&... args) {
		msg << val;
		log(std::move(msg), args...);
	}

	void log(std::ostringstream msg) {
		std::cout << "Log -- " << msg.str() << std::endl;
	}

	template < class T, class... Args >
	void logFile(const char *file, int line, std::ostringstream msg, const T &val, const Args&... args) {
		msg << val;
		logFile(file, line, std::move(msg), args...);
	}

	void logFile(const char *file, int line, std::ostringstream msg) {
		std::cout << file << "(" << line << ") -- " << msg.str() << std::endl;
	}

} //namespace log

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else //__WIN32
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif //__WIN32

#ifdef ENABLE_LOGGING
#define LOG_SIMPLE(...) logging::log(std::ostringstream(), __VA_ARGS__)
#define LOG(...) logging::logFile(__FILENAME__, __LINE__, std::ostringstream(), __VA_ARGS__)
#else //ENABLE_LOGGING
#define LOG_SIMPLE(...)
#define LOG(...)
#endif //ENABLE_LOGGING