#pragma once

namespace Vang::UI {

	class Menu {
	public:
		Menu()						 = default;
		~Menu()						 = default;
		Menu(const Menu&)			 = delete;
		Menu(Menu&&)				 = default;
		Menu& operator=(const Menu&) = delete;
		Menu& operator=(Menu&&)		 = default;

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