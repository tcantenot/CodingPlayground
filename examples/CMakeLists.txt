add_executable(kmr_tests)
set_target_properties(kmr_tests PROPERTIES OUTPUT_NAME kmr_tests)
target_sources(kmr_tests
	PRIVATE
		main.cpp
		StackAllocator.hpp
		StackAllocator.cpp
		UI.cpp
		UI.hpp
)
target_link_libraries(kmr_tests
	PRIVATE
		#kmr::gui
		kmr::gui_dev
		ext::imgui_glfw_gl
)

# Edit and continue
# https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#edit-and-continue-for-cmake-projects
if(MSVC)
	target_compile_options(kmr_tests PUBLIC "/ZI")
	target_link_options(kmr_tests PUBLIC "/INCREMENTAL")
endif()

set_target_properties(kmr_tests PROPERTIES FOLDER "examples")