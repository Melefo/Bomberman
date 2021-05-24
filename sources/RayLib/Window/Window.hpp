/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Vector2.hpp"
#include <string>

namespace RayLib
{
    class Window {
        public:
            Window();
            ~Window();

            static void InitWindow(Vector2<int> size=Vector2<int>(800, 450), const std::string& title="raylib");

            static void ClearBackground(const ::Color &color=BLACK);
            static Vector2<int> GetSize();
            static void SetSize(const Vector2<int>& size);
            static void SetTitle(const std::string& title);

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
