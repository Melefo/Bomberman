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

    Window *Window::_window = nullptr;

    Window::Window(Vector2<int> size, const std::string& title)
    {
        ::InitWindow(size.x, size.y, title.c_str());
        //if (IsWindowReady() == false)
            // !! throw error
    }

    Window *Window::GetInstance(Vector2<int> size, const std::string& title)
    {
        if (_window == nullptr) {
            _window = new Window(size, title);
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

    bool Window::WindowShouldClose(void)
    {
        return (::WindowShouldClose());
    }

    Vector2<int> Window::GetSize()
    {
        Vector2<int> size(GetScreenWidth(), GetScreenHeight());

        return (size);
    }

    void Window::SetSize(const Vector2<int>& size)
    {
        SetWindowSize(size.x, size.y);
    }

    void Window::SetTitle(const std::string& title)
    {
        SetWindowTitle(title.c_str());
    }
}
