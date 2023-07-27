#pragma once

namespace Vang {

	class Item;

	// When adding a new Usability Type make sure to add it to the createFromType() function
	enum class UsabilityType {
		Unusable,
		Placeable,
	};

	class Usability {
	public:
		virtual void use(Item&)				  = 0;
		virtual UsabilityType getType() const = 0;

		static std::unique_ptr<Usability> createFromType(UsabilityType usabilityType);
	};

}