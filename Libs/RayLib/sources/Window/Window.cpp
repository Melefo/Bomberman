/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Window
*/

#include "Window.hpp"
#include <iostream>

namespace RayLib
{

    std::unique_ptr<Window> Window::_window = nullptr;

    Window::Window(Vector2<int> size, const std::string& title) : _fullscreen(false)
    {
        ::InitWindow(size.x, size.y, title.c_str());
        //if (IsWindowReady() == false)
            // !! throw error
    }

    std::unique_ptr<Window>& Window::GetInstance(Vector2<int> size, const std::string& title)
    {
        if (_window == nullptr) {
            _window = std::make_unique<Window>(size, title);
        }
        return (_window);
    }

    Window::~Window()
    {
        if (IsWindowReady()) {
            CloseWindow();
        }
    }

    void Window::BeginDrawing()
    {
        ::BeginDrawing();
    }

    void Window::EndDrawing()
    {
        ::EndDrawing();
    }

    void Window::DrawCube(Vector3 position, Vector3 scale, Color color)
    {
        ::DrawCube(position.getVector3(), scale.x, scale.y, scale.z, color.getColor());
    }

    void Window::DrawCubeWires(Vector3 position, Vector3 scale, Color color)
    {
        ::DrawCubeWires(position.getVector3(), scale.x, scale.y, scale.z, color.getColor());
    }

    void Window::DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color)
    {
        ::DrawSphereWires(centerPos.getVector3(), radius, rings, slices, color.getColor());
    }


    void Window::DrawBoundingBox(BoundingBox box, Color color)
    {
        ::DrawBoundingBox(box.GetBounds(), color.getColor());
    }

    void Window::DrawGrid(int slices, float spacing)
    {
        ::DrawGrid(slices, spacing);
    }

    void Window::ClearBackground(Color color)
    {
        ::ClearBackground(color.getColor());
    }

    void Window::SetTargetFPS(int target)
    {
        ::SetTargetFPS(target);
    }

    void Window::SetIcon(const Image& image)
    {
        ::SetWindowIcon(image.GetImage());
    }

    bool Window::WindowShouldClose(void)
    {
        return (::WindowShouldClose());
    }

    void Window::CloseWindow()
    {
        ::CloseWindow();
    }

    void Window::ToggleFullScreen()
    {
        this->_fullscreen = !this->_fullscreen;
        ::ToggleFullscreen();
    }

    bool Window::IsFullScreen() const
    {
        return this->_fullscreen;
    }

    Vector2<int> Window::GetSize()
    {
        Vector2<int> size(::GetScreenWidth(), ::GetScreenHeight());

        return (size);
    }

    Vector2<int> Window::GetMaxSize()
    {
        Vector2<int> size(::GetMonitorWidth(::GetCurrentMonitor()), ::GetMonitorHeight(::GetCurrentMonitor()));

        return (size);
    }

    Vector2<float> Window::GetScale()
    {
        Vector2<int> window = this->GetSize();
        Vector2<int> monitor = this->GetMaxSize();

        return Vector2<float>(static_cast<float>(window.x) / monitor.x, static_cast<float>(window.y) / monitor.y);
    }

    void Window::SetSize(const Vector2<int>& size)
    {
        SetWindowSize(size.x, size.y);
    }

    void Window::SetTitle(const std::string& title)
    {
        SetWindowTitle(title.c_str());
    }

    float Window::GetFrameTime(void)
    {
        return (::GetFrameTime());
    }

    void Window::SetWindowState(unsigned int flags)
    {
        ::SetWindowState(flags);
    }

    bool Window::IsFileDropped(void)
    {
        return (::IsFileDropped());
    }

    std::vector<std::string> Window::GetDroppedFiles(int *count)
    {
        char **files = ::GetDroppedFiles(count);
        std::vector<std::string> filesVec;

        for (int i = 0; i < *count; i++) {
            filesVec.push_back(files[i]);
        }
        return (filesVec);
    }

    void Window::ClearDroppedFiles(void)
    {
        ::ClearDroppedFiles();
    }

    void Window::SetExitKey(int key)
    {
        ::SetExitKey(key);
    }

    void Window::DrawFPS(Vector2<int> pos)
    {
        ::DrawFPS(pos.x, pos.y);
    }

    void Window::SetTraceLogLevel(int logLevel)
    {
        ::SetTraceLogLevel(logLevel);
    }
}
