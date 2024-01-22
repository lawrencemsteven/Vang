#pragma once

#include "World.h"

namespace Vang::Voxel {

	struct PlayerData {
		worldID world{};
		glm::ivec3 position{};
	};

	class Universe {
	public:
		Universe();
		Universe(std::string seed);
		Universe(const Universe&)			 = delete;
		Universe(Universe&&)				 = delete;
		Universe& operator=(const Universe&) = delete;
		Universe& operator=(Universe&&)		 = delete;

		worldID createWorld();
		World& getWorld(worldID id);

	private:
		const std::string m_seed{};
		std::vector<World> m_worlds{};
		std::unordered_map<std::string, PlayerData> playerData{};
	};

}