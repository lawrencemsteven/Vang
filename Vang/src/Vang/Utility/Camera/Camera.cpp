#include "Camera.h"
#include "Vang.h"

#include <glm/gtx/transform.hpp>

namespace Vang::Objects {

	void Camera::setPosition(const glm::vec3& position) {
		m_position = position;
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::setFOV(float fov) {
		m_fov = fov;
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::setLookSensitivity(float lookSensitivity) {
		m_lookSensitivity = lookSensitivity;
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::rotateRight(float x_offset) {
		m_yaw -= x_offset;
		recalculateForward();
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::rotateUp(float y_offset) {
		m_pitch += y_offset;
		m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
		recalculateForward();
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::mouseRotate(double x_pos, double y_pos) {
		// Logic may need to be changed. This is when the user clicks back into the window
		if (!m_lastX.has_value() || !m_lastY.has_value()) {
			m_lastX = x_pos;
			m_lastY = y_pos;
			return;
		}

		float x_offset = x_pos - m_lastX.value();
		float y_offset = y_pos - m_lastY.value();
		m_lastX		   = x_pos;
		m_lastY		   = y_pos;

		x_offset *= m_lookSensitivity;
		y_offset *= m_lookSensitivity;

		rotateRight(x_offset);
		rotateUp(y_offset);
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	void Camera::lookAt(const glm::vec3& look_at) {
		VANG_ERROR("Camera::lookAt has not been implemented yet!");
		// This can most likely be done with glm::lookat function, just needs to be implemented and
		// tested.
		Vang::getGraphicsAPI().displayCamera(*this);
	}

	glm::vec3 Camera::getPosition() const {
		return m_position;
	}

	glm::vec3 Camera::getForward() const {
		return m_forward;
	}

	glm::vec3 Camera::getGroundedForward() const {
		// TODO: This should also take into account the current Universe's up vector and not be hard
		// coded to 1 on x and z.
		return glm::normalize(m_forward * glm::vec3{1.0f, 0.0f, 1.0f});
	}

	glm::vec3 Camera::getGroundedRight() const {
		// TODO: This should be the world up vector and NOT the camera up vector. Since the camera
		// does not currently support any other directions for the up vector this will work for now.
		return -glm::normalize(glm::cross(getGroundedForward(), m_up));
	}

	glm::vec3 Camera::getUp() const {
		return m_up;
	}

	glm::vec3 Camera::getRight() const {
		return glm::cross(m_up, m_forward);
	}

	float Camera::getFOV() const {
		return m_fov;
	}

	float Camera::getLookSensitivity() const {
		return m_lookSensitivity;
	}

	const glm::mat4 Camera::getView() const {
		return glm::lookAt(m_position, m_position - m_forward, m_up);
	}

	void Camera::recalculateForward() {
		m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward.y = sin(glm::radians(m_pitch));
		m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	}
}