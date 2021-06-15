/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <raylib.h>
#include "Vector2.hpp"
#include "Ray.hpp"

namespace RayLib
{
    /**
     * @brief static Mouse encapsulation
     * 
     */
    class Mouse {
        public:
            /**
             * @brief Construct a new Mouse object
             * 
             */
            Mouse() = default;

            /**
             * @brief Destroy the Mouse object
             * 
             */
            ~Mouse() = default;

            /**
             * @brief Get the mouse's position
             * 
             * @return Vector2<float> 
             */
            static Vector2<float> GetPosition();

            /**
             * @brief 
             * returns true if mouse button is down during frame
             * left mouse button: MOUSE_BUTTON_LEFT
             * right mouse button: MOUSE_BUTTON_RIGHT
             * @param button 
             * @return true 
             * @return false 
             */
            static bool IsButtonDown(int button);

            /**
             * @brief 
             * returns true if mouse button was pressed during frame
             * left mouse button: MOUSE_BUTTON_LEFT
             * right mouse button: MOUSE_BUTTON_RIGHT
             * @param button 
             * @return true 
             * @return false 
             */
            static bool IsButtonPressed(int button);

            /**
             * @brief 
             * returns true if mouse button is up during frame
             * @param button 
             * @return true 
             * @return false 
             */
            static bool IsButtonUp(int button);

            /**
             * @brief 
             * returns true if mouse button was released during frame
             * @param button 
             * @return true 
             * @return false 
             */
            static bool IsButtonReleased(int button);

        protected:
        private:
    };
}

#endif /* !MOUSE_HPP_ */
