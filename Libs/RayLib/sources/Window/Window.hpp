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
#include "Window.hpp"
#include "Image.hpp"
#include "BoundingBox.hpp"

namespace RayLib
{
    /**
     * @brief Window encapsulation (Singleton)
     * 
     */
    class Window {
        public:
            /**
             * @brief Destroy the Window object
             *
             */
            ~Window();

            /**
             * @brief Set window background to color
             * 
             * @param color 
             */
            void ClearBackground(Color color=BLACK);

            /**
             * @brief Get the window's size as a vector2<int>
             *
             * @return Vector2<int>
             */
            Vector2<int> GetSize();

            /**
             * @brief Set the window's size
             *
             * @param size
             */
            void SetSize(const Vector2<int>& size);

            /**
             * @brief Get the monitor's size as a vector2<int>
             *
             * @return Vector2<int>
             */
            Vector2<int> GetMaxSize();

            /**
             * @brief Get the Scale between monitor size and window size
             *
             * @return Vector2<float>
             */
            Vector2<float> GetScale();

            /**
             * @brief Change Window State mode
             *
             * @param size
             */
            void ToggleFullScreen();
            /**
             * @brief Get Window State mode
             *
             * @return bool
             */
            bool IsFullScreen() const;

            /**
             * @brief Set the window's Icon
             * 
             * @param image 
             */
            void SetIcon(const Image& image);
            /**
             * @brief Set the window's title
             * 
             * @param title 
             */
            void SetTitle(const std::string& title);

            /**
             * @brief Set the target FPS
             * 
             * @param target 
             */
            void SetTargetFPS(int target);

            /**
             * @brief Returns true if you press ESC or close button
             * 
             * @return true 
             * @return false 
             */
            bool WindowShouldClose(void);

            /**
             * @brief Close the window
             * 
             * @return vois
             */
            void CloseWindow(void);

            /**
             * @brief Initialize canvas for drawing
             * 
             */
            void BeginDrawing(void);

            /**
             * @brief Stop drawing
             * 
             */
            void EndDrawing(void);

            /**
             * @brief Draw a cube at position, with scale, and color
             * 
             * @param position 
             * @param scale 
             * @param color 
             */
            void DrawCube(Vector3 position, Vector3 scale, Color color);

            /**
             * @brief Draw a cube's outline
             * 
             * @param position 
             * @param scale 
             * @param color 
             */
            void DrawCubeWires(Vector3 position, Vector3 scale, Color color);

            /**
             * @brief Draw sphere wires
             * 
             * @param position 
             * @param scale 
             * @param color 
             */
            void DrawSphereWires(Vector3 centerPos, float radius, int rings=20, int slices=20, Color color=RED);

            /**
             * @brief Draw bounding box
             * 
             * @param box 
             * @param color 
             */
            void DrawBoundingBox(BoundingBox box, Color color);

            /**
             * @brief Draw a grid with slices squares with spacing spaces
             * 
             * @param slices 
             * @param spacing 
             */
            void DrawGrid(int slices, float spacing);

            /**
             * @brief Returns delta time
             * 
             * @return float 
             */
            float GetFrameTime(void);

            //Window(Window& other) = delete;
            //void operator=(const Window& other) = delete;

            /**
             * @brief Set window configuration state using flags
             * 
             * @param flags 
             */
            void SetWindowState(unsigned int flags);

            /**
             * @brief set the key given as the exit key
             * 
             * @param key
             */
            void SetExitKey(int key);

            /**
             * @brief Function that returns the singleton
             * 
             * @param size 
             * @param title 
             * @return std::unique_ptr<Window>& 
             */
            static std::unique_ptr<Window>& GetInstance(Vector2<int> size, const std::string& title);

            static void SetTraceLogLevel(int logLevel);

            /**
             * @brief Construct a new Window
             * 
             * @param size 
             * @param title 
             */
            Window(Vector2<int> size=Vector2<int>(800, 450), const std::string& title="raylib");

            bool IsFileDropped(void);
            std::vector<std::string> GetDroppedFiles(int *count);
            void ClearDroppedFiles(void);

            // draw FPS
            void DrawFPS(Vector2<int> pos);

        protected:
        private:
            bool _fullscreen;
            static std::unique_ptr<Window> _window;

    };
}

#endif /* !WINDOW_HPP_ */
