set(Vang_Vang
    "./src/VangPCH.h"
    "./src/Vang.h"
    "./src/Vang.cpp"
)

set(Vang_UTILITY_LOGGING
    "./src/Vang/Utility/Logging/Log.h"
    "./src/Vang/Utility/Logging/Log.cpp"
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
    "./src/Vang/GraphicsAPI/GraphicsAPI.h"
    "./src/Vang/GraphicsAPI/GraphicsAPI.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSVULKAN
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.cpp"
)

set(Vang_GRAPHICSAPI_GRAPHICSOPENGL
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
    "./src/Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.cpp"
)

set(Vang_FILES
    ${Vang_Vang}
    ${Vang_UTILITY_LOGGING}
    ${Vang_WINDOW}
    ${Vang_WINDOW_WINDOWGLFW}
    ${Vang_GRAPHICSAPI}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN}
    ${Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS}
    ${Vang_GRAPHICSAPI_GRAPHICSOPENGL}
)