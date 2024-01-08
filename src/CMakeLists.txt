# Based on https://github.com/foonathan/lexy/blob/main/src/CMakeLists.txt

get_filename_component(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/../include ABSOLUTE)
get_filename_component(src_dir ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)

set(hdr_files_gui
    ${include_dir}/GUI/RectCut.hpp
)

set(src_files_gui
    ${src_dir}/GUI/RectCut.cpp
)

set(kmr_gui_hdr_files ${hdr_files_gui} PARENT_SCOPE)

# Add headers to build and install interface for header-only libs
# https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
#   "The PRIVATE and PUBLIC keywords specify where those corresponding sources should be used.
#    PRIVATE simply means those sources should only be added to myLib, whereas PUBLIC means those
#    sources should be added to myLib and to any target that links to myLib. An INTERFACE keyword
#    can be used for sources that should not be added to myLib but should be added to anything that
#    links to myLib. In practice, sources will almost always be PRIVATE, since they shouldn’t generally
#    be added to anything that links against the target. Header-only interface libraries are one
#    exception because sources can only be added as INTERFACE for interface libraries."
function(target_sources_interface target base_include_dir)
    foreach(src ${ARGN})
        if(NOT src STREQUAL "PRIVATE" AND NOT src STREQUAL "PUBLIC" AND NOT src STREQUAL "INTERFACE")
            string(REGEX MATCH "${base_include_dir}/(.*)" _ ${src}) 
            list(APPEND _source_list "$<BUILD_INTERFACE:${src}>")
            list(APPEND _source_list "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_MATCH_1}>")
        endif()
    endforeach()
    target_sources(${target} INTERFACE ${_source_list})
endfunction()

# Function to add a alias to a target and export it
function(add_alias name target)
    #add_library(tcantenot::${name} ALIAS ${target})
    add_library(${name} ALIAS ${target})
    set_target_properties(${target} PROPERTIES EXPORT_NAME ${name})
endfunction()

function(add_dev_target_compile_options target)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        if("${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
            target_compile_options(${target} PUBLIC /WX /W3 /D _CRT_SECURE_NO_WARNINGS)
        else()
            target_compile_options(${target} PUBLIC -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
        endif()
        # clang doesn't like operator precedence rules we're using for the DSL.
        target_compile_options(${target} PUBLIC -Wno-shift-op-parentheses -Wno-parentheses-equality)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(${target} PUBLIC -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
        # GCC doesn't like the operator precedence rules we're using for the DSL.
        target_compile_options(${target} PUBLIC -Wno-parentheses)
        # GCC doesn't properly detect when local typedefs escape via the return type.
        target_compile_options(${target} PUBLIC -Wno-unused-local-typedefs)
        # GCC's arry bounds, maybe uninitialized, and restrict warning seems to have false positives.
        target_compile_options(${target} PUBLIC -Wno-array-bounds -Wno-maybe-uninitialized -Wno-restrict)
    elseif(MSVC)
        target_compile_options(${target} PUBLIC /WX /W3 /D _CRT_SECURE_NO_WARNINGS /wd5105)

    # Edit and continue
    # https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#edit-and-continue-for-cmake-projects
    if(MSVC)
        target_compile_options(${target} PUBLIC "/ZI")
        target_link_options(${target} PUBLIC "/INCREMENTAL")
    endif()
endif()
endfunction()


include(GNUInstallDirs)

# Base target for common options
add_library(_kmr_base INTERFACE)
#target_sources(_kmr_base INTERFACE ${hdr_files_core}) # Error: Target "_kmr_base" INTERFACE_SOURCES property contains path: "XXX"  which is prefixed in the source directory.
#target_sources_interface(_kmr_base ${include_dir} ${hdr_files_core})

if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    target_compile_features(_kmr_base INTERFACE cxx_std_20)
else()
    target_compile_features(_kmr_base INTERFACE cxx_std_17)
endif()

# GUI library
add_library(kmr_gui STATIC ${hdr_files_gui} ${src_files_gui})
add_alias(kmr::gui kmr_gui)
set_target_properties(kmr_gui PROPERTIES LINKER_LANGUAGE CXX)
#target_sources(kmr_gui PUBLIC ${hdr_files_gui})
target_include_directories(kmr_gui PUBLIC
    $<BUILD_INTERFACE:${include_dir}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(kmr_gui PUBLIC _kmr_base ext::imgui)

# GUI library with warnings; for development only.
add_library(kmr_gui_dev STATIC ${hdr_files_gui} ${src_files_gui})
add_alias(kmr::gui_dev kmr_gui_dev)
set_target_properties(kmr_gui_dev PROPERTIES LINKER_LANGUAGE CXX)
#target_sources(kmr_gui_dev PUBLIC ${hdr_files_gui})
target_include_directories(kmr_gui_dev PUBLIC
    $<BUILD_INTERFACE:${include_dir}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(kmr_gui_dev PUBLIC _kmr_base ext::imgui)

# Unbrella target with all components
add_library(kmr_all INTERFACE)
add_alias(kmr::all kmr_all)
target_link_libraries(kmr_all INTERFACE kmr::gui)

# Unbrella dev target with all components
add_library(kmr_all_dev INTERFACE)
add_alias(kmr::all_dev kmr_all_dev)
target_link_libraries(kmr_all_dev INTERFACE kmr::gui_dev)
