/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <raylib.h>
#include <string>
#include "Vector2.hpp"
#include "Color.hpp"

namespace RayLib
{
    /**
     * @brief Font encapsulation
     * 
     */
    class Font {
        public:
            /**
             * @brief Construct a new Font object
             * creates default raylib font
             */
            Font();

            /**
             * @brief Construct a new Font object
             * 
             * @param fileName constructs font from file
             */
            Font(const std::string &fileName);

            /**
             * @brief Construct a new Font object
             * 
             * @param font 
             */
            Font(const Font &font);

            /**
             * @brief Construct a new Font object
             * 
             * @param font 
             */
            Font(const ::Font &font);

            /**
             * @brief assignment operator
             * 
             * @param font 
             * @return Font& 
             */
            Font& operator=(const Font &font);

            /**
             * @brief draw some text to the screen
             * 
             * @param text
             * @param position
             * @param fontSize
             * @param spacing
             * @param tint
             */
            void DrawText(const std::string &text, Vector2<float> position, float fontSize, float spacing=0, Color tint=WHITE);

            /**
             * @brief Destroy the Font object
             * 
             */
            ~Font();


            ::Font font;
        protected:
        private:
    };
}

#endif /* !FONT_HPP_ */
