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
    class Input {
        public:
            Input(Vector2<int> horizontalKeys=Vector2<int>(KEY_D, KEY_A),
                     Vector2<int> verticalKeys=Vector2<int>(KEY_S, KEY_W));
            ~Input();

            float GetHorizontalAxis(void);
            float GetVerticalAxis(void);
            bool IsKeyDown(int key);
            int GetKeyPressed(void);

        protected:
        private:
            Vector2<int> _horizontalAxis;
            Vector2<int> _verticalAxis;
    };
}

#endif /* !INPUT_HPP_ */
