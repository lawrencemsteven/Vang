#pragma once

namespace Vang {

	class Window {
	public:
		Window();
		Window(std::string_view title);
		Window(uint32_t width, uint32_t height);
		Window(std::string_view title, uint32_t width, uint32_t height);

		virtual void beginFrame() = 0;
		virtual void close()	  = 0;

		virtual void setTitle(std::string_view title) = 0;
		std::string_view getTitle();

		virtual void setResolution(uint32_t width, uint32_t height) = 0;
		uint32_t getWidth();
		uint32_t getHeight();
	protected:
		std::string_view m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool windowOpen = false;
	};

}
