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
		Item(const std::string& name, UsabilityType usabilityType);
		Item(const std::string& name, uint32_t amount, uint32_t maxStack,
			 UsabilityType usabilityType);
		~Item() = default;

		void use();

		void setName(const std::string& name);
		void setAmount(uint32_t amount);
		void incrementAmount(int32_t amount);
		void setMaxStack(uint32_t maxStack);
		void setUsability(std::unique_ptr<Usability> usability);
		void setUsability(UsabilityType usbilityType);

		const std::string& getName() const;
		uint32_t getAmount() const;
		uint32_t getMaxStack() const;
		Usability& getUsability();
		UsabilityType getUsabilityType() const;

		const std::string& getName() const;

	protected:
		std::string m_name;
		uint32_t m_amount{1};
		uint32_t m_maxStack{1};
		std::unique_ptr<Usability> m_usability;
	};

}