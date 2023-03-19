#pragma once

namespace Vang {

	class Application {
	public:
		Application() { Application(""); }
		Application(std::string_view name)
			: m_name{name} {}

		const std::string_view getName() { return m_name; }

	private:
		std::string_view m_name;
	};

}