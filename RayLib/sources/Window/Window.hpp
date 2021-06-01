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
#include <memory>
#include "BoundingBox.hpp"

namespace RayLib
{
    class Window {
        public:
            ~Window();

            void ClearBackground(Color color=BLACK);
            Vector2<int> GetSize();
            void SetSize(const Vector2<int>& size);
            void SetTitle(const std::string& title);
            void SetTargetFPS(int target);
            bool WindowShouldClose(void);
            void BeginDrawing(void);
            void EndDrawing(void);
            void DrawCube(Vector3 position, Vector3 scale, Color color);
            void DrawCubeWires(Vector3 position, Vector3 scale, Color color);
            void DrawBoundingBox(BoundingBox box, Color color);

            void DrawGrid(int slices, float spacing);
            float GetFrameTime(void);

            //Window(Window& other) = delete;
            //void operator=(const Window& other) = delete;

            static std::unique_ptr<Window>& GetInstance(Vector2<int> size, const std::string& title);

            Window(Vector2<int> size=Vector2<int>(800, 450), const std::string& title="raylib");
        protected:
        private:

            static std::unique_ptr<Window> _window;

    };
}

#endif /* !WINDOW_HPP_ */
