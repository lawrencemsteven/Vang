#pragma once

#include "World.h"

namespace Vang {

	class Universe {
	public:
		Universe();
		Universe(std::string seed);

	private:
		const std::string m_seed;
		std::vector<World> m_worlds;
	};

}