/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Window
*/

#include "Window.hpp"

namespace RayLib
{
    Window::Window()
    {

    }

    void Window::InitWindow(Vector2<int> size, const std::string& title)
    {
        ::InitWindow(size.x, size.y, title.c_str());
        //if (IsWindowReady() == false)
            // !! throw error

    }

    Window::~Window()
    {
        if (IsWindowReady())
            CloseWindow();
    }

    void Window::ClearBackground(const ::Color &color)
    {
        ::ClearBackground(color);
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
