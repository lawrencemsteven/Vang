#pragma once

namespace Vang {

	class Item;

	class Usability {
	public:
		virtual void use(Item&) = 0;
	};

}