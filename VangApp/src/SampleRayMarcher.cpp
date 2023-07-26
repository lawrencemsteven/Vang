#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <ctime>

#include "Vang/Utility/FileIO/FileIO.h"

// settings
const unsigned int SCR_WIDTH  = 1280;
const unsigned int SCR_HEIGHT = 720;

const std::string_view COMPUTE_SHADER_SOURCE = "../../../Vang/shaders/voxelRayMarcher.glsl";
//const std::string_view COMPUTE_SHADER_SOURCE = "../../../Vang/shaders/2dSceneTest.glsl";

class World {
public:
	World()	 = default;
	~World() = default;

	glm::vec3 getUp() { return up; };

	void setUp(glm::vec3 up) { this->up = up; }

private:
	glm::vec3 up{0.0f, 1.0f, 0.0f};
};

class Camera {
public:
	Camera()  = default;
	~Camera() = default;

	void setPosition(glm::vec3 position) { this->position = position; }
	void setFOV(float fov) { this->fov = fov; }
	void setForward(glm::vec3 forward) { this->forward = glm::normalize(forward); }
	void setup(glm::vec3 up) { this->up = glm::normalize(up); }

	void rotateRight(float x_offset) {
		yaw -= x_offset;
		recalculateForward();
	}
	void rotateUp(float y_offset) {
		pitch += y_offset;
		pitch = std::clamp(pitch, -89.0f, 89.0f);
		recalculateForward();
	}
	void newMousePos(double xpos, double ypos) {
		float xOffset = xpos - lastX;
		float yOffset = ypos - lastY;
		lastX		  = xpos;
		lastY		  = ypos;

		xOffset *= look_speed;
		yOffset *= look_speed;

		rotateRight(xOffset);
		rotateUp(-yOffset);
	}

	glm::vec3 getPosition() { return position; }
	glm::vec3 getForward() { return forward; }
	glm::vec3 getGroundedForward() {
		return glm::normalize(getForward() * glm::vec3{1.0f, 0.0f, 1.0f});
	}
	glm::vec3 getUp() { return up; }
	glm::vec3 getRight() { return glm::cross(up, forward); }
	float getFOV() { return fov; }
	float getMoveSpeed() { return move_speed; }
	float getLookSpeed() { return look_speed; }
	glm::mat4 getView() { return glm::lookAt(position, position - forward, up); }

private:
	void recalculateForward() {
		forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward.y = sin(glm::radians(pitch));
		forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	}

	glm::vec3 position{0.0f};
	glm::vec3 forward{0.0f, 0.0f, 1.0f};
	glm::vec3 up{0.0f, 1.0f, 0.0f};
	float pitch{0.0f};
	float yaw{90.0f};
	float move_speed{3.0f};
	float look_speed{0.075f};
	float fov{90};
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
};

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	camera->newMousePos(xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

const char* vertexShaderSource	 = R"(
	#version 460 core

	layout (location = 0) in vec2 a_Pos;
	layout (location = 1) in vec2 a_UV;

	out vec2 v_UV;

	void main() {
		gl_Position = vec4(a_Pos.x, a_Pos.y, 0.0, 1.0);
		v_UV = a_UV;
	}
)";
const char* fragmentShaderSource = R"(
	#version 460 core

	out vec4 FragColor;

	uniform sampler2D screen;
	in vec2 v_UV;

	void main()
	{
		FragColor = texture(screen, v_UV);
	}
)";

void initializeUniforms(unsigned int program) {
	int screen_size[2] = {SCR_WIDTH, SCR_HEIGHT};
	GLint myLoc		   = glGetUniformLocation(program, "iResolution");
	glProgramUniform2iv(program, myLoc, 1, screen_size);
}

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

	// glfw window creation
	// --------------------
	GLFWwindow* window =
		glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Super Cool Ray Tracer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}




	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// clang-format off
	float vertices[5 * 4] = {
		-1.0f,  1.0f, 0.0f, 1.0f,	// Top Left
		 1.0f,	1.0f, 1.0f, 1.0f,	// Top Right
		-1.0f, -1.0f, 0.0f, 0.0f,	// Bottom Left
		 1.0f, -1.0f, 1.0f, 0.0f,	// Bottom Right
	};
	// clang-format on

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure
	// vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
	// attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but
	// this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways so we
	// generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// compute shader
	unsigned int computeShader			  = glCreateShader(GL_COMPUTE_SHADER);
	std::string computeShaderSourceString = Vang::FileIO::readFile(COMPUTE_SHADER_SOURCE).value();
	const char* computeShaderSource		  = computeShaderSourceString.c_str();
	glShaderSource(computeShader, 1, &computeShaderSource, 0);
	glCompileShader(computeShader);
	// check for shader compile errors
	glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link compute shader
	unsigned int computeProgram = glCreateProgram();
	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);
	glGetProgramiv(computeProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(computeProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteShader(computeShader);

	// create texture
	unsigned int m_texture0;
	glGenTextures(1, &m_texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glBindImageTexture(0, m_texture0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	initializeUniforms(computeProgram);
	auto start_time	  = std::chrono::system_clock::now();
	auto current_time = std::chrono::system_clock::now();

	World world{};

	Camera camera{};
	camera.setPosition({0.0f, 1.0f, 0.0f});
	camera.setFOV(90);

	glfwSetWindowUserPointer(window, &camera);
	glfwSetCursorPosCallback(window, mouseCallback);

	// render loop
	// -----------
	bool e_key_pressed = false;
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);
		glfwPollEvents();

		// render
		// ------
		// Update Time
		float delta_time =
			std::chrono::duration<float>{std::chrono::system_clock::now() - current_time}.count();
		current_time = std::chrono::system_clock::now();

		// Get New Camera Position
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camera.setPosition(camera.getPosition() +
							   camera.getGroundedForward() * camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			camera.setPosition(camera.getPosition() +
							   glm::cross(camera.getGroundedForward(), world.getUp()) *
								   camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camera.setPosition(camera.getPosition() +
							   -camera.getGroundedForward() * camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camera.setPosition(camera.getPosition() +
							   glm::cross(world.getUp(), camera.getGroundedForward()) *
								   camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			camera.setPosition(camera.getPosition() +
							   world.getUp() * camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
			camera.setPosition(camera.getPosition() +
							   -world.getUp() * camera.getMoveSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			camera.rotateRight(camera.getLookSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			camera.rotateRight(-camera.getLookSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			camera.rotateUp(camera.getLookSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			camera.rotateUp(-camera.getLookSpeed() * delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) { break; }

		if (glfwGetKey(window, GLFW_KEY_E)) {
			if (!e_key_pressed) {
				computeShader = glCreateShader(GL_COMPUTE_SHADER);
				std::string computeShaderSourceString =
					Vang::FileIO::readFile(COMPUTE_SHADER_SOURCE).value();
				computeShaderSource = computeShaderSourceString.c_str();
				glShaderSource(computeShader, 1, &computeShaderSource, 0);
				glCompileShader(computeShader);
				// check for shader compile errors
				glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n"
							  << infoLog << std::endl;
				}
				computeProgram = glCreateProgram();
				glAttachShader(computeProgram, computeShader);
				glLinkProgram(computeProgram);
				glGetProgramiv(computeProgram, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(computeProgram, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				}
				glDeleteShader(computeShader);
				initializeUniforms(computeProgram);
			}
			e_key_pressed = true;
		}
		else { e_key_pressed = false; }

		glm::mat4 view = camera.getView();

		GLint myLoc2 = glGetUniformLocation(computeProgram, "iTime");
		GLint myLoc3 = glGetUniformLocation(computeProgram, "camera.position");
		GLint myLoc4 = glGetUniformLocation(computeProgram, "camera.forward");
		GLint myLoc5 = glGetUniformLocation(computeProgram, "camera.up");
		GLint myLoc6 = glGetUniformLocation(computeProgram, "camera.right");
		GLint myLoc7 = glGetUniformLocation(computeProgram, "camera.fov");
		glProgramUniform1f(computeProgram, myLoc2,
						   std::chrono::duration<float>{current_time - start_time}.count());
		glProgramUniform3f(computeProgram, myLoc3, camera.getPosition().x, camera.getPosition().y,
						   camera.getPosition().z);
		glProgramUniform3f(computeProgram, myLoc4, view[0][2], view[1][2], view[2][2]);
		glProgramUniform3f(computeProgram, myLoc5, view[0][1], view[1][1], view[2][1]);
		glProgramUniform3f(computeProgram, myLoc6, view[0][0], view[1][0], view[2][0]);
		glProgramUniform1f(computeProgram, myLoc7, camera.getFOV());
		glUseProgram(computeProgram);
		glDispatchCompute(floor(SCR_WIDTH / 16), floor(SCR_HEIGHT / 8), 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it
								// every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glFlush();
		glfwSwapBuffers(window);
		// glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}