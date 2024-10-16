#pragma once

namespace Vang::UI {

	class ImGuiMenu {
	public:
		ImGuiMenu()							   = default;
		~ImGuiMenu()						   = default;
		ImGuiMenu(const ImGuiMenu&)			   = delete;
		ImGuiMenu(ImGuiMenu&&)				   = default;
		ImGuiMenu& operator=(const ImGuiMenu&) = delete;
		ImGuiMenu& operator=(ImGuiMenu&&)	   = default;

		bool getDrawMenu() const;
		bool& getDrawMenu();

		void setDrawMenu(bool drawMenu);

		virtual void onAttach(){};
		virtual void onDetach(){};
		virtual void draw() = 0;

	protected:
		bool m_drawMenu{true};
	};

}