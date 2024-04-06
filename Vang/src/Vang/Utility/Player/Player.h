#pragma once

#include "Vang/Utility/Camera/Camera.h"

namespace Vang::Objects {

	class Player {
	public:
		Player();
		~Player()						 = default;
		Player(const Player&)			 = delete;
		Player(Player&&)				 = delete;
		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&)		 = delete;

		void moveForward(float amount);
		void moveRight(float amount);
		void moveUp(float amount);

		void setPosition(const glm::vec3& position);
		void setSpeed(float speed);

		Camera& getCamera();
		const Camera& getCamera() const;
		const glm::vec3& getPosition() const;
		float getSpeed();

	private:
		void updateCameraPosition();

		// TODO: Make this editable, maybe somewhere to set player size or height?
		const float cameraHeight = 1.8f;
		Camera m_camera;
		glm::vec3 m_position{0.0f};
		float m_speed{3.0f};
	};

}