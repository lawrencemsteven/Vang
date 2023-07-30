#pragma once

namespace Vang {

	class Mod {
	public:
		Mod(std::string name);

		const std::string& getName() const;

	protected:
		std::string m_name;
	};

}