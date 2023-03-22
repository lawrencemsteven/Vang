#pragma once

class VangInst;

namespace Vang {

	class GraphicsAPI {
	public:
		GraphicsAPI() = delete;
		GraphicsAPI(VangInst& vangInst);
		GraphicsAPI(VangInst& vangInst, std::string_view application_name);

		virtual void beginFrame() = 0;

		std::string_view getApplicationName();

	protected:
		VangInst& m_vangInst;
		std::string_view m_applicationName;
	};

}
