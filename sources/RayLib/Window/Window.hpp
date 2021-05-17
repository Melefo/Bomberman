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
            Window(Vector2 size={800, 450}, const std::string& title="raylib");
            ~Window();

            void ClearBackground(const ::Color &color=BLACK);
            Vector2 GetSize();
            void SetSize(const Vector2& size);
            void SetTitle(const std::string& title);

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
