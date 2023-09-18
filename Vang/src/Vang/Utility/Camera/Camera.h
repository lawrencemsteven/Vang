#pragma once

#include <glm/glm.hpp>

namespace Vang::Objects {

	class Camera {
	public:
		Camera()  = default;
		~Camera() = default;

		void setPosition(const glm::vec3& position);
		void setFOV(float fov);
		void setLookSensitivity(float lookSensitivity);

		void rotateRight(float x_offset);
		void rotateUp(float y_offset);
		void mouseRotate(double x_pos, double y_pos);
		void lookAt(const glm::vec3& look_at);

		glm::vec3 getPosition() const;
		glm::vec3 getForward() const;
		glm::vec3 getGroundedForward() const;
		glm::vec3 getGroundedRight() const;
		glm::vec3 getUp() const;
		glm::vec3 getRight() const;
		float getFOV() const;
		float getLookSensitivity() const;
		const glm::mat4 getView() const;

	private:
		void recalculateForward();

		glm::vec3 m_position{0.0f, 1.0f, 0.0f};
		glm::vec3 m_forward{0.0f, 0.0f, 1.0f};
		glm::vec3 m_up{0.0f, 1.0f, 0.0f};
		float m_pitch{0.0f};
		float m_yaw{90.0f};
		float m_lookSensitivity{0.075f};
		float m_fov{90.0f};
		std::optional<float> m_lastX;
		std::optional<float> m_lastY;
	};

}