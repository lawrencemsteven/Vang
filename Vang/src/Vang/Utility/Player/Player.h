#pragma once

#include "Vang/Utility/Camera/Camera.h"

class VangInst;

namespace Vang {

	class Player {
	public:
		Player(VangInst& vangInst);
		~Player() = default;

		void moveForward(float amount);
		void moveRight(float amount);
		void moveUp(float amount);

		void setPosition(const glm::vec3& position);
		void setSpeed(float speed);

		Camera& getCamera();
		const Camera& getCamera() const;
		const glm::vec3& getPosition();
		float getSpeed();

	private:
		void updateCameraPosition();

		// TODO: Make this editable, maybe somewhere to set player size or height?
		VangInst& m_vangInst;
		const float cameraHeight = 1.8f;
		Camera m_camera;
		glm::vec3 m_position{0.0f};
		float m_speed{3.0f};
	};

}