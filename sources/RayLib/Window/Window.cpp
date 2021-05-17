/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Window
*/

#include "Window.hpp"

namespace RayLib
{
    Window::Window(Vector2 size=Vector2(800, 450), const std::string& title="raylib")
    {
        InitWindow(size.x, size.y, title.c_str());

        //if (IsWindowReady() == false)
            // !! throw error
    }

    Window::~Window()
    {
        if (IsWindowReady())
            CloseWindow();
    }

    void Window::ClearBackground(const ::Color &color=BLACK)
    {
        ::ClearBackground(color);
    }

    Vector2& Window::GetSize()
    {
        Vector2 size(GetScreenWidth(), GetScreenHeight());

        return (size);
    }

    void Window::SetSize(const Vector2& size)
    {
        SetWindowSize(static_cast<int>(size.x), static_cast<int>(size.y));
    }

    void Window::SetTitle(const std::string& title)
    {
        SetWindowTitle(title.c_str());
    }
}
