#pragma once

namespace Vang {

	class Mod {
	public:
		Mod(std::string name);
		bool operator==(Mod& othermod);

		const std::string& getName() const;

	protected:
		std::string m_name;
	};

}