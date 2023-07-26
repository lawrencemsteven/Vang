#pragma once

#include "Event.h"
#include "Vang/Utility/Input/Input.h"

namespace Vang {
	class KeyEvent : public Event {
	public:
		inline KEY getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KEY keycode)
			: m_keyCode(keycode) {}

		KEY m_keyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KEY keycode, int repeatCount)
			: KeyEvent(keycode),
			  m_repeatCount(repeatCount) {}

		inline int getRepeatCount() const { return m_repeatCount; }
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << static_cast<int>(m_keyCode) << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(KEY keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << static_cast<int>(m_keyCode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(KEY keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << static_cast<int>(m_keyCode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	private:
		int m_repeatCount;
	};
}