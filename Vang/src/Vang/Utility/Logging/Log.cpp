#include "Log.h"

namespace Vang {

	Log::Level Log::s_level = Log::Level::DEBUG;

	void Log::SetLevel(Log::Level level) { s_level = level; }
	Log::Level Log::GetLevel() { return s_level; }

	void Log::Debug(const std::string_view message, const std::source_location location) {
		if (s_level >= Level::DEBUG) { Print("\033[32m", message, location); }
	}

	void Log::Info(const std::string_view message, const std::source_location location) {
		if (s_level >= Level::INFO) { Print("\033[0m", message, location); }
	}

	void Log::Warn(const std::string_view message, const std::source_location location) {
		if (s_level >= Level::WARN) { Print("\033[33m", message, location); }
	}

	void Log::Error(const std::string_view message, const std::source_location location) {
		if (s_level >= Level::ERROR) { Print("\033[31m", message, location); }
	}

	void Log::Fatal(const std::string_view message, const std::source_location location) {
		if (s_level >= Level::FATAL) { Print("\033[91;1m", message, location, true); }
	}

	inline void Log::Print(std::string_view color, std::string_view message,
						   std::source_location location, bool throw_error) {
		std::string output =
			std::format("{}File: {}({}:{}) `{}`: {}\033[0m\n", color, location.file_name(),
						location.line(), location.column(), location.function_name(), message);

		std::cout << output;
		if (throw_error) { throw std::exception(message.data()); }
	}

}