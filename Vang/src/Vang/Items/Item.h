#pragma once

#include "Usability/Usability.h"

namespace Vang {

	class Item {
	public:
		Item(const std::string& name);
		Item(const std::string& name, uint32_t amount, uint32_t maxStack);
		Item(const std::string& name, std::unique_ptr<Usability> usability);
		Item(const std::string& name, uint32_t amount, uint32_t maxStack,
			 std::unique_ptr<Usability> usability);
		~Item() = default;

		void use();

		const std::string& getName() const;

	protected:
		std::string m_name;
		uint32_t m_amount{1};
		uint32_t m_maxStack{1};
		std::unique_ptr<Usability> m_usability;
	};

}