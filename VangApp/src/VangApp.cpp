// #include <iostream>
//
// #include <Vang.h>
//
// int main() {
//	VangInst& vangInst = VangInst::Get("VangApp");
//	bool running  = true;
//	while (running) {
//		vangInst.beginFrame();
//		vangInst.endFrame();
//		if (vangInst.getToClose()) running = false;
//	}
// }

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <ctime>

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

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
const char* computeShaderSource	 = R"(
	#version 460 core
	layout(local_size_x = 16, local_size_y = 8, local_size_z = 1) in;
	layout(rgba32f, binding = 0) uniform image2D screen;

	uniform ivec2 screen_size;
	uniform float iTime;

	#define MAX_STEPS 100
	#define MAX_DIST 100.0f
	#define SURF_DIST 0.01f

	float getDist(vec3 p) {
		vec4 sphere = vec4(0, 1, 6, 1);

		float sphere_dist = length(p - sphere.xyz) - sphere.w;
		float plane_dist = p.y;

		float dist = min(sphere_dist, plane_dist);
		return dist;
	}

	float rayMarch(vec3 ro, vec3 rd) {
		float dO = 0.0f;
		
		for (int i = 0; i < MAX_STEPS; i++) {
			vec3 p = ro + rd*dO;
			float dS = getDist(p);
			dO += dS;
			if (dO > MAX_DIST || dS < SURF_DIST) break;
		}

		return dO;
	}

	vec3 getNormal(vec3 p) {
		float d = getDist(p);
		vec2 e = vec2(0.01, 0);

		vec3 n = d - vec3(
			getDist(p-e.xyy),
			getDist(p-e.yxy),
			getDist(p-e.yyx));
		
		return normalize(n);
	}

	float getLight(vec3 p) {
		vec3 lightPosition = vec3(0, 5, 6);
		lightPosition.xz += vec2(sin(iTime), cos(iTime)) * 2.0f;
		vec3 l = normalize(lightPosition - p);
		vec3 n = getNormal(p);

		float dif = clamp(dot(n, l), 0.0f, 1.0f);
		float d = rayMarch(p+n*SURF_DIST*2, l);
		if (d < length(lightPosition - p)) dif *= 0.1f;
		return dif;
	}

	void main() {
		ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
		vec2 uv = (pixel_coords - 0.5*screen_size) / screen_size.y;

		vec3 col = vec3(0);

		vec3 ro = vec3(0,1,0);
		vec3 rd = normalize(vec3(uv.x, uv.y, 1));
		
		float d = rayMarch(ro, rd);

		vec3 p = ro + rd * d;
		float dif = getLight(p);
		col = vec3(dif);

		imageStore(screen, pixel_coords, vec4(col, 1.0f));
	}
)";

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
	unsigned int computeShader = glCreateShader(GL_COMPUTE_SHADER);
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

	int screen_size[2] = {SCR_WIDTH, SCR_HEIGHT};
	GLint myLoc		   = glGetUniformLocation(computeProgram, "screen_size");
	glProgramUniform2iv(computeProgram, myLoc, 1, screen_size);

	auto start_time	  = std::chrono::system_clock::now();
	auto current_time = std::chrono::system_clock::now();
	GLint myLoc2	  = glGetUniformLocation(computeProgram, "iTime");
	glProgramUniform1f(computeProgram, myLoc2,
					   std::chrono::duration<float>{current_time - start_time}.count());

	// uncomment this call to draw in wireframe polygons.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		current_time = std::chrono::system_clock::now();
		glProgramUniform1f(computeProgram, myLoc2,
						   std::chrono::duration<float>{current_time - start_time}.count());
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
		glfwSwapBuffers(window);
		glfwPollEvents();
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