#include "Shader.h"

namespace Vang::gfx {

	Shader::Shader(std::filesystem::path path, ShaderType type)
		: m_path{path},
		  m_type{type} {
		loadAndCompile();
	}

}
