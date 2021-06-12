/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "Vector2.hpp"

namespace RayLib
{
    /**
     * @brief Input encapsulation
     * 
     */
    class Input {
        public:
            /**
             * @brief Construct a new Input object
             * 
             * @param horizontalKeys macros for horizontal axis (x = negative, y = positive)
             * @param verticalKeys macros for vertical axis (x = negative, y = positive)
             */
            Input(Vector2<int> horizontalKeys=Vector2<int>(KEY_D, KEY_A),
                     Vector2<int> verticalKeys=Vector2<int>(KEY_S, KEY_W));

            /**
             * @brief Destroy the Input object
             * 
             */
            ~Input() = default;

            /**
             * @brief Get the Horizontal Axis object
             * 
             * @return float Negative for left, positive for right
             */
            float GetHorizontalAxis(void);

            /**
             * @brief Get the Vertical Axis object
             * 
             * @return float Negative for down, positive for up
             */
            float GetVerticalAxis(void);

            /**
             * @brief 
             * returns true if key parameter is pressed during frame
             * @param key 
             * @return true 
             * @return false 
             */

            /**
             * @brief 
             * returns the last key pressed
             * @param key 
             * @return true 
             * @return false 
             */
            bool IsKeyDown(int key);
            int GetKeyPressed(void);

            /**
             * @brief Get the Horizontal Keys
             * 
             * @return Vector2<int> 
             */
            Vector2<int> GetHorizontalKeys(void);
            /**
             * @brief Get the Vertical Keys
             * 
             * @return Vector2<int> 
             */
            Vector2<int> GetVerticalKeys(void);

        protected:
        private:
            Vector2<int> _horizontalAxis;
            Vector2<int> _verticalAxis;
    };
}

#endif /* !INPUT_HPP_ */
