/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Color.hpp"
#include <string>

namespace RayLib
{
    class Window {
        public:
            Window();
            ~Window();

            static void InitWindow(Vector2<int> size=Vector2<int>(800, 450), const std::string& title="raylib");

            static void ClearBackground(Color color=BLACK);
            static Vector2<int> GetSize();
            static void SetSize(const Vector2<int>& size);
            static void SetTitle(const std::string& title);

            static void SetTargetFPS(int target);
            static bool WindowShouldClose(void);

            static void BeginDrawing(void);
            static void EndDrawing(void);

            static void CloseWindow(void);

            static void DrawCube(Vector3 position, Vector3 scale, Color color);
            static void DrawCubeWires(Vector3 position, Vector3 scale, Color color);

            static void DrawGrid(int slices, float spacing);

        protected:
        private:
    };
}

#endif /* !WINDOW_HPP_ */
