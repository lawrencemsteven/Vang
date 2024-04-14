#pragma once

#include "Vang/Utility/VMath/VMath.h"
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
		void setReachDistance(float reachDistance);

		Camera& getCamera();
		const Camera& getCamera() const;
		const glm::vec3& getPosition() const;
		float getSpeed();
		float getReachDistance() const;
		const Vang::VMath::raycastReturn& getRaycastResult() const;

	private:
		void updateCameraPosition();
		void updateRaycastReturn();

		// TODO: Make this editable, maybe somewhere to set player size or height?
		const float cameraHeight = 1.8f;
		float m_reachDistance{10.0f};
		Vang::VMath::raycastReturn m_raycastResult{};
		Camera m_camera;
		glm::vec3 m_position{0.0f};
		float m_speed{3.0f};
	};

}