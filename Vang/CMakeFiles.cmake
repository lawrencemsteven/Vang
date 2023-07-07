set(Vang_Vang
    "./src/VangPCH.h"
    "./src/Vang.h"
    "./src/Vang.cpp"
)

set(Vang_UTILITY_CAMERA
    "./src/Vang/Utility/Camera/Camera.h"
    "./src/Vang/Utility/Camera/Camera.cpp"
)

set(Vang_UTILITY_LOGGING
    "./src/Vang/Utility/Logging/Log.h"
    "./src/Vang/Utility/Logging/Log.cpp"
)

set(Vang_UTILITY_PLAYER
    "./src/Vang/Utility/Player/Player.h"
    "./src/Vang/Utility/Player/Player.cpp"
)

set(Vang_WINDOW
    "./src/Vang/Window/Window.h"
    "./src/Vang/Window/Window.cpp"
)

set(Vang_WINDOW_WINDOWGLFW
    "./src/Vang/Window/WindowGLFW/WindowGLFW.h"
    "./src/Vang/Window/WindowGLFW/WindowGLFW.cpp"
)

set(Vang_GRAPHICSAPI
    "./src/Vang/GraphicsAPI/Generic/GraphicsAPI.h"
    "./src/Vang/GraphicsAPI/Generic/GraphicsAPI.cpp"
)

set(Vang_GRAPHICSAPI_SHADER
    "./src/Vang/GraphicsAPI/Generic/Shader/Shader.h"
    "./src/Vang/GraphicsAPI/Generic/Shader/Shader.cpp"
)

set(Vang_GRAPHICSAPI_SHADERPROGRAM
    "./src/Vang/GraphicsAPI/Generic/ShaderProgram/ShaderProgram.h"
    "./src/Vang/GraphicsAPI/Generic/ShaderProgram/ShaderProgram.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSVULKAN
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.cpp"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanSurface.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanSurface.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSOPENGL
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSOPENGL_SHADER
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shader/Shader.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shader/Shader.cpp"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shader/ShaderProgram.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shader/ShaderProgram.cpp"
)

set(Vang_FILES
    ${Vang_Vang}
    ${Vang_UTILITY_CAMERA}
    ${Vang_UTILITY_LOGGING}
    ${Vang_UTILITY_PLAYER}
    ${Vang_WINDOW}
    ${Vang_WINDOW_WINDOWGLFW}
    ${Vang_GRAPHICSAPI}
    ${Vang_GRAPHICSAPI_SHADER}
    ${Vang_GRAPHICSAPI_SHADERPROGRAM}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS}
    ${Vang_GRAPHICSAPI_GRAPHICSOPENGL}
    ${Vang_GRAPHICSAPI_GRAPHICSOPENGL_SHADER}
)