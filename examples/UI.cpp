#include "UI.hpp"
#include <GUI/RectCut.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

static void DarkTheme()
{
	ImGuiStyle & style = ImGui::GetStyle();

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_Border]                 = ImVec4(0.27f, 0.27f, 0.27f, 0.22f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(0.00f, 0.48f, 0.82f, 0.92f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(0.15f, 0.48f, 0.82f, 0.77f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.00f, 0.48f, 0.82f, 0.92f);
	colors[ImGuiCol_Button]                 = ImVec4(0.25f, 0.25f, 0.27f, 0.77f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(0.15f, 0.48f, 0.82f, 0.77f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(0.00f, 0.48f, 0.82f, 0.92f);
	colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(0.16f, 0.62f, 0.91f, 0.80f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_Separator]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_Tab]                    = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_TabHovered]             = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TabActive]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabUnfocused]           = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	//colors[ImGuiCol_DockingPreview]         = ImVec4(0.19f, 0.53f, 0.78f, 0.22f);
	//colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderLight]       = ImVec4(0.20f, 0.20f, 0.20f, 0.49f);
	colors[ImGuiCol_TableRowBg]             = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.19f, 0.53f, 0.78f, 1.00f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(0.00f, 0.44f, 0.88f, 1.00f);
	colors[ImGuiCol_NavHighlight]           = ImVec4(0.00f, 0.44f, 0.88f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	style.WindowRounding = 4.f;
	style.FrameRounding = 3.f;
	style.GrabRounding = 3.f;
	style.PopupRounding = 3.f;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void UIFunc();

int UIExample()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
	if (window == nullptr)
		return 1;
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	DarkTheme();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
#ifdef __EMSCRIPTEN__
	// For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
	// You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
	io.IniFilename = nullptr;
	EMSCRIPTEN_MAINLOOP_BEGIN
#else
	while (!glfwWindowShouldClose(window))
#endif
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UIFunc();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}
#ifdef __EMSCRIPTEN__
	EMSCRIPTEN_MAINLOOP_END;
#endif

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

ImVec2 GetPos(KimeraUI::Rect const & rect)
{
	return ImVec2(rect.minX, rect.minY);
}

ImVec2 GetSize(KimeraUI::Rect const & rect)
{
	return ImVec2(rect.maxX - rect.minX, rect.maxY - rect.minY);
}

ImVec2 GetWidgetMinPosFromRect(KimeraUI::Rect const & rect)
{
	return ImVec2(floorf(rect.minX), floorf(rect.minY));
}

ImVec2 GetWidgetMaxPosFromRect(KimeraUI::Rect const & rect)
{
	return ImVec2(floorf(rect.maxX), floorf(rect.maxY));
}

ImVec2 GetWidgetSizeFromRect(KimeraUI::Rect const & rect)
{
	return GetWidgetMaxPosFromRect(rect) - GetWidgetMinPosFromRect(rect);
}

KimeraUI::Rect GetRect(ImVec2 min, ImVec2 max)
{
	return { min.x, min.y, max.x, max.y };
}

void UIFunc()
{
	using namespace KimeraUI;

	ImGuiStyle & style = ImGui::GetStyle();
	style.FrameRounding = 0.f;

	const ImVec2 charTextSize = ImGui::CalcTextSize("A");

	{
		ImVec2 windowSize = ImVec2(180, charTextSize.y * 2.f + style.FramePadding.y);
		ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
		if(ImGui::Begin("RectCut - simple", 0, ImGuiWindowFlags_NoDecoration))
		{
			Rect layout = { 0, 0, windowSize.x, windowSize.y };

			const float cutW = charTextSize.x * 2.f + style.FramePadding.x;

			Rect r1 = CutLeft(&layout, cutW);
			Rect r2 = CutLeft(&layout, cutW);
			Rect r3 = CutLeft(&layout, cutW);

			Rect r4 = CutRight(&layout, cutW);
			Rect r5 = CutRight(&layout, cutW);

			const ImVec2 windowPos = ImGui::GetWindowPos();
			const ImVec2 cursorPos = ImGui::GetCursorPos();
			const ImVec2 basePos = windowPos + cursorPos - style.FramePadding * 2.f - ImVec2(1.f, 1.f);

			const auto ChildWindow = [&basePos](char const * label, Rect const & rect, auto uiFunc)
			{
				ImGui::SetNextWindowPos(basePos + GetPos(rect));
				if(ImGui::BeginChild(label, GetSize(rect), ImGuiChildFlags_Border))
				{
					uiFunc();
				}
				ImGui::EndChild();
			};

			ChildWindow("r1", r1, []() { ImGui::Text("1"); });
			ChildWindow("r2", r2, []() { ImGui::Text("2"); });
			ChildWindow("r3", r3, []() { ImGui::Text("3"); });
			ChildWindow("r4", r4, []() { ImGui::Text("4"); });
			ChildWindow("r5", r5, []() { ImGui::Text("5"); });
		}
		ImGui::End();
	}

	{
		ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);
		if(ImGui::Begin("RectCut", 0, ImGuiWindowFlags_NoScrollbar))//ImGuiWindowFlags_NoDecoration))
		{
			style.Colors[ImGuiCol_Border] = ImVec4(1, 0, 1, 1);

			const ImVec2 windowPos = ImGui::GetWindowPos();
			const ImVec2 contentRegionMin = ImGui::GetCursorPos();
			const ImVec2 contentRegionMax = ImGui::GetContentRegionMax() - style.FramePadding;
			const ImVec2 contentRegionSize = contentRegionMax - contentRegionMin;

			const ImVec2 contentRegionMinAbs = windowPos + contentRegionMin;
			const ImVec2 contentRegionMaxAbs = windowPos + contentRegionMax;
			
			ImGui::GetWindowDrawList()->AddRect(contentRegionMinAbs, contentRegionMaxAbs, 0xFF00FF00);

			const Rect windowArea = GetRect(contentRegionMinAbs, contentRegionMaxAbs);
			Rect windowAreaLayout = windowArea;

			const float topAreaHeight = floorf(contentRegionSize.y * 0.1f);
			const float bottomAreaHeight = topAreaHeight;

			const Rect topArea = CutTop(&windowAreaLayout, topAreaHeight);
			const Rect topAreaLayout = topArea;
			
			const Rect bottomArea = CutBottom(&windowAreaLayout, topAreaHeight);
			const Rect middleArea = windowAreaLayout;

			const float cutW = contentRegionSize.x * 0.1f; //charTextSize.x * 2.f + style.FramePadding.x;

			Rect topBar = topArea;
			Rect r1 = CutLeft(&topBar, cutW);
			Rect r2 = CutLeft(&topBar, cutW);
			Rect r3 = CutLeft(&topBar, cutW);
			Rect r4 = CutRight(&topBar, cutW);
			Rect r5 = CutRight(&topBar, cutW);

			const auto ChildWindow = [](char const * label, Rect const & rect, auto uiFunc)
			{
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
				ImGui::SetNextWindowPos(GetWidgetMinPosFromRect(rect));
				if(ImGui::BeginChild(label, GetWidgetSizeFromRect(rect), ImGuiChildFlags_Border))
				{
					uiFunc();
					const float w = rect.maxX - rect.minX;
					const float h = rect.maxY - rect.minY;
					ImGui::Text("%.1fx%.1f", w, h);
				}
				ImGui::EndChild();
				ImGui::PopStyleColor();
			};

			ChildWindow("Top", topArea, []() { ImGui::Text("Top"); });
			//ChildWindow("r1", r1, []() { ImGui::Text("1"); });
			ChildWindow("r2", r2, []() { ImGui::Text("2"); });
			ChildWindow("r3", r3, []() { ImGui::Text("3"); });
			ChildWindow("r4", r4, []() { ImGui::Text("4"); });
			ChildWindow("r5", r5, []() { ImGui::Text("5"); });
			ChildWindow("Bottom", bottomArea, []() { ImGui::Text("Bottom"); });
		}
		ImGui::End();
	}
}
