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

		virtual const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const = 0;

		virtual void setTitle(std::string_view title) = 0;
		const std::string_view& getTitle() const;

		virtual void setResolution(uint32_t width, uint32_t height) = 0;
		uint32_t getWidth() const;
		uint32_t getHeight() const;
	protected:
		std::string_view m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_windowOpen = false;
	};

}
