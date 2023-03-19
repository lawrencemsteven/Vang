#pragma once

namespace Vang {

	class Log {
	public:
		enum Level {
			FATAL,
			ERROR,
			WARN,
			INFO,
			DEBUG,
		};

		static void SetLevel(Level level);
		static Level GetLevel();

		static void
		Debug(const std::string_view message,
			  const std::source_location location = std::source_location::current());
		static void
		Info(const std::string_view message,
			 const std::source_location location = std::source_location::current());
		static void
		Warn(const std::string_view message,
			 const std::source_location location = std::source_location::current());
		static void
		Error(const std::string_view message,
			  const std::source_location location = std::source_location::current());
		static void
		Fatal(const std::string_view message,
			  const std::source_location location = std::source_location::current());

	private:
		static inline void Print(std::string_view color, std::string_view message,
								 std::source_location location, bool throw_error = false);

	private:
		static Level s_level;
	};

}