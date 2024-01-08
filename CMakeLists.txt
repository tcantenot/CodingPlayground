cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(
    KimeraPlayground
    VERSION 0.1
    DESCRIPTION "Coding playground"
    LANGUAGES CXX
)

# Enable folder usage in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(external EXCLUDE_FROM_ALL)

add_subdirectory(src)
set_target_properties(kmr_gui     PROPERTIES FOLDER "libs/GUI")
set_target_properties(kmr_gui_dev PROPERTIES FOLDER "libs/GUI")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) #if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

    cmake_minimum_required(VERSION 3.18)
    option(KMR_PLAYGROUND_BUILD_EXAMPLES   "Whether or not examples should be built" ON)
    #option(KMR_PLAYGROUND_BUILD_TESTS      "Whether or not tests should be built" ON)
    #option(KMR_PLAYGROUND_BUILD_DOCS       "Whether or not docs should be built" OFF)
    option(KMR_PLAYGROUND_BUILD_PACKAGE    "Whether or not the package should be built" ON)
    option(KMR_PLAYGROUND_ENABLE_INSTALL   "Whether or not to enable the install rule" ON)

    if(KMR_PLAYGROUND_BUILD_PACKAGE)
        set(package_files include/ src/ cmake/ CMakeLists.txt LICENSE)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/kmr-playground-src.zip
            COMMAND ${CMAKE_COMMAND} -E tar c ${CMAKE_CURRENT_BINARY_DIR}/kmr-playground-src.zip --format=zip -- ${package_files}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${package_files})
        add_custom_target(kmr_playground_package DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/kmr-playground-src.zip)
        set_target_properties(kmr_playground_package PROPERTIES FOLDER "package")
    endif()

    if(KMR_PLAYGROUND_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    #if(KMR_PLAYGROUND_BUILD_TESTS)
    #    set(DOCTEST_NO_INSTALL ON)
    #    enable_testing()
    #    add_subdirectory(tests)
    #endif()

    #if(KMR_PLAYGROUND_BUILD_DOCS)
    #   add_subdirectory(docs EXCLUDE_FROM_ALL)
    #endif()

    if(KMR_PLAYGROUND_ENABLE_INSTALL)
        include(CMakePackageConfigHelpers)
        include(GNUInstallDirs)

        install(TARGETS kmr_all kmr_gui kmr_gui_dev _kmr_base
            EXPORT ${PROJECT_NAME}Targets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

        install(EXPORT ${PROJECT_NAME}Targets
            #NAMESPACE tcantenot::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        configure_package_config_file(
            cmake/${PROJECT_NAME}Config.cmake.in
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
        install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        # YYYY.MM.N1 is compatible with YYYY.MM.N2.
        write_basic_package_version_file(
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            COMPATIBILITY SameMinorVersion)

        install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

        install(DIRECTORY include/GUI
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING
            PATTERN "*.hpp|*inl")
    endif()
endif()