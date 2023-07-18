set(Vang_Vang
    "./src/VangPCH.h"
    "./src/Vang.h"
    "./src/Vang.cpp"
)

set(Vang_UTILITY_CAMERA
    "./src/Vang/Utility/Camera/Camera.h"
    "./src/Vang/Utility/Camera/Camera.cpp"
)

set(Vang_UTILITY_FILEIO
    "./src/Vang/Utility/FileIO/FileIO.h"
    "./src/Vang/Utility/FileIO/FileIO.cpp"
)

set(Vang_UTILITY_INPUT
    "./src/Vang/Utility/Input/Input.h"
    "./src/Vang/Utility/Input/Input.cpp"
)

set(Vang_UTILITY_LOGGING
    "./src/Vang/Utility/Logging/Log.h"
    "./src/Vang/Utility/Logging/Log.cpp"
)

set(Vang_UTILITY_PLAYER
    "./src/Vang/Utility/Player/Player.h"
    "./src/Vang/Utility/Player/Player.cpp"
)

set(Vang_UTILITY_TIME
    "./src/Vang/Utility/Time/Time.h"
    "./src/Vang/Utility/Time/Time.cpp"
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

set(Vang_GRAPHICSAPI_SHADERS
    "./src/Vang/GraphicsAPI/Generic/Shaders/ShaderProgram.h"
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

set(Vang_GRAPHICSAPI_GRAPHICSOPENGL_SHADERS
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/Shader.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/Shader.cpp"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgram.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgram.cpp"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgramManager.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderProgramManager.cpp"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderTexture.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/ShaderTexture.cpp"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/VertexData.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/Shaders/VertexData.cpp"
)

set(Vang_FILES
    ${Vang_Vang}
    ${Vang_UTILITY_CAMERA}
    ${Vang_UTILITY_FILEIO}
    ${Vang_UTILITY_INPUT}
    ${Vang_UTILITY_LOGGING}
    ${Vang_UTILITY_PLAYER}
    ${Vang_UTILITY_TIME}
    ${Vang_WINDOW}
    ${Vang_WINDOW_WINDOWGLFW}
    ${Vang_GRAPHICSAPI}
    ${Vang_GRAPHICSAPI_SHADERS}
    ${Vang_GRAPHICSAPI_SHADERPROGRAM}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS}
    ${Vang_GRAPHICSAPI_GRAPHICSOPENGL}
    ${Vang_GRAPHICSAPI_GRAPHICSOPENGL_SHADERS}
)