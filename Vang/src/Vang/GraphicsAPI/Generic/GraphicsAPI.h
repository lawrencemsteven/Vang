#pragma once

#include "Vang/Utility/Camera/Camera.h"

namespace Vang::gfx {

	class GraphicsAPI {
	public:
		GraphicsAPI()							   = default;
		GraphicsAPI(const GraphicsAPI&)			   = delete;
		GraphicsAPI(GraphicsAPI&&)				   = delete;
		GraphicsAPI& operator=(const GraphicsAPI&) = delete;
		GraphicsAPI& operator=(GraphicsAPI&&)	   = delete;

		virtual double getRenderTextureScale() const = 0;

		virtual void setRenderTextureScale(const double renderTextureScale) = 0;

		virtual void initialize();
		virtual void initialize(std::string_view applicationName);
		virtual void update()	 = 0;
		virtual void endUpdate() = 0;

		std::string_view getApplicationName();

		virtual void windowResize(uint32_t width, uint32_t height) = 0;
		virtual void resizeRenderTexture()						   = 0;

		virtual void displayCamera(const Vang::Objects::Camera& camera) = 0;

	protected:
		std::string_view m_applicationName;
	};

}
