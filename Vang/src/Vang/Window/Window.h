#pragma once

#include "Vang/Utility/Events/Event.h"

namespace Vang::Windowing {

	enum class DISPLAY_MODE {
		WINDOWED,
		BORDERLESS,
		FULLSCREEN,
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Vang::Utility::Events::Event&)>;

		virtual void initialize(const std::string& title, uint32_t width, uint32_t height,
								DISPLAY_MODE displayMode);
		virtual void update() = 0;
		virtual void close()  = 0;

		virtual const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const = 0;

		const std::string& getTitle() const;
		uint32_t getWidth() const;
		uint32_t getHeight() const;
		DISPLAY_MODE getDisplayMode() const;
		bool getVSync() const;
		bool getMouseEnabled() const;

		virtual void setTitle(const std::string& title)				= 0;
		virtual void setResolution(uint32_t width, uint32_t height) = 0;
		virtual void setDisplayMode(DISPLAY_MODE displayMode)		= 0;
		virtual void setVSync(bool enabled)							= 0;
		virtual void setMouseEnabled(bool enabled)					= 0;

		virtual void* getNativeWindow() const = 0;

	protected:
		struct WindowData {
			std::string title{};
			uint32_t width{};
			uint32_t height{};
			DISPLAY_MODE displayMode{DISPLAY_MODE::WINDOWED};
			bool vSync{false};
			bool mouseEnabled{false};

			EventCallbackFn eventCallback;
		};

		WindowData m_data;
	};

}
