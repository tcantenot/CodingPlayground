# Submodules setup

Submodules setup when copying this repository for start a new project.

Open a command line terminal in this folder and run the following commands.

## Glad

Nothing to do. Auto-generated files: see `glad/README.md`.

## GLFW

```
git submodule add https://github.com/glfw/glfw.git glfw
```

## ImGui

```
git submodule add https://github.com/ocornut/imgui.git imgui/imgui
cd imgui/imgui
git checkout docking
cd ../..
```

And eventually change `IMGUI_VERSION` in `imgui/CMakeLists.txt` to the version in `imgui/imgui/imgui.h`.
