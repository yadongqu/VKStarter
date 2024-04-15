cmake_minimum_required(VERSION 3.20)

project(flow)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE GLSL_SOURCE_FILES "shaders/*.glsl")
file(GLOB_RECURSE CPP_SOURCE_FILES "src/*.cpp")

add_executable(flow ${CPP_SOURCE_FILES})

if(WIN32)
    target_compile_definitions(flow PRIVATE VK_USE_PLATFORM_WIN32_KHR GLFW_EXPOSE_NATIVE_WIN32)
    target_compile_definitions(flow PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/vk-bootstrap)

target_link_libraries(flow PRIVATE glfw glm::glm vk-bootstrap::vk-bootstrap)

set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")

set(SPIRV_OUTPUT_DIR "${PROJECT_BINARY_DIR}/shaders/")

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(STEM ${GLSL} NAME_WLE)
    set(SPIRV "${SPIRV_OUTPUT_DIR}${STEM}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
        COMMAND ${GLSL_VALIDATOR} -V --target-env vulkan1.3 --quiet ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL} ${GLSL_HEADER_FILES})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

add_custom_target(compile_shaders DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(flow compile_shaders)