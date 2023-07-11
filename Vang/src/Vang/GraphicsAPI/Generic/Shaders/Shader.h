#pragma once

namespace Vang::gfx {

	enum class ShaderType {
		Vertex,
		Fragment,
		Compute,
	};

	class Shader {
	public:
		Shader()						 = delete;
		~Shader()						 = default;
		Shader(const Shader&)			 = delete;
		Shader(Shader&&)				 = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&)		 = delete;

		Shader(std::filesystem::path path, ShaderType type);

		virtual std::optional<void> reload() = 0;

		virtual std::optional<int> getID() = 0;

	protected:
		virtual std::optional<void> loadAndCompile() = 0;

		std::filesystem::path m_path{};
		ShaderType m_type;
	};

}