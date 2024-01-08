project(external C CXX)

set(EXTERNAL_IDE_FOLDER "external")

### GLFW ###########################################################################################

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_library(ext::glfw ALIAS glfw)
set_target_properties(glfw PROPERTIES EXPORT_NAME ext::glfw)
set_target_properties(glfw PROPERTIES FOLDER ${EXTERNAL_IDE_FOLDER})

install(
    TARGETS glfw
    EXPORT glfwTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT shlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT glfwTargets
    FILE glfwConfig.cmake
    NAMESPACE glfw::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

### ImGui ##########################################################################################

if(NOT TARGET imgui)
    add_subdirectory(imgui EXCLUDE_FROM_ALL)
    add_library(ext::imgui ALIAS imgui)
    set_target_properties(imgui PROPERTIES EXPORT_NAME ext::imgui)  
    set_target_properties(imgui PROPERTIES FOLDER ${EXTERNAL_IDE_FOLDER})
endif()

### Glad ###########################################################################################

set(GLAD_HDR
    "glad/include/glad/gl.h"
    "glad/include/KHR/khrplatform.h"
)

set(GLAD_SRC
    "glad/src/gl.c"
)

add_library(glad STATIC ${GLAD_HDR} ${GLAD_SRC})

target_sources(glad
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_HDR}
)

target_include_directories(glad
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/glad/include>
)

add_library(ext::glad ALIAS glad)
set_target_properties(glad PROPERTIES EXPORT_NAME ext::glad)
set_target_properties(glad PROPERTIES FOLDER ${EXTERNAL_IDE_FOLDER})

install(
    TARGETS glad
    EXPORT gladTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT shlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT gladTargets
    FILE gladConfig.cmake
    NAMESPACE glad::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

### ImGui/GLFW/GL backend ##########################################################################

set(IMGUI_GLFW_GL_BACKEND_HDR
    "imgui/imgui/backends/imgui_impl_glfw.h"
    "imgui/imgui/backends/imgui_impl_opengl3.h"
)

set(IMGUI_GLFW_GL_BACKEND_SRC
    "imgui/imgui/backends/imgui_impl_glfw.cpp"
    "imgui/imgui/backends/imgui_impl_opengl3.cpp"
)

add_library(imgui_glfw_gl STATIC ${IMGUI_GLFW_GL_BACKEND_HDR} ${IMGUI_GLFW_GL_BACKEND_SRC})
target_link_libraries(imgui_glfw_gl PUBLIC imgui glfw glad)

target_include_directories(imgui_glfw_gl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/imgui/imgui/backends/>
)

add_library(ext::imgui_glfw_gl ALIAS imgui_glfw_gl)
set_target_properties(imgui_glfw_gl PROPERTIES EXPORT_NAME ext::imgui_glfw_gl)
set_target_properties(imgui_glfw_gl PROPERTIES FOLDER ${EXTERNAL_IDE_FOLDER})

install(
    TARGETS imgui_glfw_gl
    EXPORT imguiGLFWGLTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT shlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT imguiGLFWGLTargets
    FILE imguiGLFWGLTargetsConfig.cmake
    NAMESPACE imgui_glfw_gl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)