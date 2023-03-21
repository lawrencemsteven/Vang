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
)

set(Vang_GRAPHICSAPI_GRAPHICS_VULKAN
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
    "./src/Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.cpp"
)

set(Vang_FILES
    ${Vang_Vang}
    ${Vang_UTILITY_LOGGING}
    ${Vang_WINDOW}
    ${Vang_WINDOW_WINDOWGLFW}
    ${Vang_GRAPHICSAPI}
    ${Vang_GRAPHICSAPI_GRAPHICS_VULKAN}
)