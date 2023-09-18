#pragma once


#ifdef VANG_DEBUG
#	define VANG_FATAL(message) Vang::Utility::Log::Fatal(message);
#	define VANG_ERROR(message) Vang::Utility::Log::Error(message);
#	define VANG_WARN(message) Vang::Utility::Log::Warn(message);
#	define VANG_INFO(message) Vang::Utility::Log::Info(message);
#	define VANG_DEBUG(message) Vang::Utility::Log::Debug(message);
#else
#	define VANG_FATAL(message) Vang::Utility::Log::FatalExceptionOnly(message);
#	define VANG_ERROR(message)
#	define VANG_WARN(message)
#	define VANG_INFO(message)
#	define VANG_DEBUG(message)
#endif

namespace Vang::Utility {

	class Log {
	public:
		enum class Level {
			FATAL,
			ERROR,
			WARN,
			INFO,
			DEBUG,
		};

		static void SetLevel(Level level);
		static Level GetLevel();

		static void Debug(const std::string_view message,
						  const std::source_location location = std::source_location::current());
		static void Info(const std::string_view message,
						 const std::source_location location = std::source_location::current());
		static void Warn(const std::string_view message,
						 const std::source_location location = std::source_location::current());
		static void Error(const std::string_view message,
						  const std::source_location location = std::source_location::current());
		static void Fatal(const std::string_view message,
						  const std::source_location location = std::source_location::current());
		static void FatalExceptionOnly(const std::string_view message,
						  const std::source_location location = std::source_location::current());

	private:
		static inline void Print(std::string_view color, std::string_view message,
								 std::source_location location, bool throw_error = false);

	private:
		static Level s_level;
	};

}