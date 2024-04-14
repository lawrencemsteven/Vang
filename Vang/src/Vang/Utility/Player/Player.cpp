#include "Player.h"

#include "Vang.h"

namespace Vang::Objects {

	Player::Player() {
		updateCameraPosition();
	}

	void Player::moveForward(float amount) {
		m_position += m_camera.getGroundedForward() * m_speed * amount;
		updateCameraPosition();
	}

	void Player::moveRight(float amount) {
		m_position += m_camera.getGroundedRight() * m_speed * amount;
		updateCameraPosition();
	}

	void Player::moveUp(float amount) {
		m_position += m_camera.getUp() * m_speed * amount;
		updateCameraPosition();
	}

	void Player::setPosition(const glm::vec3& position) {
		m_position = position;
		updateCameraPosition();
	}

	void Player::setSpeed(float speed) {
		m_speed = speed;
	}

	void Player::setReachDistance(float reachDistance) {
		m_reachDistance = reachDistance;
		updateRaycastReturn();
	}

	Camera& Player::getCamera() {
		updateRaycastReturn();
		return m_camera;
	}

	const Camera& Player::getCamera() const {
		return m_camera;
	}

	const glm::vec3& Player::getPosition() const {
		return m_position;
	}

	float Player::getSpeed() {
		return m_speed;
	}

	float Player::getReachDistance() const {
		return m_reachDistance;
	}

	const Vang::VMath::raycastReturn& Player::getRaycastResult() const {
		return m_raycastResult;
	}

	void Player::updateCameraPosition() {
		m_camera.setPosition(m_position + m_camera.getUp() * cameraHeight);
		Vang::getGraphicsAPI().displayCamera(m_camera);
		updateRaycastReturn();
	}

	void Player::updateRaycastReturn() {
		// TODO: Replace with player's current world
		auto& world = Vang::getCurrentWorld();

		m_raycastResult = Vang::VMath::raycast(world, m_camera.getPosition(), m_camera.getForward(),
											   m_reachDistance);
	}
}