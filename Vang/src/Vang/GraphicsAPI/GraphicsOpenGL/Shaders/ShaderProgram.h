#pragma once

#include "Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"
#include "Vang/GraphicsAPI/GraphicsOpenGL/Shaders/Shader.h"
#include "glm/glm.hpp"

namespace Vang::gfx::OpenGL {

	class ShaderProgram : public gfx::ShaderProgram {
	public:
		ShaderProgram()								   = default;
		~ShaderProgram()							   = default;
		ShaderProgram(const ShaderProgram&)			   = delete;
		ShaderProgram(ShaderProgram&&)				   = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&)	   = delete;

		void initialize();

		bool linkProgram() override;
		bool reloadShaders() override;

		bool attachShader(Shader shader);

		GLuint getID() const;

		void use();

		void setUniform(const std::string& name, glm::float32_t val1);
		void setUniform(const std::string& name, glm::float32_t val1, glm::float32_t val2);
		void setUniform(const std::string& name, glm::float32_t val1, glm::float32_t val2,
						glm::float32_t val3);
		void setUniform(const std::string& name, glm::float32_t val1, glm::float32_t val2,
						glm::float32_t val3, glm::float32_t val4);
		void setUniform(const std::string& name, glm::int32_t val1);
		void setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2);
		void setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2,
						glm::int32_t val3);
		void setUniform(const std::string& name, glm::int32_t val1, glm::int32_t val2,
						glm::int32_t val3, glm::int32_t val4);
		void setUniform(const std::string& name, const glm::ivec4& vals);
		void setUniform(const std::string& name, glm::uint32_t val1);
		void setUniform(const std::string& name, glm::uint32_t val1, glm::uint32_t val2);
		void setUniform(const std::string& name, glm::uint32_t val1, glm::uint32_t val2,
						glm::uint32_t val3);
		void setUniform(const std::string& name, glm::uint32_t val1, glm::uint32_t val2,
						glm::uint32_t val3, glm::uint32_t val4);
		void setUniform(const std::string& name, bool val1);

	private:
		void reinitialize();
		GLuint getVarLocation(const std::string& name);

		GLuint m_shaderProgram{};
		std::vector<Shader> m_attachedShaders;
		std::map<std::string, GLuint> m_uniformVariables;
	};

}