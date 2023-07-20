#include "Player.h"

#include "Vang.h"

namespace Vang {

	void Player::moveForward(float amount) {
		m_position += m_camera.getGroundedForward() * m_speed * amount;
	}

	void Player::moveRight(float amount) {
		m_position += m_camera.getGroundedRight() * m_speed * amount;
	}

	void Player::moveUp(float amount) {
		m_position += m_camera.getUp() * m_speed * amount;
	}

	void Player::setPosition(const glm::vec3& position) {
		m_position = position;
	}

	void Player::setSpeed(float speed) {
		m_speed = speed;
	}

	Camera& Player::getCamera() {
		return m_camera;
	}
	const Camera& Player::getCamera() const {
		return m_camera;
	}

	const glm::vec3& Player::getPosition() {
		return m_position;
	}

	float Player::getSpeed() {
		return m_speed;
	}

	void Player::updateCameraPosition() {
		m_camera.setPosition(m_position + m_camera.getUp() * cameraHeight);
		VangInst::Get().getGraphicsAPI().displayCamera(m_camera);
	}
}