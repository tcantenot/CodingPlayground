cmake_minimum_required(VERSION 3.13)
project(imgui CXX)

include (GNUInstallDirs)

set(IMGUI_VERSION 1.90.1)

set(IMGUI_HDR
    "imgui/imconfig.h"
    "imgui/imgui.h"
    "imgui/imgui_internal.h"
)

set(IMGUI_SRC
    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
)

add_library(imgui STATIC ${IMGUI_HDR} ${IMGUI_SRC})
target_include_directories(imgui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/imgui>
)

set_target_properties(imgui PROPERTIES PUBLIC_HEADER ${IMGUI_HDR})
set_target_properties(imgui PROPERTIES VERSION   ${IMGUI_VERSION})
set_target_properties(imgui PROPERTIES SOVERSION ${IMGUI_VERSION})

install(
    TARGETS imgui
    EXPORT imguiTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT shlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT imguiTargets
    FILE imguiConfig.cmake
    NAMESPACE imgui::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)