#include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"

#include "Vang.h"

namespace Vang {

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst)
		: GraphicsAPI{vangInst} {
		initialize();
	}

	GraphicsOpenGL::GraphicsOpenGL(VangInst& vangInst, std::string_view applicationName)
		: GraphicsAPI{vangInst, applicationName} {
		initialize();
	}

	GraphicsOpenGL::~GraphicsOpenGL() { cleanup(); }

	void GraphicsOpenGL::beginFrame() {}

	void GraphicsOpenGL::initialize() { VANG_DEBUG("Initializing OpenGL"); }

	void GraphicsOpenGL::cleanup() { VANG_DEBUG("Closing OpenGL"); }

}
