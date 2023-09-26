#include "Time.h"

namespace Vang::Utility::Time {

	const static auto start_time = std::chrono::system_clock::now();

	static auto previous_frame_time = std::chrono::system_clock::now();
	static auto current_frame_time = std::chrono::system_clock::now();

	float timeSinceStart() {
		return std::chrono::duration<float>{std::chrono::system_clock::now() - start_time}
			.count();
	}

	float deltaTime() {
		return std::chrono::duration<float>{current_frame_time - previous_frame_time}
			.count();
	}

	void updateDeltaTime() {
		previous_frame_time = current_frame_time;
		current_frame_time	= std::chrono::system_clock::now();
	}

}