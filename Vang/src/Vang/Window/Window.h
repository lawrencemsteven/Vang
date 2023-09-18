#pragma once

#include "Vang/Utility/Events/Event.h"

namespace Vang::Windowing {

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const std::string& title, uint32_t width, uint32_t height);

		virtual void update() = 0;
		virtual void close()	  = 0;

		virtual const char** getGraphicsAPIInstanceExtensions(uint32_t* count) const = 0;

		const std::string& getTitle() const;
		uint32_t getWidth() const;
		uint32_t getHeight() const;
		bool getVSync() const;

		virtual void setTitle(const std::string& title)				   = 0;
		virtual void setResolution(uint32_t width, uint32_t height)	   = 0;
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled)							   = 0;

		virtual void* getNativeWindow() const = 0;

	protected:
		struct WindowData {
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_data;
	};

}
