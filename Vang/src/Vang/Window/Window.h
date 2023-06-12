#pragma once

class VangInst;

namespace Vang {

	class Window {
	public:
		Window() = delete;
		Window(VangInst& vangInst);
		Window(VangInst& vangInst, std::string_view title);
		Window(VangInst& vangInst, uint32_t width, uint32_t height);
		Window(VangInst& vangInst, std::string_view title, uint32_t width, uint32_t height);

		virtual void beginFrame() = 0;
		virtual void close()	  = 0;

		virtual const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const = 0;

		virtual void setTitle(std::string_view title) = 0;
		std::string_view getTitle();

		virtual void setResolution(uint32_t width, uint32_t height) = 0;
		uint32_t getWidth();
		uint32_t getHeight();
	protected:
		VangInst& m_vangInst;
		std::string_view m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_windowOpen = false;
	};

}
